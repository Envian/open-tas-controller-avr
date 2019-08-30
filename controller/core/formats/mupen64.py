# Open TAS - A Command line interface for the Open TAS Controller.
# Copyright (C) 2019  Russell Small
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

from io import BytesIO, IOBase
from core.formatting import *
from core.movies import N64Movie

def getName():
	return "Mupen64"

def loadMovie(file):
	if not isinstance(file, IOBase):
		return None

	data = Mupen64File()
	data.load(file)
	if data.header != b"M64\x1A":
		return None

	movie = N64Movie(data.rom, data.controllers, data.author, data.description)
	inputStream = BytesIO(data.inputData)
	for x in range(data.frames):
		movie.write([inputStream.read(4)])
	return movie

def saveMovie(file):
	pass

class Mupen64File:
	def __init__(self):
		pass

	def load(self, file):
		file.seek(0)

		self.header = file.read(4)
		if self.header != b"M64\x1A":
			return

		self.version = readInt(file, 4)
		self.uid = readInt(file, 4)
		self.realframes = readInt(file, 4)
		self.rerecords = readInt(file, 4)
		self.fps = readInt(file, 1)
		self.controllers = readInt(file, 1)
		self._reserved1 = file.read(2)
		self.frames = readInt(file, 4)
		self.startType = file.read(2)
		self._reserved2 = file.read(2)
		self.controllerFlags = readInt(file, 4)
		self._reserved3 = file.read(160)
		self.rom = readString(file, 32)
		self.crc = readInt(file, 4)
		self.countryCode = readInt(file, 2)
		self._reserved4 = file.read(56)
		self.videoPlugin = readString(file, 64)
		self.soundPlugin = readString(file, 64)
		self.inputPlugin = readString(file, 64)
		self.rspPlugin = readString(file, 64)
		self.author = readString(file, 222)
		self.description = readString(file, 256)
		self.inputData = file.read()


class Mupen64Writer:
	def __init__(self, file, controllers=1, rom="Unknown ROM", author="Unknown Author", description="Recorded with Open TAS"):
		self.__file = file
		self.system = 0x40 # Nintendo 64
		self.controllers = controllers
		self.__frames = 0

		file.write(b"M64\x1A") #Header
		file.write(bytearray([3, 0, 0, 0])) #Version
		file.write(bytearray([0, 0, 0, 0])) #uid
		file.write(bytearray([0, 0, 0, 0])) #Frame Count (Includes lag frames)
		file.write(bytearray([0, 0, 0, 0])) #Rerecord count
		file.write(bytearray([30])) #fps
		file.write(bytearray([controllers])) #controllers
		file.write(bytearray([0, 0])) #reserved
		file.write(bytearray([0, 0, 0, 0])) #input count (To be filled later)
		file.write(bytearray([2, 0])) #Movie start type (Power On)
		file.write(bytearray([0, 0])) #reserved
		file.write(bytearray([(2 ** controllers) - 1, 0, 0, 0 ])) #controller flags
		file.write(bytearray([0] * 160)) #reserved
		file.write(convertString(rom, 32, nullTerminate=True, truncate=False)) #ROM Name
		file.write(bytearray([0, 0, 0, 0])) #crc
		file.write(bytearray([0, 0])) #country code
		file.write(bytearray([0] * 56)) #reserved
		file.write(bytearray([0] * 64)) #Video Plugin
		file.write(bytearray([0] * 64)) #Sound Plugin
		file.write(bytearray([0] * 64)) #Input Plugin
		file.write(bytearray([0] * 64)) #RSP Plugin
		file.write(convertString(author, 222, nullTerminate=True, truncate=False)) #Author
		file.write(convertString(description, 256, nullTerminate=True, truncate=False)) #Description

	def write(self, inputs):
		self.__file.write(inputs)
		self.__frames += 1

	def close(self):
		self.__file.seek(0x18)
		#self.__file.write(convertInt(self.__frames, 4))
		self.__file.write(bytearray([0xFF, 0xFF, 0xFF, 0xFF]))
		self.__file.flush()
		self.__file.close()

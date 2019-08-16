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

from formats.helpers import readAt, readAtInt

def getName():
	return "Mupen64"

def loadMovie(file):
	return Mupen64Reader(file)

def isMovie(file):
	#N.B: There's a few properties that we may want to consider that would make replays harder:
	#   Version (0x04) - Only 3 is supported now.
	#   Movie Type (0x1C) - Should be 2 (From power on), not 1 (From snapshot)
	#   Controller Flags (0x20) - Does not currently support perriphreals
	with open(file, "rb") as movie:
		return movie.read(4) == b"M64\x1A"

class Mupen64Reader:
	def __init__(self, path):
		self.__path = path
		self.eof = False

		self.system = 0x40
		self.author = None
		self.description = None
		self.controllers = None
		self.frames = None
		self.rerecords = None
		self.rom = None
		self.romcrc = None
		self.countrycode = None


	def __enter__(self):
		self.open()
		return self

	def __exit__(self, type, value, traceback):
		self.close()

	def open(self):
		self.__file = open(self.__path, "rb")

		self.author = readAt(self.__file, 0x0222, 222).decode().strip("\x00")
		self.description = readAt(self.__file, 0x0300, 256).decode().strip("\x00")
		self.controllers = readAt(self.__file, 0x15)[0]
		self.frames = readAtInt(self.__file, 0x18)
		self.rerecords = readAtInt(self.__file, 0x10)
		self.rom = readAt(self.__file, 0xC4, 32).decode().strip("\x00")
		self.romcrc = readAtInt(self.__file, 0xE4)
		self.countrycode = readAtInt(self.__file, 0xE8, size=2)

		self.__file.seek(0x400)

	def close(self):
		self.__file.close()

	def getInputs_player1(self):
		return self.__getInputs()

	def __getInputs(self):
		inputs = self.__file.read(4)
		self.eof = len(inputs) != 4
		return inputs

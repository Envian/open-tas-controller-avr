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
	return readAt(file, 0, 4) == b"M64\x1A"

class Mupen64Reader:
	def __init__(self, file):
		self.__file = file
		self.eof = None

		self.system = 0x40 # Nintendo 64
		self.author = readAt(file, 0x0222, 222).decode().strip("\x00")
		self.description = readAt(file, 0x0300, 256).decode().strip("\x00")
		self.controllers = readAt(file, 0x15)[0]
		self.frames = readAtInt(file, 0x18)
		self.rerecords = readAtInt(file, 0x10)
		self.rom = readAt(file, 0xC4, 32).decode().strip("\x00")
		self.romcrc = readAtInt(file, 0xE4)
		self.countrycode = readAtInt(file, 0xE8, size=2)

		file.seek(0x400)

	def getInputs_player1(self):
		return self.__getInputs()

	def __getInputs(self):
		inputs = self.__file.read(4)
		self.eof = len(inputs) != 4
		return inputs

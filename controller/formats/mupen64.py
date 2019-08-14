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

def getName():
	return "mupen64"

def loadMovie(file):
	return Mupen64Reader(file)

def isMovie(file):
	return True

class Mupen64Reader:
	def __init__(self, path):
		self.__path = path
		self.system = 0x40
		self.eof = False

	def __enter__(self):
		self.open()
		return self

	def __exit__(self, type, value, traceback):
		self.close()

	def open(self):
		self.__file = open(self.__path, "rb")
		#TODO: Load this from the mupen file
		self.controllers = 1
		self.__file.seek(0x400)

	def close(self):
		self.__file.close()

	def getInputs_player1(self):
		return self.__getInputs()

	def __getInputs(self):
		inputs = self.__file.read(4)
		self.eof = len(inputs) != 4
		return inputs

# Converts emulator recording files into TASRAW files.
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

class TasrawStream:
	__HEADER = b"TASRAW"
	__CONSOLE = 0x64
	__VERSION = 0
	__DESCRIPTION_LENGTH = 32

	def __init__(self, file, description = ""):
		if not description:
			description = bytearray(self.__DESCRIPTION_LENGTH)
		elif len(description) > self.__DESCRIPTION_LENGTH:
			description = description[:self.__DESCRIPTION_LENGTH]

		if type(description) is not bytearray:
			description = description.encode("ASCII", "replace")

		self.__description = description.ljust(self.__DESCRIPTION_LENGTH, bytearray(1))
		self.__filename = file
		self.__last = None
		self.__count = 0

	def __enter__(self):
		self.open()
		self.writeHeader()
		return self

	def __exit__(self, type, value, traceback):
		self.flush()
		self.close()

	def open(self):
		self.__file = open(self.__filename, "wb")

	def writeHeader(self):
		self.__file.write(self.__HEADER)
		self.__file.write(bytearray([self.__CONSOLE, self.__VERSION]))
		self.__file.write(self.__description)

	def flush(self):
		if self.__count != 0:
			self.__file.write(self.__last)
			self.__file.write(bytearray([self.__count - 1]))
			self.__file.flush()

	def close(self):
		self.__file.close()

	def writeInput(self, input):
		if type(input) is list:
			input = bytearray(input)
		elif type(input) is int:
			input = input.to_bytes(byteorder="big", signed="false")

		if self.__last != input or self.__count == 256:
			if self.__count != 0:
				self.__file.write(self.__last)
				self.__file.write(bytearray([self.__count - 1]))

			self.__last = input
			self.__count = 1
		else:
			self.__count = self.__count + 1

#!/usr/bin/env python
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

from serial import Serial

class TASController:
	def __init__(self, port, baud):
		self.__port = Serial(port, baud)

	def play(self, movie):
		self.__port.read(5)
		self.__port.write(bytearray([0x0A])) # begin playback
		self.__port.write(bytearray([movie.system]))
		self.__port.write(bytearray([movie.controllers]))

		while not movie.eof:
			size = self.__port.read(1)[0]
			self.__port.write(movie.getInputs_player1())

		self.__port.write([0xFF, 0xFF, 0xFF, 0xFF])

	def record(self, movie):
		pass

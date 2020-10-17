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

class Movie:
	def __init__(self, system, game, controllers, author, description):
		self.system = system
		self.game = game
		self.controllers = controllers
		self.author = author
		self.description = description

		self.frames = 0

	def play(self, connection):
		raise NotImplementedError()

	def record(self, connection):
		raise NotImplementedError()

	def write(self, raw, **kargs):
		raise NotImplementedError()

	def print(self):
		if self.system: print("System: ", self.system)
		if self.game: print("ROM:    ", self.game)
		if self.author: print("Author: ", self.author)
		if self.description: print("Desc:   ", self.description)

class N64Movie(Movie):
	def __init__(self, game, controllers, author, description):
		super().__init__("Nintendo 64", game, controllers, author, description)
		self.inputs = ([],) * controllers

	def play(self, connection, statusFunction = None):
		connection.write(bytearray([0x0A])) # begin playback
		connection.write(bytearray([0x40])) # Nintendo 64
		#connection.write(bytearray([self.controllers]))
		connection.write(bytearray([0x01])) # Temp - One controller

		for frame in range(self.frames):
			size = connection.read(1)[0]
			if size == 0xFF: break

			#Size is equal to the number of bytes the chip is expecting back.
			#currently not considered.
			inputs = [input[frame] for input in self.inputs]
			connection.write(b"".join(inputs))

			statusFunction(self, frame, inputs) if statusFunction else None

	def record(self, connection, statusFunction = None):
		connection.write(bytearray([0x0B])) # begin Recording
		connection.write(bytearray([0x40])) # Nintendo 64
		connection.write(bytearray([self.controllers]))

		try:
			while True:
				inputs = [connection.read(4) for x in range(self.controllers)]
				self.write(b"".join(inputs))
				statusFunction(self, frame, inputs) if statusFunction else None


		except KeyboardInterrupt:
			pass


	def write(self, raw, **kargs):
		for x in range(self.controllers):
			self.inputs[x].append(raw[x])
		self.frames += 1

#!/usr/bin/env python3

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

def readUntil(stream, char):
	result = stream.read(1)
	while result[-1] != char:
		result += stream.read(1)
	return result

class CommandStream:
	def __init__(self, stream):
		self.inputSize = None
		self.stream = stream;
		self.dataParser = None

	def readPacket(self):
		command = self.stream.read(1)[0]
		isText = (command >= ord("A") and command <= ord("Z")) or command == ord(" ") or command == ord("\t") or command == 0xFF or command == 0xFE
		return {
			"command": command,
			"isText": isText,
			"data": self.getData(command, isText)
		}

	def sendPacket(self, packet):
		self.stream.write(bytearray([packet["command"]]))
		self.stream.write(packet["data"])

	def getData(self, command, isText):
		if isText:
			return readUntil(self.stream, ord("\n"))

		if command == ord("c"):
			return self.stream.read(3)

		if self.dataParser:
			return self.dataParser(self, command)

		# Input Packet Commands
		if command == 0x80:
			return self.stream.read(self.inputSize);
		if command == 0x81:
			self.inputSize = self.stream.read(1)[0]
			return bytearray([self.inputSize])

		#Console Specific
		if command == 0x82: #N64 - Configure Controller
			return self.stream.read(4)

		return b""

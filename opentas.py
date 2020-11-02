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

import os
import sys

from argparse import ArgumentParser, FileType
from serial import Serial

from commandstream import CommandStream

parser = ArgumentParser(description="Can play TAS's or record inputs from an Open TAS Controller.")
parser.add_argument("port", help="The port that the arduino is on")
parser.add_argument("-b", "--baud", default=250000, help="Sets the baud rate used in communication. Defaults to 250,000")
subparsers = parser.add_subparsers(title="Mode", dest="mode", required=True)

playparser = subparsers.add_parser("play", description="Plays a movie file through the Open TAS Controller.")
playparser.add_argument("input", nargs="?", type=FileType("rb"), default=sys.stdin, help="The file to playback")

recordparser = subparsers.add_parser("record", description="Records a movie from a connected controller & console.")
recordparser.add_argument("console", choices=["n64"], help="The console to record from")
recordparser.add_argument("output", type=FileType("wb+"), help="An output file to save the recording to")

def main(arguments):
	print("Connecting to OpenTAS Controller on " + arguments.port + "... ", end="", flush=True)
	device = Serial(arguments.port, arguments.baud, timeout=10);
	preamble = device.read_until(b"\n")
	if preamble == b"OpenTAS\n":
		print("Success!")
		if arguments.mode == "play":
			play(arguments, device)
		elif arguments.mode == "record":
			record(arguments, device);
		else:
			raise Abort("Unknown Command")
	else:
		print("Failed!")
		raise Abort("Connected device is not an OpenTAS Controller.")

def play(arguments, device):
	device.timeout = None
	fileStream = CommandStream(arguments.input)
	deviceStream = CommandStream(device)


	while True:
		packet = fileStream.readPacket()
		if packet["isText"]:
			continue

		deviceStream.sendPacket(packet)

		# input packets require waiting on response
		if packet["command"] == 0x80:
			print("X", end="", flush=True)
			while True:
				response = deviceStream.readPacket()
				if response["command"] == 0x8B:
					break;

				if response["isText"]:
					try:
						print(byteArray([response["command"]]).decode("ASCII"), end="")
					except:
						pass
					print(response["data"].decode("ASCII"))

		if packet["command"] == ord('x'):
			return

def record(arguments, device):
	device.timeout = None
	device.write(("c" + arguments.console + "r").encode())

	fileStream = CommandStream(arguments.output)
	deviceStream = CommandStream(device)

	try:
		while True:
			packet = deviceStream.readPacket()
			fileStream.sendPacket(packet)
			if packet["isText"]:
				try:
					print(byteArray([response["command"]]).decode("ASCII"), end="")
				except:
					pass
				print(response["data"].decode("ASCII"))
	except KeyboardInterrupt:
		device.write(b"x")
		arguments.output.write(b"x")
		arguments.output.close()

class Abort(Exception):
	pass

try:
	main(parser.parse_args())
except Abort as ex:
	print("Error: " + str(ex))

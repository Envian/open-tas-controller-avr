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

from argparse import ArgumentParser
from core.connection import TASController
import formats.helpers

parser = ArgumentParser(description="Can play TAS's or record inputs from an Open TAS Controller.")
parser.add_argument("port", action="store", help="The port that the arduino is on")
parser.add_argument("--force", action="store_true", help="Bypasses sanity checks and forces the movie to play or record from the given port")
parser.add_argument("-i", "--input", action="store", help="The file to playback")
parser.add_argument("-f", "--format", action="store", help="Sets the format for the input or output file")
parser.add_argument("-b", "--baud-rate", action="store", default=250000, help="Sets the baud rate used in communication. Defaults to 250,000")

def main(arguments):
	port = connectToController(arguments.port, arguments.baud_rate, arguments.force)
	input, output = getStreams(arguments.input, None)
	format = getFormat(arguments.format, input)

	if input:
		with input:
			movie = format.loadMovie(input)
			print("Beginning playback\n")
			if movie.rom: print("ROM:    " + movie.rom)
			if movie.author: print("Author: " + movie.author)
			if movie.description: print("Desc:   " + movie.description)
			port.play(movie, progressBar)
	else:
		pass
		#todo: recording

	print("\n")

def connectToController(port, baudrate, force):
	print("Connecting to OpenTAS Controller on: " + port)
	controller = TASController(port, baudrate)
	print("Connection successful.")

	if not controller.isOpenTAS:
		if force:
			print("Warning: Connected device is not an OpenTAS Controller.")
		else:
			raise Abort("Connected device is not an OpenTAS Controller. Use --force to force playback.")
			return

	return controller

def getStreams(input, output):
	if input:
		return (open(input, "rb"), None)
	else:
		return (None, open(output, "wb"))

def getFormat(format, input):
	if format:
		parser = formats.helpers.getFormatByName(format)

		if not parser.isMovie(input):
			raise Abort("Input file is not the correct format. Expected: " + parser.getName())

		return parser
	elif input:
		print("Auto-detecting format...", end="", flush=True)
		parser = formats.helpers.getFormatByFile(input)

		if not parser:
			print(" Failed!")
			raise Abort("Unknown file format.")

		print(" Success!")
		print("Using format: " + parser.getName())
		return parser
	else:
		raise Abort("File format must be specified.")

def progressBar(movie, frame, inputs):
	progress = frame / movie.frames
	icon = ["|", "/", "-", "\\"][frame % 4]

	line = "{0: >7}/{1} [{3: <50}] {2:.1%} {4}".format(frame, movie.frames, progress, "#" * int(progress * 50), icon)

	print(line, end="", flush=True)
	print("\b" * len(line), end="")


class Abort(Exception):
	pass

try:
	main(parser.parse_args())
except Abort as ex:
	print("Error: " + str(ex))

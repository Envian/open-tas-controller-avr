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
	print("Connecting to OpenTAS Controller on: " + arguments.port)
	port = TASController(arguments.port, arguments.baud_rate)
	print("Connection successful.")

	if not port.isOpenTAS:
		if arguments.force:
			print("Warning: Connected device is not an OpenTAS Controller.")
		else:
			print("Error: Connected device is not an OpenTAS Controller. Use --force to force playback.")
			return

	#determine parser
	parser = None
	if arguments.format:
		print("Using format: " + arguments.format)
		parser = formats.helpers.getFormatByName("mupen64")
		if not parser.isMovie(arguments.input):
			print("Error: input file is not the correct format. Expected: " + parser.getName())
			return
	else:
		print("Auto-detecting format...")
		parser = formats.helpers.getFormatByFile(arguments.input)

		if not parser:
			print("Error: Unknown file format.")
			return

		print("Format detected: " + parser.getName())

	print("")

	#begin playback
	with parser.loadMovie(arguments.input) as movie:
		port.play(movie)

main(parser.parse_args())

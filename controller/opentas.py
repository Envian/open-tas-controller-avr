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

from argparse import ArgumentParser, FileType
import os

from core.services import connectToController, loadMovie, getFormatByName
from core.output import printPlayProgress

import core.movies

parser = ArgumentParser(description="Can play TAS's or record inputs from an Open TAS Controller.")
parser.add_argument("port", action="store", help="The port that the arduino is on")
parser.add_argument("-b", "--baud", action="store", default=250000, help="Sets the baud rate used in communication. Defaults to 250,000")
subparsers = parser.add_subparsers(title="Mode", dest="mode", required=True)

playparser = subparsers.add_parser("play", description="Plays a movie file through the Open TAS Controller.")
playparser.add_argument("-i", "--input", action="store", type=FileType("rb"), required=True, help="The file to playback")
playparser.add_argument("-f", "--format", action="store", help="Sets the format for the input file")

recordparser = subparsers.add_parser("record", description="Records a movie from a connected controller & console.")
recordparser.add_argument("-o", "--output", action="store", type=FileType("wb+"), required=True, help="An output file to save the recording to")
recordparser.add_argument("-f", "--format", action="store", required=True, help="Sets the format for the output file")


def main(arguments):
	print("Connecting to OpenTAS Controller on " + arguments.port + "... ", end="", flush=True)
	controller, isOpenTAS = connectToController(arguments.port, arguments.baud)
	if not isOpenTAS:
		print("Failed!")
		raise Abort("Connected device is not an OpenTAS controller.")
	print("Success!")


	if arguments.mode == "play":
		play(controller, arguments)
	elif arguments.mode == "record":
		record(controller, arguments)

	print("\n")

def play(controller, arguments):
	print("Loading Movie File... ", end="", flush=True)
	movie = loadMovie(arguments.input, arguments.format)

	if not movie:
		print("Failed!")
		raise Abort("Unable to load movie file - Unkown or incorrect file format.")

	print("Complete.")
	confirmConnection(movie)
	movie.play(controller, printPlayProgress)

def record(controller, arguments):
	print("Preparing to record movie... ", end="", flush=True)
	movie = core.movies.N64Movie("test", 1, "test", "test")
	movie.record(controller, debugPrint)

	print("\n\n\n")


def confirmConnection(movie):
	print("")
	movie.print()
	print("")

class Abort(Exception):
	pass

def debugPrint(movie, frames, inputs):
	print(frames, end="", flush=True)

try:
	main(parser.parse_args())
except Abort as ex:
	print("Error: " + str(ex))

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
import formats.mupen64

parser = ArgumentParser(description="Can play TAS's or record inputs from an Open TAS Controller.")
parser.add_argument("port", action="store", help="The port that the arduino is on")
parser.add_argument("-i", "--input", action="store", help="The file to playback")
parser.add_argument("-b", "--baud-rate", action="store", default=250000, help="Overrides the default baud rate")

arguments = parser.parse_args()

port = TASController(arguments.port, arguments.baud_rate)
with formats.mupen64.loadMovie(arguments.input) as movie:
	port.play(movie)

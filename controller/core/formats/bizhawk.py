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

import json

from zipfile import ZipFile
from core.movies import N64Movie

def getName():
	return "Bizhawk Movie"

def loadMovie(file):
	if not isinstance(file, ZipFile):
		return None

	filelist = file.namelist()
	if not ("Comments.txt" in filelist and
			"Input Log.txt" in filelist and
			"Header.txt" in filelist and
			"SyncSettings.json" in filelist):
		return None

	comment = file.open("Comments.txt", "r").read()
	rom, authors = readHeader(file.open("Header.txt", "r"))
	controllers = readSync(file.open("SyncSettings.json", "r"))

	movie = N64Movie(rom, controllers, authors, comment)
	loadInputs(movie, file.open("Input Log.txt", "r"))
	return movie

def readHeader(file):
	lines = file.read().split(b"\n", 1)
	attributes = {}
	for line in lines:
		parts = line.split(b" ", 1)
		if (len(parts) == 2):
			attributes[parts[0]] = parts[1].decode("ASCII")

	return (attributes.get("GameName", "Unknown Game"), attributes.get("Author", "Unknown Author"))

def readSync(file):
	return 1


def loadInputs(movie, file):
	lines = file.read().split(b"\n")[2:-2]
	movie.write([bytearray([0, 0, 0, 0])])
	movie.write([bytearray([0, 0, 0, 0])])
	movie.write([bytearray([0, 0, 0, 0])])
	movie.write([bytearray([0, 0, 0, 0])])
	movie.write([bytearray([0, 0, 0, 0])])
	movie.write([bytearray([0, 0, 0, 0])])
	movie.write([bytearray([0, 0, 0, 0])])
	movie.write([bytearray([0, 0, 0, 0])])
	movie.write([bytearray([0, 0, 0, 0])])
	for line in lines:
		(x, y, inputs) = line[4:34].split(b",")
		movie.write(transformInputs(x, y, inputs))

def transformInputs(x, y, inputs):
	highByte = 0
	highByte += (0x80 if inputs[11] != 46 else 0)
	highByte += (0x40 if inputs[10] != 46 else 0)
	highByte += (0x20 if inputs[9] != 46 else 0)
	highByte += (0x10 if inputs[8] != 46 else 0)
	highByte += (0x8 if inputs[7] != 46 else 0)
	highByte += (0x4 if inputs[6] != 46 else 0)
	highByte += (0x2 if inputs[5] != 46 else 0)
	highByte += (0x1 if inputs[4] != 46 else 0)

	lowByte = 0
	lowByte += (0x20 if inputs[16] != 46 else 0)
	lowByte += (0x10 if inputs[17] != 46 else 0)
	lowByte += (0x8 if inputs[12] != 46 else 0)
	lowByte += (0x4 if inputs[13] != 46 else 0)
	lowByte += (0x2 if inputs[14] != 46 else 0)
	lowByte += (0x1 if inputs[15] != 46 else 0)

	return [bytearray([highByte, lowByte, int(x) % 256, int(y) % 256])]

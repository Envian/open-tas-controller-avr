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
import glob
import importlib

def listFormats():
	modules = [os.path.split(mod)[-1][:-3] for mod in glob.glob(os.path.join(os.path.dirname(__file__), "*.py"))]
	modules.remove("__init__")
	modules.remove(__name__.split(".")[-1])
	return modules

def getFormatByFile(file):
	for format in listFormats():
		targetModule = getFormatByName(format)
		if targetModule.isMovie(file):
			return targetModule
	return None


def getFormatByName(name):
	try:
		targetModule = importlib.import_module("formats." + name)
		return targetModule
	except ImportError:
		raise Exception("Format unsupported. Unable to find format file: " + name + ".py")

def readAt(stream, position, count = 1):
	stream.seek(position)
	return stream.read(count)

def readAtInt(stream, position, size = 4, littleEndian = True):
	raw = readAt(stream, position, 4)
	if littleEndian: raw = raw[::-1]

	value = 0
	for byte in raw:
		value = value * 256 + byte
	return value

def convertString(string, size=None, truncate=True, nullTerminate=True):
	realsize = len(string) + 1 if size == None else size
	realsize = realsize - 1 if nullTerminate else realsize
	result = string if len(string) <= realsize else string[:realsize]
	result = result.encode()

	if not truncate:
		result = result.ljust(realsize, bytearray([0]))

	if nullTerminate:
		result += bytearray([0])

	return result

def convertInt(value, size=4, littleEndian=True):
	data = b""

	for x in range(size):
		data += bytearray([data % 256])
		data = data / 256

	if not littleEndian:
		data = data.reverse()

	return data

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

import glob
import os
import importlib
import zipfile

from serial import Serial

def connectToController(port, rate):
	controller = Serial(port, rate, timeout=5)
	isOpenTAS = controller.read(7) == b"OpenTAS"
	controller.timeout = None

	return (controller, isOpenTAS)

def loadMovie(file, specifiedFormat):
	formats = [specifiedFormat] if specifiedFormat else listFormats()
	file = getMovieFile(file)

	for name in formats:
		format = getFormatByName(name)
		movie = format.loadMovie(file)
		if movie:
			return movie
	return None

def getMovieFile(file):
	if zipfile.is_zipfile(file):
		zip = zipfile.ZipFile(file)
		if len(zip.namelist()) == 1:
			return getMovieFile(zip.open(zip.namelist()[0], "r"))
		else:
			return zip
	else:
		file.seek(0)
		return file

def listFormats():
	modules = [os.path.split(mod)[-1][:-3] for mod in glob.glob(os.path.join(os.path.dirname(__file__), "formats", "*.py"))]
	modules.remove("__init__")
	return modules

def getFormatByName(name):
	try:
		targetModule = importlib.import_module("core.formats." + name)
		return targetModule
	except ImportError:
		raise Exception("Format unsupported. Unable to find format file: " + name + ".py")

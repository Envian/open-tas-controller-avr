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
	modules = [mod.replace("/", ".")[:-3] for mod in glob.glob("*.py")]
	modules.remove("__init__")
	modules.remove(__name__)
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

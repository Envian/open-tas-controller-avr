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

def readInt(stream, size, littleEndian=True):
	raw = stream.read(size)
	if littleEndian: raw = raw[::-1]
	value = 0
	for byte in raw:
		value = value * 256 + byte
	return value

def readString(stream, length=None, fixed=True):
	if fixed:
		return stream.read(length).strip(b"\x00").decode()

	raw = stream.read(1)
	while raw[-1] != "\x00" and len(raw) < length:
		raw += stream.read(1)
	return raw.decode()

def formatString(string, size=None, truncate=True, nullTerminate=True):
	realsize = len(string) + 1 if size == None else size
	realsize = realsize - 1 if nullTerminate else realsize
	result = string if len(string) <= realsize else string[:realsize]
	result = result.encode()

	if not truncate:
		result = result.ljust(realsize, bytearray([0]))

	if nullTerminate:
		result += bytearray([0])

	return result

def writeInt(stream, value, size=4, littleEndian=True):
	data = b""

	for x in range(size):
		data += bytearray([data % 256])
		data = data / 256

	if not littleEndian:
		data = data.reverse()

	return stream.write(data)

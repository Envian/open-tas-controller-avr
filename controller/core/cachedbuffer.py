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

import io
from os import fdopen

class CachedBuffer(io.IOBase):
	def __init__(self, raw_buffer):
		self.raw = os.fdopen(raw_buffer.fileno(), "rb")
		self.buffer = b""
		self.pos = 0

	def seek(self, pos, whence=0):
		if whence == 0:
			self.pos = pos
		elif whence == 1:
			self.pos += pos
		else:
			raise io.UnsupportedOperation("Seeking from the end of the buffer is not supported")
		return self.pos

	def seekable(self):
		return True

	def readable(self):
		return True

	def read(self, size):
		toRead = (self.pos + size) - len(self.buffer)
		if toRead > 0:
			self.buffer += self.raw.read(toRead)
		result = self.buffer[self.pos:self.pos + size]
		self.pos += size
		return result

# Injects a start input for flash carts.
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

import sys

HEADER_LENGTH = 0x28
CMD = bytearray([0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00])

def usage():
	print("add_flash [file]")
	print("Injects inputs at the start of the movie to play from a flash cart.")

def main(file):
	with open(file, "r+b") as target:
		target.seek(HEADER_LENGTH)
		bytes = target.read(len(CMD))
		if bytes == CMD:
			answer = input("This already seem to have a start header. Continue? [y,N]")
			if answer != "y" and answer != "Y":
				return

		target.seek(HEADER_LENGTH)
		data = target.read()
		target.seek(HEADER_LENGTH)
		target.write(CMD)
		target.write(data)
		target.flush()

if len(sys.argv) > 2:
	usage()
elif len(sys.argv) == 2:
	main(sys.argv[1])
else:
	main("inputs.inp")

# Convert Mupen - Converts MUPEN input files into TASRAW files.
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

#Note: This ignores the header, and thus version of the MUPEN recording. Will not work with multi-controller tas's,
# though it would still produce a tas file.

HEADER = b"TASRAW"
CONSOLE = 0x64
VERSION = 0


def usage():
	print("convert_mupen [file] [desctription]")
	print("outputs inputs.inp in the correct format. Description is optional")

def main(input, description):
	descriptionBytes = bytearray(32)
	if description:
		if len(description) > 32:
			description = description[:32]
		descriptionBytes = description.encode("ASCII", "replace").ljust(32, bytearray(1))

	with open(input, "rb") as source, open("inputs.inp", "wb") as target:
		#Standard Header
		target.write(b"TASRAW")
		target.write(bytearray([CONSOLE, VERSION]))
		target.write(descriptionBytes)

		source.seek(0x400)
		current = source.read(4)
		count = 0

		while True:
			bytes = source.read(4)

			if len(bytes) != 4:
				break

			if bytes != current or count == 255:
				target.write(current)
				target.write(bytearray([count]))
				current = bytes
				count = 0
			else:
				count += 1

		target.write(current)
		target.write(bytearray([count]))
		target.flush()


if len(sys.argv) == 2:
	main(sys.argv[1], None)
elif len(sys.argv) == 3:
	main(sys.argv[1], sys.argv[2])
else:
	usage()

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

def printPlayProgress(movie, frame, inputs):
	progress = frame / movie.frames if movie.frames > 0 else 0
	icon = ["|", "/", "-", "\\"][frame % 4]

	line = "{0: >7}/{1} [{3: <50}] {2:.1%} {4}".format(frame, movie.frames, progress, "#" * int(progress * 50), icon)

	print(line, end="", flush=True)
	print("\b" * len(line), end="", flush=False)


def printN64Inputs(movie, frame, inputs):
	display = ["A", "B", "Z", "S", "↑", "↓", "←", "→", "!", "!", "L", "R", "^", "v", "<", ">"].reverse()
	data = inputs[0][0] * 256 + inputs[0][1]

	for x in range(len(display)):
		if not data & (2 ** x):
			display[x] = " " * len(display[x])

	text = "inputs: " + display.join(" ")

	print(text, end=None, flush=True)
	print("\b" * len(text), end=None, flush=False)

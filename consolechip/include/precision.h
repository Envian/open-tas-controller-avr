// Open TAS Controller - A controller emulator for running TAS on hardware.
// Copyright (C) 2019  Russell Small
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#define waitCycles(cycles) switch(cycles % 3) { \
case 2: asm volatile("\tNOP\n"); \
case 1: asm volatile("\tNOP\n"); \
default: { \
	register byte __scratch; \
	asm volatile( \
		"\tLDI %0, %1\n" \
		"WAIT_CYCLES_LOOP%=:\n" \
		"\tDEC %0\n" \
		"\tBRNE WAIT_CYCLES_LOOP%=\n" \
		: "=r" (__scratch) \
		: "i" (cycles / 3) \
		: "cc" \
	); \
}}

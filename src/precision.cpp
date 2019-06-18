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

#include <Arduino.h>

#pragma GCC push_options
#pragma GCC optimize ("O1")

/*
// r0 is the number of nops
FASTRUN volatile void _waitCycles() {
	asm volatile (
"WAIT_CYCLES_METHOD: .global WAIT_CYCLES_METHOD\n"\
		// Delays large numbers with loop
		"SUB r1, r1, #1 \n"\
		"CMP r1, #0 \n"\
		"BNE WAIT_CYCLES_METHOD \n"

		// Delays any remainder
		"ADD PC, PC, r0 \n" \
		"NOP \n" \
		"NOP \n" \
		"NOP \n"
		:
		:
		: "cc", "r0", "r1"
	);
}
*/

#define WAITCYCLES_CALL_COST 15

FASTRUN volatile void _waitCycles(unsigned long duration) {
	asm volatile (
"WAIT_CYCLES_METHOD: .global WAIT_CYCLES_METHOD\n"\
		// Accounts for the cost of this entire method
		"SUB r0, %0 \n"\

		// Figures out how many NOPS we need to delay
		"MOVS r3, #3 \n"\
		"BIC r3, r0 \n"\
		"LSL r3, #1 \n"\

		// Figures out how many loop iterations we need.
		"LSR r0, #2 \n"\

		// Delays large numbers with loop
		"FINE_WAIT_LOOP: \n"\
		"SUB r0, r0, #1 \n"\
		"CMP r0, #0 \n"\
		"BNE FINE_WAIT_LOOP \n"

		// Delays any remainder
		"ADD PC, PC, r3 \n" \
		"NOP \n" \
		"NOP \n" \
		"NOP \n"
		:
		: "i" (WAITCYCLES_CALL_COST)
		: "cc", "r0", "r3"
	);
}

#pragma GCC pop_options

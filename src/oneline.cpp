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
#include "oneline.h"

#include "config.h"
#include "pinregisters.h"

#include "precision.h"

#define CTRL_DIR CONTROLLER_DIR_AB
#define CTRL_OUTPUT CONTROLLER_OUTPUT_AB
#define CTRL_INPUT CONTROLLER_INPUT_AB

#if CONTROLLER_PORT_AB == PB
#define PORT_NUMBER 0x05
#elif CONTROLLER_PORT_AB == PC
#define PORT_NUMBER 0x07
#else
#define PORT_NUMBER 0x0A
#endif

// This is a wrapper class for nintend's one line communication, used by
// the N64 and Gamecube
namespace OneLine {
	void init(const byte mask) {
		CTRL_DIR = 0x00; // All pints input
		CTRL_OUTPUT = 0x00; // Force all inputs low
	}

	void writeBytes(const byte* data, register byte count, register const byte mask) {
		register byte __scratch1, __scratch2, __scratch3;
		asm volatile (
			"rjmp writeloop%= \r\n" \

			// The strange order of the looping is for optimization.
			// This section is the looping logic for the inner loop.
			// This allows the logic to have a consistent length, while maximizing performance
			"byteloop%=: \r\n" \
			"nop \r\n" \
			"nop \r\n" \
			"nop \r\n" \
			"rjmp sendbit%= \r\n" \

			"writeloop%=: \r\n" \
			// Prepares the mask register and gets the next byte to send
			"ldi %[bitmask], 0b10000000 \r\n" \
			"ld %[currentByte], x+ \r\n" \

			// Send a bit here.
			"sendbit%=: \r\n" \
			"mov %[scratch], %[currentByte] \r\n" \
			"and %[scratch], %[bitmask] \r\n" \
			"brne highBit%= \r\n" \
			"nop \r\n" \

			// Send a 0 bit
			"out %[portNumber], %[lowMask] \r\n" \
			// Wait 47 cycles
			"ldi %[scratch], 15 \r\n" \
			"delayLoopLowA%=: \r\n" \
			"dec %[scratch] \r\n" \
			"brne delayLoopLowA%= \r\n" \
			"nop \r\n" \
			"nop \r\n" \

			"out %[portNumber], %[zero] \r\n" \

			// Wait 15 cycles before the next input (includes delay time)
			"nop \r\n" \


			"rjmp bitDone%= \r\n" \
			"highBit%=: \r\n" \

			// Send a 1 bit
			"out %[portNumber], %[lowMask] \r\n" \
			// Wait 15 cycles
			"ldi %[scratch], 5 \r\n" \
			"delayLoopHighA%=: \r\n" \
			"dec %[scratch] \r\n" \
			"brne delayLoopHighA%= \r\n" \

			"out %[portNumber], %[zero] \r\n" \

			// Wait 47 cycles before the next input (includes delay time)
			"ldi %[scratch], 11 \r\n" \
			"delayLoopHighB%=: \r\n" \
			"dec %[scratch] \r\n" \
			"brne delayLoopHighB%= \r\n" \
			"nop \r\n" \
			"nop \r\n" \
			"bitDone%=: \r\n" \

			// Move to the next bit to send
			"lsr %[bitmask] \r\n" \
			"brne byteloop%= \r\n" \

			// Count down and end byte count loop
			"dec %[counter] \r\n" \
			"brne writeloop%= \r\n" \

			// End of loop requires a 2us signal
			"ldi %[scratch], 2 \r\n" \
			"delayLoopLastA%=: \r\n" \
			"dec %[scratch] \r\n" \
			"brne delayLoopLastA%= \r\n" \
			"nop \r\n" \
			"nop \r\n" \

			"out %[portNumber], %[lowMask] \r\n" \

			"ldi %[scratch], 10 \r\n" \
			"delayLoopLastB%=: \r\n" \
			"dec %[scratch] \r\n" \
			"brne delayLoopLastB%= \r\n" \
			"nop \r\n" \

			"out %[portNumber], %[zero] \r\n"
			// outputs (None are real)
			: [counter] "+r" (count), [bitmask] "+r" (__scratch1), [currentByte] "+r" (__scratch2),
			[pointer] "+x" (data), [scratch] "+r" (__scratch3)

			// inputs
			: "[counter]" (count), "[pointer]" (data), [zero] "r" (0),
			[lowMask] "r" (mask), [portNumber] "i" (PORT_NUMBER)

			// Clobbers
			: "cc"
		);
	}

	byte readByte(byte* const mask) {
		// Does GCC optimize this properly with the pointer?
		byte result;
		for (byte x = 0; x < 8; x++) {
			result <<= 1;

			// Always ensure the ports start high so we only detect true falling edges.
			while ((CTRL_INPUT & *mask) != *mask);

			byte input;
			do { input = CTRL_INPUT & *mask; }
			while (input == *mask);

			*mask = (~input & *mask);

			// Not sure how long this delay needs to be, but it doesn't matter too much
			waitCycles(16);

			result |= (CTRL_INPUT & *mask) ? 1 : 0;
		}

		return result;
	}

	void readBytes(byte* dest, const int count, byte mask) {
		for (byte n = 0; n < count; n++) {
			*dest = readByte(&mask);
			dest++;
		}
	}

	void endRead(const byte mask) {
		while ((CTRL_INPUT & mask) != mask);
		while ((CTRL_INPUT & mask) == mask); 
		while ((CTRL_INPUT & mask) != mask);
	}
}

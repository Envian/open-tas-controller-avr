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

#include "commands.h"
#include "config.h"
#include "hardware.h"
#include "precision.h"

#define CTRL_PORT _pinToPort(PIN_ONELINE_CTRL_2)
#define CTRL_DIR _portModeRegister(CTRL_PORT)
#define CTRL_OUTPUT _portOutputRegister(CTRL_PORT)
#define CTRL_INPUT _portInputRegister(CTRL_PORT)

#define CTRLMASK_1 _pinToBitMask(PIN_ONELINE_CTRL_1)
#define CTRLMASK_2 _pinToBitMask(PIN_ONELINE_CTRL_2)
#define CTRLMASK_3 _pinToBitMask(PIN_ONELINE_CTRL_3)
#define CTRLMASK_4 _pinToBitMask(PIN_ONELINE_CTRL_4)

#define CTRL_DIR_PORT _portToModePortNumber(CTRL_PORT)
#define CTRL_INPUT_PORT _portToInputPortNumber(CTRL_PORT)

#define waitForHigh(msk) while((CTRL_INPUT & msk) != msk);
#define waitForLow(msk) while((CTRL_INPUT & msk) == msk);
#define waitForFalling(msk) waitForHigh(msk) waitForLow(msk)
#define waitForRising(msk) waitForLow(msk) waitForHigh(msk)


// This is a wrapper class for nintend's one line communication, used by
// the N64 and Gamecube
namespace OneLine {
	byte controllerMask;
	byte lastInputMask;

	void init() {
		controllerMask = 0;

		CTRL_DIR = 0x00; // All Pins to Input
		CTRL_OUTPUT = 0x00; // Force all inputs low
	}

	void enableController(byte controller) {
		switch (controller) {
			case 0: controllerMask |= CTRLMASK_1; break;
			case 1: controllerMask |= CTRLMASK_2; break;
			case 2: controllerMask |= CTRLMASK_3; break;
			case 3: controllerMask |= CTRLMASK_4; break;
		}
	}

/*
Rise times take over 200ns with a 2k resistor.
These diagrams assume a 16mhz CPU
X====X is the range where readings may take place for each signal.

Diagram: 1 bit
----|                 /-X====X--------------------------------------
    |                /
    |---------------/

Diagram: 0 bit
----|                                                 /-------------
    |                                                /
    |-------------------X====X----------------------/
*/
byte readByte() {
#define CYCLES_AFTER_READ 6
		byte result, mask;
		for (byte bit = 0; bit < 8; bit++) {
			result <<= 1;

			// Previous iterations could get back here while the line is still low.
			waitForHigh(controllerMask);

			// Waits for any to drop low, and captures that bit
			do {
				mask = (CTRL_INPUT & controllerMask);
			}
			while (mask == controllerMask);
			lastInputMask = mask ^ controllerMask;

			// 6 cycles seems to be the theoretical minimum.
			waitCycles(CYCLES_PER_MICRO - CYCLES_AFTER_READ + RISING_EDGE_BUFFER);

			result |= (CTRL_INPUT & lastInputMask) ? 1 : 0;
		}
		return result;
	}

	byte getLastController() {
		switch (lastInputMask) {
			case (byte)CTRLMASK_1: return 0;
			case (byte)CTRLMASK_2: return 1;
			case (byte)CTRLMASK_3: return 2;
			case (byte)CTRLMASK_4: return 3;
			//default: while (true); // This should never run
		}
		return 0;
	}

	void reply(const byte* data, byte count) {
		// It takes _roughly_ 34 cycles to get here. Optimization may change that.
		waitCycles(CYCLES_PER_MICRO * 4 - 32);

		byte __scratch1, __scratch2, __scratch3;
		asm volatile (
			"rjmp writeloop%= \n" \

			// The strange order of the looping is for optimization.
			// This section is the looping logic for the inner loop.
			// This allows the logic to have a consistent length, while maximizing performance
			"byteloop%=: \n" \
			"nop \n" \
			"nop \n" \
			"nop \n" \
			"rjmp sendbit%= \n" \

			"writeloop%=: \n" \
			// Prepares the mask register and gets the next byte to send
			"ldi %[bitmask], 0b10000000 \n" \
			"ld %[currentByte], x+ \n" \

			// Send a bit here.
			"sendbit%=: \n" \
			"mov %[scratch], %[currentByte] \n" \
			"and %[scratch], %[bitmask] \n" \
			"brne highBit%= \n" \
			"nop \n" \

			// Send a 0 bit
			"out %[portNumber], %[lowMask] \n" \
			// Wait 47 cycles
			"ldi %[scratch], 15 \n" \
			"delayLoopLowA%=: \n" \
			"dec %[scratch] \n" \
			"brne delayLoopLowA%= \n" \
			"nop \n" \
			"nop \n" \

			"out %[portNumber], %[zero] \n" \

			// Wait 15 cycles before the next input (includes delay time)
			"nop \n" \


			"rjmp bitDone%= \n" \
			"highBit%=: \n" \

			// Send a 1 bit
			"out %[portNumber], %[lowMask] \n" \
			// Wait 15 cycles
			"ldi %[scratch], 5 \n" \
			"delayLoopHighA%=: \n" \
			"dec %[scratch] \n" \
			"brne delayLoopHighA%= \n" \

			"out %[portNumber], %[zero] \n" \

			// Wait 47 cycles before the next input (includes delay time)
			"ldi %[scratch], 11 \n" \
			"delayLoopHighB%=: \n" \
			"dec %[scratch] \n" \
			"brne delayLoopHighB%= \n" \
			"nop \n" \
			"nop \n" \
			"bitDone%=: \n" \

			// Move to the next bit to send
			"lsr %[bitmask] \n" \
			"brne byteloop%= \n" \

			// Count down and end byte count loop
			"dec %[counter] \n" \
			"brne writeloop%= \n" \

			// End of loop requires a 2us signal
			"ldi %[scratch], 2 \n" \
			"delayLoopLastA%=: \n" \
			"dec %[scratch] \n" \
			"brne delayLoopLastA%= \n" \
			"nop \n" \
			"nop \n" \

			"out %[portNumber], %[lowMask] \n" \

			"ldi %[scratch], 10 \n" \
			"delayLoopLastB%=: \n" \
			"dec %[scratch] \n" \
			"brne delayLoopLastB%= \n" \
			"nop \n" \

			"out %[portNumber], %[zero] \n"
			// outputs (None are real)
			: [counter] "+&r" (count), [bitmask] "=&r" (__scratch1), [currentByte] "=&r" (__scratch2),
			[pointer] "+&x" (data), [scratch] "=&r" (__scratch3)
			// inputs
			: "[counter]" (count), "[pointer]" (data), [zero] "r" (0),
			[lowMask] "r" (lastInputMask), [portNumber] "i" (CTRL_DIR_PORT)

			// Clobbers
			: "cc"
		);
	}

	void readBytes(const byte* buffer, byte max) {
		// TODO: Not Implemented
	}
}

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
#include "hardware.h"
#include "precision.h"
#include "interrupts.h"

#define CTRL_PORT _pinToPort(PIN_ONELINE_CTRL_2)
#define CTRL_DIR _portModeRegister(CTRL_PORT)
#define CTRL_OUTPUT _portOutputRegister(CTRL_PORT)
#define CTRL_INPUT _portInputRegister(CTRL_PORT)

#define CTRLMASK_1 _pinToBitMask(PIN_ONELINE_CTRL_1)
#define CTRLMASK_2 _pinToBitMask(PIN_ONELINE_CTRL_2)
#define CTRLMASK_3 _pinToBitMask(PIN_ONELINE_CTRL_3)
#define CTRLMASK_4 _pinToBitMask(PIN_ONELINE_CTRL_4)

#if CTRL_PORT == PB
#define PORT_NUMBER 0x05
#elif CTRL_PORT == PC
#define PORT_NUMBER 0x07
#else
#define PORT_NUMBER 0x0A
#endif

#define waitForHigh(msk) while((CTRL_INPUT & msk) != msk);
#define waitForLow(msk) while((CTRL_INPUT & msk) == msk);
#define waitForFalling(msk) waitForHigh(msk) waitForLow(msk)
#define waitForRising(msk) waitForLow(msk) waitForHigh(msk)

// This is a wrapper class for nintend's one line communication, used by
// the N64 and Gamecube
namespace OneLine {
	byte controllerMask;
	byte lastInputMask;

	byte init(const byte mask) {
		Interrupts::disableRegisters();
		controllerMask = 0;
		controllerMask |= (mask & 0x08) ? CTRLMASK_4 : 0;
		controllerMask |= (mask & 0x04) ? CTRLMASK_3 : 0;
		controllerMask |= (mask & 0x02) ? CTRLMASK_2 : 0;
		controllerMask |= (mask & 0x01) ? CTRLMASK_1 : 0;

		CTRL_DIR = 0x00; // All Pins to Input
		CTRL_OUTPUT = 0x00; // Force all inputs low

		byte controllerCount = 0;
		for (byte bit = 0; bit < 8; bit++) {
			controllerCount += (mask & (1 << bit)) ? 1 : 0;
		}

		return controllerCount;
	}

	byte readCommand() {
		byte result;
		for (byte bit = 0; bit < 8; bit++) {
			result <<= 1;

			// Previous iterations could get back here while the line is still low.
			waitForHigh(controllerMask);

			// Waits for any to drop low, and captures that bit
			do {lastInputMask = CTRL_INPUT | ~controllerMask; }
			while (lastInputMask == 0xFF);

			// Not sure how long this delay needs to be, but it doesn't matter too much
			waitCycles(16);

			result |= (CTRL_INPUT & controllerMask) ? 1 : 0;
		}
		return result;
	}

	byte getLastController() {
		switch (lastInputMask) {
			case (byte)~CTRLMASK_1: return 0;
			case (byte)~CTRLMASK_2: return 1;
			case (byte)~CTRLMASK_3: return 2;
			case (byte)~CTRLMASK_4: return 3;
			//default: while (true); // This should never run
		}
		return 0;
	}

	void reply(const byte* data, register byte count) {
		byte replyMask = ~lastInputMask;
		//waitForLow(replyMask);
		waitForHigh(replyMask);
		waitCycles(32);

		// Note: Takes about 30 cycles to get here from readCommand.
		register byte __scratch1, __scratch2, __scratch3;

#pragma GCC diagnostic ignored "-Wuninitialized"
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
			: [counter] "+r" (count), [bitmask] "+r" (__scratch1), [currentByte] "+r" (__scratch2),
			[pointer] "+x" (data), [scratch] "+r" (__scratch3)
			// inputs
			: "[counter]" (count), "[pointer]" (data), [zero] "r" (0),
			[lowMask] "r" (replyMask), [portNumber] "i" (PORT_NUMBER)

			// Clobbers
			: "cc"
		);
#pragma GCC diagnostic pop
	}

	int getReadWriteAddress() {
		// TODO: Not Implemented
		return 0;
	}

	void readBytes(const byte* buffer, byte max) {
		// TODO: Not Implemented
	}
/*
	static inline byte _readByte(const byte mask) {
		byte result;
		for (byte x = 0; x < 8; x++) {
			result <<= 1;

			waitForFalling(mask);
			waitCycles(16);
			result |= (CTRL_INPUT & mask) ? 1 : 0;
		}

		return result;
	}

	void readBytes(byte* dest, const byte count, const byte mask) {
		for (byte n = 0; n < count; n++) {
			*dest = _readByte(mask);
			dest++;
		}
	}

	void discardBits(const int bits, const byte mask) {
		for (int x = 0; x < bits; x++) {
			waitForFalling(mask);
		}
	}
	*/
}

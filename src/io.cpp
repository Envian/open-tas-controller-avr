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

#include "pinout.h"
#include "error.h"
#include "precision.h"

#define CONSOLE_RELEASE() CONSOLE_PINMODE_REG &= ~CONSOLE_PINMODE_MASK
#define CONSOLE_LOWER() CONSOLE_PINMODE_REG |= CONSOLE_PINMODE_MASK
#define UNIT_WAIT 46

FASTRUN unsigned long readBits(int count) {
	unsigned long value = 0;
	for (int x = 0; x < count; x++) {
		value <<= 1;
		while (digitalReadFast(PIN_CONSOLE) == LOW) { }
		while (digitalReadFast(PIN_CONSOLE) == HIGH) { }
		waitCycles(UNIT_WAIT * 2);
		value |= digitalReadFast(PIN_CONSOLE) ? 1 : 0;
	}
	return value;
}

FASTRUN void writeBits(unsigned long bits, int count) {
	for (count--; count >= 0; count--) {
		CONSOLE_LOWER();
		if (bitRead(bits, count)) {
			waitCycles(UNIT_WAIT);
			CONSOLE_RELEASE();
			waitCycles(UNIT_WAIT * 3);
		} else {
			waitCycles(UNIT_WAIT * 3);
			CONSOLE_RELEASE();
			waitCycles(UNIT_WAIT);
		}
	}

	// Final control bit
	CONSOLE_LOWER();
	waitCycles(UNIT_WAIT * 2);
	CONSOLE_RELEASE();
}

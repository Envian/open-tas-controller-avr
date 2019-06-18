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

#include "error.h"
#include "io.h"
#include "precision.h"

FASTRUN void sendButton(unsigned long buttons) {
	noInterrupts();
	while (true) {
		unsigned long cmd = readBits(8);

		// Delays long enough for the console to send its control bit
		waitCycles(110);
		waitCycles(110);

		switch (cmd) {
			// Some consoles ask with FF (SM64 US), others 00 (Army Men Sarge's Heros 2). 
			case 0x00:
			case 0xFF:
				writeBits(0b000000000000000010100000, 24);
				break;
			case 1:
				writeBits(buttons, 32);
				interrupts();
				return;
		}
	}
}

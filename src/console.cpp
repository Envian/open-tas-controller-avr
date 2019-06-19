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
		int cmd = readBits(8);

		switch (cmd) {
			case 0x00: // Controller status
			case 0xFF: // Reset Controller
				endRead();
				writeBits(0x050000, 24);
				break;
			case 0x01: // Poll Inputs
				endRead();
				writeBits(buttons, 32);
				interrupts();
				return;
			case 0x02: // Read
				readBits(16); // Reads two extra address bytes.
				endRead();
				writeZeros(33 * 8);
				break;
			case 0x03:
				int address = readBits(16) >> 5;
				readBits(32 * 8);
				endRead();
				// TODO: respond here.
				break;
		}
	}
}

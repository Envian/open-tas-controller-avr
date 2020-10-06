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
#include "n64.h"
#include "config.h"
#include "pinregisters.h"

#include "helpers.h"
#include "oneline.h"
#include "precision.h"
#include "interrupts.h"

// N64 uses pin A on each controller, and nothing else.
#define CTRLMASK_1 (_pinToBitMask(CONTROLLER1A))
#define CTRLMASK_2 (_pinToBitMask(CONTROLLER2A))
#define CTRLMASK_3 (_pinToBitMask(CONTROLLER3A))
#define CTRLMASK_4 (_pinToBitMask(CONTROLLER4A))
#define CTRLMASK_ALL (CTRLMASK_1 & CTRLMASK_2 & CTRLMASK_3 & CTRLMASK_4)

#define CONTROLLER_COUNT 4
#define INPUT_PACKAGE_SIZE 4

namespace N64 {
	const byte zeros[33] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	byte buffer[4];
	byte inputs[INPUT_PACKAGE_SIZE] = {0, 0, 0, 0};
	const byte controllerStatus[] = { 0x05, 0x00, 0x00 };

	void init() {
		Interrupts::disableRegisters();
		OneLine::init(CTRLMASK_ALL);
	}

	void sendInput(byte* input, const byte controllerMask, const byte allMasks) {
		while (true) {
			byte mask = allMasks;
			switch (OneLine::readByte(&mask)) {
			case 0x00: // Controller Status
			case 0xFF: // Reset Controller
				waitForFalling(mask);
				OneLine::writeBytes(controllerStatus, 3, mask);
				break;
			case 0x01: // Get Inputs
				waitForFalling(mask);
				if (mask == controllerMask) {
					OneLine::writeBytes(input, 4, mask);
					return;
				}
				break;
			case 0x02: // Read from pack
				OneLine::readBytes(buffer, 2, mask);
				waitForFalling(mask);
				OneLine::writeBytes(zeros, 16, mask);
				break;
			case 0x03: // Write to pack
				break;
			}
		}
	}

	void playback() {
		init();

		const byte controllerCount = Helpers::readBlocking();

		while (true) {
			Serial.write(INPUT_PACKAGE_SIZE);
			Helpers::readBytesBlocking(inputs, INPUT_PACKAGE_SIZE);

			if ((inputs[0] & inputs[1] & inputs[2] & inputs[3]) == 0xFF) {
				return;
			}

			noInterrupts();
			sendInput(&inputs[0], CTRLMASK_1, CTRLMASK_1);
			interrupts();
		}
	}

	void record() {
		init();

		const byte controllerCount = Helpers::readBlocking();
		byte currentMask = CTRLMASK_1;

		noInterrupts();

		DDRB = 0xFF;

		while (true) {
			byte mask = currentMask;
			switch (OneLine::readByte(&mask)) {
			case 0x00: // Controller Status
			case 0xFF: // Reset Controller
				// Discards 3 bytes plus the control bits
				OneLine::discardBits(26, mask);
				break;
			case 0x01: // Get Inputs
				waitForFalling(mask);
				OneLine::readBytes(buffer, 4, mask);
				waitForFalling(mask);
				Serial.write(buffer, 4);
				break;
			case 0x02: // Read from pack
				// Discards 2 additional address bytes, 33 data bytes, and 2 control bits
				OneLine::discardBits(35 * 8 + 2, mask);
				break;
			case 0x03: // Write to pack
				// Discards 32 data bytes, 1 response byte, and 2 control bits
				OneLine::discardBits(34 * 8 + 2, mask);
				break;
			}
		}
	}
}

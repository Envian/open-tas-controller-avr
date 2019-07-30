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

#include "n64.h"

#include <Arduino.h>
#include "config.h"
#include "pinregisters.h"

#include "oneline.h"
#include "precision.h"
#include "interrupts.h"
#include "error.h"

// N64 uses pin A on each controller, and nothing else.
#define CTRLMASK_1 (_pinToBitMask(CONTROLLER1A))
#define CTRLMASK_2 (_pinToBitMask(CONTROLLER2A))
#define CTRLMASK_3 (_pinToBitMask(CONTROLLER3A))
#define CTRLMASK_4 (_pinToBitMask(CONTROLLER4A))
#define CTRLMASK_ALL (CTRLMASK_1 & CTRLMASK_2 & CTRLMASK_3 & CTRLMASK_4)

#define CONTROLLER_COUNT 4
#define INPUT_PACKAGE_SIZE 4

namespace N64 {
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
				OneLine::endRead(mask);
				OneLine::writeBytes(controllerStatus, 3, mask);
				break;
			case 0x01: // Get Inputs
				OneLine::endRead(mask);
				if (mask == controllerMask) {
					OneLine::writeBytes(input, 4, mask);
					return;
				}
				break;
			case 0x02: // Read from pack
				break;
			case 0x03: // Write to pack
				break;
			}
		}
	}

	void playback() {
		init();

		while (!Serial.available());
		const byte controllerCount = Serial.read();
		// Only support 1 controller for now
		if (controllerCount != 1) {
			error(ERROR_UNSUPPORTED_CONTROLLERS);
		}

		while (true) {
			Serial.write(INPUT_PACKAGE_SIZE);
			while (Serial.available() < INPUT_PACKAGE_SIZE);
			Serial.readBytes(&inputs[0], INPUT_PACKAGE_SIZE);

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

		while (!Serial.available());
		const byte controllerCount = Serial.read();
		// Only support 1 controller for now
		if (controllerCount != 1) {
			error(ERROR_UNSUPPORTED_CONTROLLERS);
		}

		byte buffer[4];

		while (true) {
			noInterrupts();
			byte currentMask = CTRLMASK_1;
			while (true) {
				byte mask = currentMask;
				switch (OneLine::readByte(&mask)) {
				case 0x00: // Controller Status
				case 0xFF: // Reset Controller
					OneLine::endRead(mask);
					OneLine::readBytes(buffer, 3, mask);
					OneLine::endRead(mask);
					break;
				case 0x01: // Get Inputs
					OneLine::endRead(mask);
					OneLine::readBytes(buffer, 4, mask);
					OneLine::endRead(mask);
					Serial.write(buffer, 4);
					break;
				case 0x02: // Read from pack
					break;
				case 0x03: // Write to pack
					break;
				}
			}
			interrupts();
		}
	}
}

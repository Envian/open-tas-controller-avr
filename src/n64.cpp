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
#include "hardware.h"
#include "commands.h"
#include "helpers.h"
#include "precision.h"

#include "oneline.h"

// N64 uses pin A on each controller, and nothing else.
#define CTRLMASK_1 (_pinToBitMask(PIN_ONELINE_CTRL_1))
#define CTRLMASK_2 (_pinToBitMask(PIN_ONELINE_CTRL_2))
#define CTRLMASK_3 (_pinToBitMask(PIN_ONELINE_CTRL_3))
#define CTRLMASK_4 (_pinToBitMask(PIN_ONELINE_CTRL_4))
#define CTRLMASK_ALL (CTRLMASK_1 & CTRLMASK_2 & CTRLMASK_3 & CTRLMASK_4)

#define MAX_CONTROLLERS 4
#define INPUT_PACKAGE_SIZE 4
#define STATUS_SIZE 3

namespace N64 {
	byte ZERO_PACKET[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	byte inputBuffer[INPUT_PACKAGE_SIZE * MAX_CONTROLLERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	byte statusBuffer[STATUS_SIZE * MAX_CONTROLLERS] = { 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00 };
	byte controllerCount;
	byte packetSize;

	void sendPacket() {
		byte controllersUpdated = 0;
		readBytesBlocking(inputBuffer, packetSize);

		noInterrupts();
		// Send inputs
		do {
			switch (OneLine::readCommand()) {
			case 0x00: // Controller Status
			case 0xFF: // Reset Controller
				OneLine::reply(statusBuffer + OneLine::getLastController() * STATUS_SIZE, STATUS_SIZE);
				break;
			case 0x01: // Get Inputs
				OneLine::reply(inputBuffer + OneLine::getLastController() * INPUT_PACKAGE_SIZE, INPUT_PACKAGE_SIZE);
				controllersUpdated++;
				break;
			case 0x02: // Read from pack
				// Ignore the next 2 bytes.
				OneLine::readCommand();
				OneLine::readCommand();
				OneLine::reply(ZERO_PACKET, 16);
				break;
			case 0x03: // Write to pack
				break;
			}
		}
		while (controllersUpdated < controllerCount);
		interrupts();

		Serial.write(CMD_INPUT_SENT);
	}



	void handleCommands() {
		while (true) {
			switch (readBlocking()) {
			case 0x00: break;
			case 0x81: error(ERR_UNSUPPORTED_CONSOLE_CMD); break; // For use with mempacks.
			case 0x82: error(ERR_UNSUPPORTED_CONSOLE_CMD); break; // Configure Console (2)
			case 0x83: error(ERR_UNSUPPORTED_CONSOLE_CMD); break; // Configure Console (3)
			case 0x84: error(ERR_UNSUPPORTED_CONSOLE_CMD); break; // Configure Console (4)
			case 0x8A: sendPacket(); break; // Send Input Packet.
			case 0x8C: error(ERR_UNSUPPORTED_CONSOLE_CMD); break; // Begin Recording.
			case 0x8E: error(ERR_UNSUPPORTED_CONSOLE_CMD); break; // Reset Console.
			case 0x8F: return; // Exit Console mode
			default: Serial.write(CMD_UNKNOWN);
			}
		}
	}

	void connect() {
		// Size byte is fixed for n64.
		assert(readBlocking() == STATUS_SIZE * MAX_CONTROLLERS + 1, ERR_CONSOLE_CONFIG);

		// First byte is input packet size.
		packetSize = readBlocking();
		assert(packetSize <= INPUT_PACKAGE_SIZE * MAX_CONTROLLERS, ERR_CONSOLE_CONFIG);

		// 12 bytes representing controller config.
		readBytesBlocking(statusBuffer, STATUS_SIZE * MAX_CONTROLLERS);

		// Reads config buffer
		byte controllerFlags = 0;
		controllerCount = 0;

		for (byte controller = 0; controller < MAX_CONTROLLERS; controller++) {
			if (statusBuffer[controller] == 0x05) {
				controllerCount++;
				controllerFlags |= 1 << controller;
			}
		}

		OneLine::init(controllerFlags);

		enablePrecisionMode();
		handleCommands();
		disablePrecisionMode();
	}

	void record() {

	// 	const byte controllerCount = Helpers::readBlocking();
	// 	byte currentMask = CTRLMASK_1;
	//
	// 	noInterrupts();
	//
	// 	DDRB = 0xFF;
	//
	// 	while (true) {
	// 		byte mask = currentMask;
	// 		switch (OneLine::readByte(&mask)) {
	// 		case 0x00: // Controller Status
	// 		case 0xFF: // Reset Controller
	// 			// Discards 3 bytes plus the control bits
	// 			OneLine::discardBits(26, mask);
	// 			break;
	// 		case 0x01: // Get Inputs
	// 			waitForFalling(mask);
	// 			OneLine::readBytes(buffer, 4, mask);
	// 			waitForFalling(mask);
	// 			Serial.write(buffer, 4);
	// 			break;
	// 		case 0x02: // Read from pack
	// 			// Discards 2 additional address bytes, 33 data bytes, and 2 control bits
	// 			OneLine::discardBits(35 * 8 + 2, mask);
	// 			break;
	// 		case 0x03: // Write to pack
	// 			// Discards 32 data bytes, 1 response byte, and 2 control bits
	// 			OneLine::discardBits(34 * 8 + 2, mask);
	// 			break;
	// 		}
	// 	}
	}
}

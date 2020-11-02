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
	const byte ZERO_PACKET[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	byte inputBuffer[INPUT_PACKAGE_SIZE * MAX_CONTROLLERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	byte statusBuffer[STATUS_SIZE * MAX_CONTROLLERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	byte controllerCount = 0;
	byte packetSize = 0;
	byte controllerFlags = 0;

	void setPacketSize() {
		packetSize = readBlocking();
		assert(packetSize <= INPUT_PACKAGE_SIZE * MAX_CONTROLLERS, ERR_CONSOLE_CONFIG);
	}

	void setControllerMode() {
		byte controller = readBlocking();
		assert(controller <= MAX_CONTROLLERS, ERR_CONSOLE_CONFIG);

		readBytesBlocking(statusBuffer + controller * STATUS_SIZE, STATUS_SIZE);
		OneLine::enableController(controller);
		controllerFlags |= 1 << controller;

		controllerCount = 0;
		for (byte bit = 0; bit < MAX_CONTROLLERS; bit++) {
			controllerCount += (controllerFlags & 1 << bit) ? 1 : 0;
		}
	}

	void sendPacket() {
		byte controllersUpdated = 0;
		readBytesBlocking(inputBuffer, packetSize);

		noInterrupts();
		// Send inputs
		while (controllersUpdated < controllerCount)
		{
			byte cmd = OneLine::readByte();
			switch (cmd) {
			case 0x00: // Controller Status
			case 0xFF: // Reset Controller
				OneLine::reply(statusBuffer + OneLine::getLastController() * STATUS_SIZE, STATUS_SIZE);
				break;
			case 0x01: // Get Inputs
				OneLine::reply(inputBuffer + OneLine::getLastController() * INPUT_PACKAGE_SIZE, INPUT_PACKAGE_SIZE);
				controllersUpdated++;
				break;
			// case 0x02: // Read from pack
			// 	OneLine::readByte();
			// 	OneLine::readByte();
			// 	OneLine::reply(ZERO_PACKET, 16);
			// 	break;
			// case 0x03: // Write to pack
			// 	break;
			default:
				error(ERR_UNSUPPORTED_CONSOLE_CMD, cmd);
			}
		}
		interrupts();

		Serial.write(CMD_INPUT_SENT);
	}

	void record() {
	}

	void handleCommands() {
		while (true) {
			switch (readBlocking()) {
			case 0x00: break;

			case 'c': error(ERR_BAD_CONSOLE); break; // Connect to Console
			case 'x': return; // Exit Console Mode
			case 'r': record(); break; // Record

			case 0x80: sendPacket(); break;
			case 0x81: setPacketSize(); break;
			case 0x82: setControllerMode(); break;
			default: Serial.write(CMD_UNKNOWN);
			}
		}
	}

	void connect() {
		OneLine::init();
		controllerCount = 0;
		packetSize = 0;
		controllerFlags = 0;

		enablePrecisionMode();
		handleCommands();
		disablePrecisionMode();
	}
}

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

#include "config.h"
#include "commands.h"
#include "helpers.h"

#include "n64.h"

void connectConsole(byte console) {
	switch (console) {
#ifdef N64_SUPPORT
	// byte 0: config packet size (always 13).
	// byte 1: input packet size.
	// bytes 2-13: controller config data.
	case CONSOLE_N64: N64::connect(); break;
#endif
	default:
		error(ERR_BAD_CONSOLE);
	}
}

void setup() {
	Serial.begin(SERIAL_BAUD);
	info(STR_STARTUP);
}

void loop() {
	switch (readBlocking()) {
	case 0x0: break; // Special: NOP

// Text Commands
	case '?': info(STR_HELP); break;
	case 'd': info(STR_DESCRIPTION); break;
	case 'v': info(STR_VERSION); break;

// Binary Commands
	case 0x80: connectConsole(readBlocking()); break; // Connect to Console.
	case 0x81: error(ERR_NO_CONSOLE); break; // Configure Console (1)
	case 0x82: error(ERR_NO_CONSOLE); break; // Configure Console (2)
	case 0x83: error(ERR_NO_CONSOLE); break; // Configure Console (3)
	case 0x84: error(ERR_NO_CONSOLE); break; // Configure Console (4)
	case 0x8A: error(ERR_NO_CONSOLE); break; // Send Input Packet.
	case 0x8C: error(ERR_NO_CONSOLE); break; // Begin Recording.
	case 0x8D: error(ERR_NO_CONSOLE); break; // End Recording.
	case 0x8E: error(ERR_NO_CONSOLE); break; // Reset Console.
	case 0x8F: break; // Exit Console mode

	// Unknown commands. send ?
	default: Serial.write(CMD_UNKNOWN);
	}
}

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

void connectConsole() {
	char console[3];
	readBytesBlocking(console, 3);

#ifdef N64_SUPPORT
	if ((console[0] == 'n' || console[0] == 'N') && console[1] == '6' && console[2] == '4') {
		N64::connect();
	} else
#endif
	{
		error(ERR_BAD_CONSOLE);
	}
}

void setup() {
	Serial.begin(SERIAL_BAUD);
	info(STR_STARTUP);
}

void loop() {
	switch (readBlocking()) {
	case 0x00: break; // Special: NOP

// Text Commands
	case '?': info(STR_HELP); break;
	case 'd': info(STR_DESCRIPTION); break;
	case 'v': info(STR_VERSION); break;

// Manul Commands
	case 'c': connectConsole(); break; // Connect to Console
	case 'x': break; // Exit Console Mode
	case 'r': error(ERR_NO_CONSOLE); break; // Record

// Binary Commands
	case 0x80: // Send Input Packet.
	case 0x81: // Generic Console Command (Binary)
	case 0x82: // Generic Console Command (Binary)
	case 0x83: // Generic Console Command (Binary)
	case 0x84: // Generic Console Command (Binary)
	case 0x85: // Generic Console Command (Binary)
	case 0x86: // Generic Console Command (Binary)
	case 0x87: // Generic Console Command (Binary)
	case 0x88: // Generic Console Command (Binary)
	case 0x89: // Generic Console Command (Binary)
	case 0x8A: // Generic Console Command (Binary)
	case 0x8B: // Generic Console Command (Binary)
	case 0x8C: // Generic Console Command (Binary)
	case 0x8D: // Generic Console Command (Binary)
	case 0x8E: // Generic Console Command (Binary)
	case 0x8F: // Generic Console Command (Binary)
		error(ERR_NO_CONSOLE); break;

	// Unknown commands. send ?
	default: Serial.write(CMD_UNKNOWN);
	}
}

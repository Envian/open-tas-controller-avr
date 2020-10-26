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

#pragma once
#include <Arduino.h>

#define assert(val, msg) if (!(val)) error(msg);

enum Responses : byte {
	// Ignored by the host.
	CMD_NOOP = 0, // Simply ignored by the host.

	// Sends an info message to the user on the host. No response expected.
	CMD_INFO = '\n',

	// Sent when an unknown command is received.
	CMD_UNKNOWN = '?',

	// Sent when the last received packet (0x8A) has been sent to the console.
	CMD_INPUT_SENT = 0x8B,

	// Host must reply with CMD_WARN_ACK or CMD_EXIT, otherwise an INVALID_RESPONSE
	// error will be thrown.
	CMD_WARN = 0xFA, // Followed by 0 terminated string.

	// Notifies the user of an error, then enters an infinite loop until reset.
	CMD_ERROR = 0xFF, // Followed by a 0 terminated string.
};

#define CONSOLE_N64 0x40

void info(const char* msg);
void warn(const char* msg);
void error(const char* msg);

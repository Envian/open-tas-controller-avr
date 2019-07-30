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
#include "config.h"

#define VERSION 0

enum Console : byte {
	CONSOLE_N64 = 0,
};

enum PlaybackMode : byte {
	FLAG_PLAYBACK = 1 << 6,
	FLAG_RECORD = 1 << 7,

	N64_PLAY = CONSOLE_N64 | FLAG_PLAYBACK,
	N64_RECORD = CONSOLE_N64 | FLAG_RECORD
};

void sendHeader();
void runConsole(PlaybackMode console);

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
#include "consoles.h"

#include "config.h"
#include "n64.h"
#include "helpers.h"

void playback() {
	switch ((Console)Helpers::readBlocking()) {
#ifdef N64_SUPPORT
	case CONSOLE_N64: N64::playback(); break;
#endif
	default: Serial.write(0xFF);
	}
}


void record() {
	switch ((Console)Helpers::readBlocking()) {
#ifdef N64_SUPPORT
	case CONSOLE_N64: N64::record(); break;
#endif
	default: Serial.write(0xFF);
	}
}

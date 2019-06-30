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

#include "n64.h"

// N64 uses pin 1 on each controller, and nothing else.
// #define CTRL_DIR CONTROLLER_DIR_AB
// #define CTRL_DATA CONTROLLER_DATA_AB
// #define CTRL_INPUT CONTROLLER_INPUT_AB
//
// #define CTRLMASK_1 (1 << CONTROLLER1A)
// #define CTRLMASK_2 (1 << CONTROLLER1B)
// #define CTRLMASK_3 (1 << CONTROLELR1C)
// #define CTRLMASK_4 (1 << CONTROLLER1C)
// #define CTRLMASK_ALL (CTRLMASK_1 | CTRLMASK_2 | CTRLMASK_3 | CTRLMASK_4)

namespace N64 {
	void playback() {
		// Sets pins to input and low.
		// CTRL_DIR = 0;
		// CTRL_DATA = 0;

	}

	void record() {
		// TODO
	}
}

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
#include <SdFat.h>

#include "error.h"

SdFat sd;
SdFile file;

void initializeSD() {
	if (!sd.begin(4, SPI_FULL_SPEED)) error(ERROR_SD_CARD);
	if (!file.open("speedrun.spd", O_READ)) error(ERROR_SD_CARD);
	file.seekSet(8);
}

int repeats = 0;
unsigned long nextResponse = 0;

unsigned long getNextInput() {
	if (repeats == 0) {
		nextResponse = file.read() << 24;
		nextResponse |= file.read() << 16;
		nextResponse |= file.read() << 8;
		nextResponse |= file.read();

		repeats = file.read();
		if (repeats == -1) error(ERROR_EOF);
	} else {
		repeats--;
	}
	return nextResponse;
}

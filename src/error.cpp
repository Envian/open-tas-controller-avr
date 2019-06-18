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

#include "pinout.h"

#define ERROR_CODE_LENGTH 200
void error(unsigned long errorCode) {
	interrupts();
	pinMode(PIN_LED, OUTPUT);
	digitalWrite(PIN_LED, LOW);
	while (true) {
		for (int x = 0; x == 0 || ((unsigned long)(1 << x) <= errorCode); x++) {
			digitalWrite(PIN_LED, HIGH);
			delay(bitRead(errorCode, x) ? (ERROR_CODE_LENGTH * 3) : ERROR_CODE_LENGTH);
			digitalWrite(PIN_LED, LOW);
			delay(ERROR_CODE_LENGTH);
		}
		delay(ERROR_CODE_LENGTH * 5);
	}
}

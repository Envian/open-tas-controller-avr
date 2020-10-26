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
#include "commands.h"

#include "config.h"
#include "precision.h"

void printString(const char* string) {
	char letter;

	Serial.write('\n');
	do {
		letter = pgm_read_byte_near(string);
		Serial.write(letter);
		string++;
	} while (letter);
}

void info(const char* msg) {
	// printString() will prefix the string with a newline.
	if (CMD_INFO != '\n') {
		Serial.write(CMD_INFO);
	}
	printString(msg);
}

void warning(const char* msg) {
	Serial.write(CMD_WARN);
	printString(msg);
}

void error(const char* msg) {
	interrupts();
	disablePrecisionMode();

	// This loop floods the host with commands to, hopefully, bypass any incopmlete data packets.
	for (int x = 0; x < 512; x++) {
		Serial.write(CMD_NOOP);
		waitCycles(512);
	}
	delay(100);
	Serial.write(CMD_ERROR);
	printString(msg);

	DDRB = 0b00100000;
	while (true) {
		PORTB = 0b00100000;
		delay(500);
		PORTB = 0;
		delay(500);
	}
}

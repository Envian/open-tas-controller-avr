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
#include "precision.h"

byte EIMSK_OLD, PCICR_OLD, TIMSK0_OLD, TIMSK1_OLD, TIMSK2_OLD;
bool precisionMode = false;

void enablePrecisionMode() {
	precisionMode = true;
	EIMSK_OLD = EIMSK; EIMSK = 0; // Disables hardware pin interrupts
	PCICR_OLD = PCICR; PCICR = 0; // Disables pin change interrupts

	// Disables timer interrupts.
	TIMSK0_OLD = TIMSK0; TIMSK0 = 0;
	TIMSK1_OLD = TIMSK1; TIMSK1 = 0;
	TIMSK2_OLD = TIMSK2; TIMSK2 = 0;
}

void disablePrecisionMode() {
	if (precisionMode) {
		EIMSK = EIMSK_OLD;
		PCICR = PCICR_OLD;
		TIMSK0 = TIMSK0_OLD;
		TIMSK1 = TIMSK1_OLD;
		TIMSK2 = TIMSK2_OLD;
	}
}

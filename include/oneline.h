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
#include "pinregisters.h"

#define CTRL_INPUT CONTROLLER_INPUT_AB

#define waitForHigh(msk) while((CTRL_INPUT & msk) != msk);
#define waitForLow(msk) while((CTRL_INPUT & msk) == msk);
#define waitForFalling(msk) waitForHigh(msk) waitForLow(msk)

namespace OneLine {
	void init(const byte mask);
	void writeBytes(const byte* data, byte count, const byte mask) ;
	byte readByte(byte* const mask) ;
	void readBytes(byte* dest, const int count, const byte mask);
}

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

// PINS
#define PIN_MODE 0
#define PIN_LED 13

// Console pin needs extra defines to go fast
#define PIN_CONSOLE 2
#define CONSOLE_PINMODE_REG CORE_PIN2_DDRREG
#define CONSOLE_PINMODE_MASK CORE_PIN2_BITMASK

#if PIN_CONSOLE == 17
#error "Don't use pin 17. It'll fry your N64"
#endif

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

// Guess we don't have these defined.
#define PB 2
#define PC 3
#define PD 4

// Why doesn't arduino include these macros?
// These are set up for Arduino Nanos - Atmega 328p

#define _pinToPort(p) (((p) <= 7) ? PD : (((p) <= 13) ? PB : (((p) <= 21) ? PC : NOT_A_PORT)))
#define _pinToBitMask(p) (((p) <= 13) ? (1 << ((p) % 8)) : (1 << ((p) - 14)))

#define _portModeRegister(p) (*(((p) == PB) ? (&DDRB) : (((p) == PC) ? (&DDRC) : (((p) == PD) ? (&DDRD) : (NOT_A_PORT)))))
#define _portInputRegister(p) (*(((p) == PB) ? (&PINB) : (((p) == PC) ? (&PINC) : (((p) == PD) ? (&PIND) : (NOT_A_PORT)))))
#define _portOutputRegister(p) (*(((p) == PB) ? (&PORTB) : (((p) == PC) ? (&PORTC) : (((p) == PD) ? (&PORTD) : (NOT_A_PORT)))))

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

#include "hardware.h"
#define __STR(val) #val
#define STR(val) __STR(val)

/*******************************************************************************
*                                   General                                    *
*******************************************************************************/
#define SERIAL_BAUD 250000

/*******************************************************************************
*                                 Nintendo 64                                  *
*******************************************************************************/

// Communication is done through a single wire per controller, pulled up to 3v3.
// Protection Circuitry is recommended, but not strictly necessary.
#define N64_SUPPORT


#ifdef N64_SUPPORT

// Controller Pins for both N64 and GCN (Must be same register)
#define PIN_ONELINE_CTRL_1 PIN_A0
#define PIN_ONELINE_CTRL_2 PIN_A1
#define PIN_ONELINE_CTRL_3 PIN_A2
#define PIN_ONELINE_CTRL_4 PIN_A3

#endif // N64_SUPPORT

/*******************************************************************************
*                                 Misc Values                                  *
*******************************************************************************/

#define VERSION 0

/*******************************************************************************
*                        Validation & Calculated Values                        *
*******************************************************************************/

#ifdef N64_SUPPORT

#if _pinToPort(PIN_ONELINE_CTRL_1) != _pinToPort(PIN_ONELINE_CTRL_2) || \
	_pinToPort(PIN_ONELINE_CTRL_1) != _pinToPort(PIN_ONELINE_CTRL_3) || \
	_pinToPort(PIN_ONELINE_CTRL_1) != _pinToPort(PIN_ONELINE_CTRL_4)
#error N64 & GCN require all controller pins to be on the same register.
#endif

#endif

// Ensures strings are loaded for most files.
#include "strings.h"

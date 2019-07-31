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

#include "pinregisters.h"

/*******************************************************************************
*                                   General                                    *
*******************************************************************************/
#define SERIAL_BAUD 500000
#define PIN_LED 13

/*******************************************************************************
*                                   Features                                   *
*******************************************************************************/

// Controller count isn't used by the TAS Chip, but will be sent to the
// controlling software.
#define CONTROLLERS_5V 1
#define CONTROLLERS_3V3 1

// Defines supported consoles.
#define N64_SUPPORT

// Set to true if the N64/GCN has protection circuitry
#define ONELINE_PROTECTED true

/*******************************************************************************
*                                     Pins                                     *
*******************************************************************************/
// Console Pins. Pins A and B must be on the same port. Pin C will be on another.
#define CONTROLLER1A PIN_A0
#define CONTROLLER1B PIN_A1
#define CONTROLLER2A PIN_A2
#define CONTROLLER2B PIN_A3
#define CONTROLLER3A PIN_A4
#define CONTROLLER3B PIN_A5
#define CONTROLLER4A PIN_A6
#define CONTROLLER4B PIN_A7

// Pin C for each controller is on a different pin set than A and B
#define CONTROLLER1C 8
#define CONTROLLER2C 9
#define CONTROLLER3C 10
#define CONTROLLER4C 11

/*******************************************************************************
*                        Common Values & Sanity Checks                         *
*******************************************************************************/

// Don't modify any of these
#define VERSION 0

#define CONTROLLER_PORT_AB (_pinToPort(CONTROLLER1A))
#define CONTROLLER_INPUT_AB (*_portInputRegister(CONTROLLER_PORT_AB))
#define CONTROLLER_OUTPUT_AB (*_portOutputRegister(CONTROLLER_PORT_AB))
#define CONTROLLER_DIR_AB (*_portModeRegister(CONTROLLER_PORT_AB))

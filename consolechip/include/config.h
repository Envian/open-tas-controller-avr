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

/*******************************************************************************
*                                     PINS                                     *
*******************************************************************************/
// Chip Communication Pins. Must be on the same port.
#define LINK_HIGHPIN PIN_A0
#define LINK_LOWPIN PIN_A1

// Console Pins
#define CONTROLLER1A 0
#define CONTROLLER1B 2
#define CONTROLLER2A 1
#define CONTROLLER2B 3
#define CONTROLLER3A 4
#define CONTROLLER3B 6
#define CONTROLLER4A 5
#define CONTROLLER4B 7

// Pin C for each controller is on CONTROLLER_DIR3 and are the bit for that pin
#define CONTROLLER1C 8
#define CONTROLLER2C 9
#define CONTROLLER3C 10
#define CONTROLLER4C 11

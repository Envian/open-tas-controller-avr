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

#define serialDiscardString() while (Serial.read());

const PROGMEM char STR_STARTUP[] = "OpenTAS | Type ? for help";
const PROGMEM char STR_HELP[] =
	"OpenTAS https://github.com/Envian/open-tas-controller/\n"
	"This is a list of commands available via ASCII Serial. More commands are\n"
	"available to dedicated, binary clients. More details can be found on Github.\n"
	"\n"
	"    v - Version Info\n"
	"    d - Describe\n"
	"    ? - Help";
const PROGMEM char STR_DESCRIPTION[] = "Test Description.";
const PROGMEM char STR_VERSION[] = "Version " STR(VERSION) " API 0";


const PROGMEM char ERR_BAD_CONSOLE[] = "ERR_BAD_C";
const PROGMEM char ERR_NO_CONSOLE[] = "ERR_NO_C";
const PROGMEM char ERR_CONSOLE_CONFIG[] = "ERR_C_CONFIG";
const PROGMEM char ERR_UNSUPPORTED_CONSOLE_CMD[] = "ERR_UNSUPPORTED_C_CMD";

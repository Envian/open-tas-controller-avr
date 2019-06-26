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

/*******************************************************************************
*                                     LINK                                     *
*******************************************************************************/
// For the console chip, runs on analog 0 and analog 1.
// Having both pins on the same port improves performance
#define LINK_DIR DDRC
#define LINK_DATA PORTC
#define LINK_INPUT PINC
#define LINK_HIGHPIN 0
#define LINK_LOWPIN 1

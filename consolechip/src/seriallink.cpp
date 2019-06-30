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
#include "config.h"
#include "pinregisters.h"

#include "seriallink.h"

#if _pinToPort(LINK_HIGHPIN) != _pinToPort(LINK_LOWPIN)
#error Link port communciation must be on the same port
#endif

#define LINK_PORT _pinToPort(LINK_HIGHPIN)

#define LINK_MODE *_portModeRegister(LINK_PORT)
#define LINK_INPUT *_portInputRegister(LINK_PORT)
#define LINK_OUTPUT *_portOutputRegister(LINK_PORT)

#define HIGHMASK _pinToBitMask(LINK_HIGHPIN)
#define LOWMASK _pinToBitMask(LINK_LOWPIN)
#define PINMASK (HIGHMASK | LOWMASK)

namespace SerialLink {
	uint8_t sending;
	byte state;

	void init() {
		LINK_MODE &= ~PINMASK; // Forces both pins to input.
		LINK_OUTPUT |= PINMASK; // Sets both to pullup
	}

	uint8_t read() {
		uint8_t result;
		for (byte n = 0; n < 8; n++) {
			result <<= 1;

			uint8_t responsePin;
			do {
				responsePin = (LINK_INPUT & PINMASK);
			} while (responsePin == PINMASK);

			result |= (responsePin == LOWMASK ? 1 : 0);

			// Confirmation Process
			LINK_OUTPUT &= ~responsePin;
			LINK_MODE |= responsePin;

			while ((LINK_INPUT & (responsePin ^ PINMASK)) == 0) {}

			LINK_OUTPUT |= responsePin;
			LINK_MODE &= ~responsePin;
		}
		return result;
	}

	void write(uint8_t data) {
		for (byte n = B10000000; n != 0; n >>= 1) {
			uint8_t pin = (((data & n) == 0) ? LOWMASK : HIGHMASK);

			while ((LINK_INPUT & PINMASK) != PINMASK) { }

			LINK_OUTPUT &= ~pin;
			LINK_MODE |= pin;

			while ((LINK_INPUT & PINMASK) != 0) { }

			LINK_OUTPUT |= pin;
			LINK_MODE &= ~pin;

			while ((LINK_INPUT & PINMASK) != PINMASK) { }
		}
	}

	void beginWrite(uint8_t data) {
		sending = data;
		state = 16;

		// Begins the send process. Not possible to return true on the first call.
		available();
	}

	bool available() {
		if (state == 0) return true;

		if (state & 1) {
			// Odd - Confirm
			if ((LINK_INPUT & PINMASK) == 0) {
				uint8_t pin = (((sending & B10000000) == 0) ? LOWMASK : HIGHMASK);
				LINK_OUTPUT |= pin;
				LINK_MODE &= ~pin;
				sending <<= 1;
				state--;
			}
		} else {
			// Even - Send the bit when ready.
			if ((LINK_INPUT & PINMASK) == PINMASK) {
				uint8_t pin = (((sending & B10000000) == 0) ? LOWMASK : HIGHMASK);
				LINK_OUTPUT &= ~pin;
				LINK_MODE |= pin;
				state--;
			}
		}

		return state == 0;
	}
}

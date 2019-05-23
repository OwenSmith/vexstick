//
// VexHead
//
// 4x5 matrix -> 20bits (3-bytes)
// (4x4 buttons, 1x4 POV)

#include <Wire.h>
#include "VexMatrix.h"

static const uint8_t ROW_PINS[4] PROGMEM = { 10, 16, 15, 14 };
static const uint8_t COL_PINS[5] PROGMEM = { 9, 8, 7, 6, 5 };

VexMatrix   btns(4, 5, ROW_PINS, COL_PINS);

#define VEX_SLAVE_ADDRESS	0x67

void setup() {
	Wire.begin();
	btns.begin();
}

void loop() {
	if (!btns.update())
		return;

	uint8_t buffer[4] = {
		0,
		btns.get(0) | (btns.get(1) << 4),
		btns.get(2) | (btns.get(3) << 4),
		btns.get(4)
	};
	/*
		// for 8x3 button matrix
		1,
		btns.get(0),
		btns.get(1),
		btns.get(2)
	*/
	/*
		// for x,y ministick
		2,
		  x & 0x0FF,
		((x & 0xF00) >> 8) | (y & 0x00F) << 4),
		 (y & 0xFF0) >> 4
	*/

	Wire.beginTransmission(VEX_SLAVE_ADDRESS);
	Wire.write(buffer, sizeof(buffer));
	Wire.endTransmission();
}

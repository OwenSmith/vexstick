//
// VexStick
//

#include <Wire.h>
#include "Adafruit_ADS1015.h"
#include "VexJoystick.h"
#include "VexAxis.h"

Adafruit_ADS1115 adc;
VexJoystick      joy;
VexAxis          x, y, z;

#define VEX_SLAVE_ADDRESS	0x67

void setup() {
	Wire.begin(VEX_SLAVE_ADDRESS);
	Wire.onReceive(receive);

	adc.begin();

	while (millis() < 5000) {
		x.calibrate(adc.readADC_SingleEnded(0));
		y.calibrate(adc.readADC_SingleEnded(1));
		z.calibrate(adc.readADC_SingleEnded(2));
	}
	x.begin();
	y.begin();
	z.begin();

	Wire.begin(VEX_SLAVE_ADDRESS);
}

void loop() {
	Wire.begin();
	x.update(adc.readADC_SingleEnded(0));
	y.update(adc.readADC_SingleEnded(1));
	z.update(adc.readADC_SingleEnded(2));
	Wire.begin(VEX_SLAVE_ADDRESS);

	joy.axis(0, x.get());
	joy.axis(1, y.get());
	joy.axis(2, z.get());

	joy.send();
}

void receive(int n) {
	uint8_t buffer[4];
	uint8_t i = 0;

	while (Wire.available() && i < 4)
		buffer[i++] = Wire.read();

	joy.btns(0, buffer[0]);
	joy.btns(1, buffer[1]);
	joy.pov(buffer[2] & 0x0F);
}

//
// VexDelta
//

#include <Wire.h>
#include "Adafruit_ADS1015.h"
#include "VexJoystick.h"
#include "VexAxis.h"
#include "VexDelta.h"

Adafruit_ADS1115 adc;
VexJoystick      joy;
VexAxis          a, b, c;
VexDelta         axis;

#define VEX_SLAVE_ADDRESS	0x67

void setup() {
	Wire.begin(VEX_SLAVE_ADDRESS);
	Wire.onReceive(receive);

	adc.begin();

	while (millis() < 5000) {
		a.calibrate(adc.readADC_SingleEnded(0));
		b.calibrate(adc.readADC_SingleEnded(1));
		c.calibrate(adc.readADC_SingleEnded(2));
	}
	a.begin();
	b.begin();
	c.begin();

	Wire.begin(VEX_SLAVE_ADDRESS);
}

void loop() {
	Wire.begin();
	a.update(adc.readADC_SingleEnded(0));
	b.update(adc.readADC_SingleEnded(1));
	c.update(adc.readADC_SingleEnded(2));
	Wire.begin(VEX_SLAVE_ADDRESS);

	axis.update(a.get(), b.get(), c.get());
	joy.axis(0, axis.get(0));
	joy.axis(1, axis.get(1));
	joy.axis(2, axis.get(2));

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

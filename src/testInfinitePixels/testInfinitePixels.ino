// tl;dr:
// use arduino uno => data signal on pin D2.
// we use this lib: https://github.com/sonyhome/FAB_LED

#include <math.h>
#include <FAB_LED.h>

#define CRATE_WIDTH 4
#define CRATE_HEIGHT 5

const uint16_t numPixels = 1000;
sk6812b<D,2> myLeds;

void color1(uint8_t white, uint8_t red, uint8_t green, uint8_t blue) {
	grbw_t pix[1];

  pix[0].w = white;
  pix[0].r = red;
  pix[0].g = green;
  pix[0].b = blue;

	// Display the LEDs
	myLeds.sendPixels(1, pix);
}

void color1N(uint8_t white, uint8_t red, uint8_t green, uint8_t blue) {
	grbw_t pix[1];

  pix[0].w = white;
	pix[0].r = red;
	pix[0].g = green;
	pix[0].b = blue;

	const uint8_t oldSREG = SREG;
	cli();

	for (uint16_t i = 0; i < numPixels; i++) {
		myLeds.sendPixels(1, pix);
	}

	SREG = oldSREG;
}

void setup() {
	myLeds.clear(1000);
}

void loop() {
  for (int led = 0; led < 255; led++) {
    color1N(
      0,
      (uint8_t)(sin(led) * 127 + 128),
      (uint8_t)(sin(led + 3.141592635/2) * 127 + 128),
      (uint8_t)(sin(led + 3.141592635) * 127 + 128)
     );
  }
}

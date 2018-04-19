// tl;dr:
// use arduino uno => data signal on pin D2.
// we use this lib: https://github.com/sonyhome/FAB_LED

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// Fast Adressable Bitbang LED Library
/// Copyright (c)2015, 2016 Dan Truong
///
/// This example demonstrates control of up to 64K LEDs using 10 bytes of RAM.
/// By default it will light up 64 pixels. the downside of using more pixels
/// is an increase of the display refresh lag.
///
/// WARNING: If you drive many LEDs, make sure you power them separately and
/// not from your Arduino board. I set the value to 64 LEDs because I can
/// drive them with my Arduino Uno, provided I do not change the LED colors
/// or brightness from the original code.
///
/// Hardware configuration:
///
/// This example works for a regular Arduino board connected to your PC via the
/// USB port to the Arduino IDE (integrated development environment used to
/// compile and load an arduino sketch program to your arduino board).
/// By default it is expected the LED strip is on port D2.
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <FAB_LED.h>
#include "alpha.h"

#define CRATE_WIDTH 4
#define CRATE_HEIGHT 5

const uint16_t numPixels = 1000; // Max: 64K pixels

sk6812b<D,2> myLeds;


////////////////////////////////////////////////////////////////////////////////
/// @brief Waits then clears the LED strip.
////////////////////////////////////////////////////////////////////////////////
void holdAndClear(uint16_t on_time, uint16_t off_time)
{
	// Wait 1sec, turn off LEDs, wait 200msec
	delay(on_time);
	//PORTB ^= 1U << 5; // On
	myLeds.clear(1000);
	delay(off_time);
	//PORTB ^= 1U << 5; // Off
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Display one pixel with one solid color for 1 second.
/// Each value can be from 0 to 255.
////////////////////////////////////////////////////////////////////////////////
void color1(uint8_t white, uint8_t red, uint8_t green, uint8_t blue)
{
	grbw_t pix[1];

  pix[0].w = white;
  pix[0].r = red;
  pix[0].g = green;
  pix[0].b = blue;

	// Display the LEDs
	myLeds.sendPixels(1, pix);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Display numPixels with one solid color.
/// We only use a 3 byte array, storing one pixel.
/// We then send the same pixel repeatedly to the LED strip very fast.
/// This demonstrates the ability tocall the library repeatedly.
/// If this feature fails, you may see only 1 pixel lit, or a varying number
/// of pixels glitching on and off.
////////////////////////////////////////////////////////////////////////////////
void color1N(uint8_t white, uint8_t red, uint8_t green, uint8_t blue)
{
	grbw_t pix[1];

  pix[0].w = white;
	pix[0].r = red;
	pix[0].g = green;
	pix[0].b = blue;

	// Disable interupts, save the old interupt state
	const uint8_t oldSREG = SREG;
	cli();

	// Display the LEDs
	for (uint16_t i = 0; i < numPixels; i++) {
		myLeds.sendPixels(1, pix);
	}

	// Restore the old interrupt state
	SREG = oldSREG;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Helper routine to calculate the next color for a rainbow
/// Note: we force gcc to inline to meet the timing constraints of the LED strip
////////////////////////////////////////////////////////////////////////////////
static void colorWheel(uint8_t incStep, uint8_t & R, uint8_t & G, uint8_t & B)
__attribute__ ((always_inline));

static void colorWheel(uint8_t incStep, uint8_t & R, uint8_t & G, uint8_t & B)
{
	if (B == 0 && R != 0) {
		R = (R <= incStep) ? 0 : R - incStep;
		G = (G >= 255-incStep) ? 255 : G + incStep;
		return;
	}
	if (R == 0 && G != 0) {
		G = (G <= incStep) ? 0 : G - incStep;
		B = (B >= 255-incStep) ? 255 : B + incStep;
		return;
	}
	if (G == 0 && B != 0) {
		B = (B <= incStep) ? 0 : B - incStep;
		R = (R >= 255-incStep) ? 255 : R + incStep;
		return;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Display numPixels in a single color changing to all rainbow color.
/// We use a 3 byte array storing one pixel.
/// We then send the same pixel repeatedly to the LED strip very fast.
/// This demonstrates the ability tocall the library repeatedly.
/// If this feature fails, you may see only 1 pixel lit, or a varying number
/// of pixels glitching on and off.
////////////////////////////////////////////////////////////////////////////////
void fade1N(uint8_t brightness, uint8_t incLevel)
{
	grbw_t pix[1];

	// Initialize the colors on the array
	pix[0].r = brightness;
	pix[0].g = 0;
	pix[0].b = 0;

	// Display the LEDs
	for (uint16_t iter = 0; iter < 20 ; iter++) {
		const uint8_t oldSREG = SREG;
		cli();
		for (uint16_t i = 0; i < numPixels ; i++) {
			myLeds.sendPixels(1, pix);
		}
		SREG = oldSREG;
		delay(100);

		// Rotate the colors based on the pixel's previous color.
		colorWheel(incLevel, pix[0].r, pix[0].g, pix[0].b);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Display numPixels with a rotating rainbow color.
/// We use a 3 byte array storing one pixel.
/// We then send the same pixel repeatedly to the LED strip very fast.
/// This demonstrates the ability tocall the library repeatedly.
/// If this feature fails, you may see only 1 pixel lit, or a varying number
/// of pixels glitching on and off.
////////////////////////////////////////////////////////////////////////////////
void rainbow1N(uint8_t brightness, int delay_)
{
  grbw_t pix[1];

  // Initialize the colors on the array
  pix[0].r = brightness;
  pix[0].g = 0;
  pix[0].b = 0;

  // Display the LEDs
  for (uint16_t iter = 0; iter < 20 ; iter++) {
    const uint8_t oldSREG = SREG;
    cli();
    for (uint16_t i = 0; i < numPixels ; i++) {
      myLeds.sendPixels(1, pix);
      // Rotate the colors based on the pixel's previous color.
      colorWheel(1, pix[0].r, pix[0].g, pix[0].b);
    }
    SREG = oldSREG;
    delay(delay_);
  }
}


////////////////////////////////////////////////////////////////////////////////
/// @brief This method display a char
////////////////////////////////////////////////////////////////////////////////
void show(char* w, uint8_t white, uint8_t red, uint8_t green, uint8_t blue)
{
  for (int i = 0; i < strlen(w); i++){
  int c = w[i] - 97;
  
  for (int y = 0; y < CRATE_HEIGHT; y++)
    for (int x = 0; x < CRATE_WIDTH; x++)
    {
      int pixel_index = (y * CRATE_WIDTH) + ((y % 2 != 0) ? (CRATE_WIDTH - 1 - x) : x);
      
      if (alpha[c][pixel_index] == 1)
      {
      color1(white, red, green, blue);
      }
      else
      {
      color1(1, 0, 0, 0);
      }
    }
  }
}



////////////////////////////////////////////////////////////////////////////////
/// @brief This method is automatically called once when the board boots.
////////////////////////////////////////////////////////////////////////////////
void setup()
{
	myLeds.clear(1000);
}


////////////////////////////////////////////////////////////////////////////////
/// @brief This method is automatically called repeatedly after setup() has run.
/// It is the main loop, and it calls all the other demo methods declared below.
////////////////////////////////////////////////////////////////////////////////

void loop()
{
  show("urlab", 0, 255, 0, 105);
  holdAndClear(1000,10);

  show("urlab", 0, 80, 100, 0);
  holdAndClear(1000,10);

  show("urlab", 0, 255, 111, 0);
  holdAndClear(1000,10);
}

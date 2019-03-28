#include <FAB_LED.h>

#include "utils.h"
#include "rollingMatrix.h"

//#include "MateEEPROM.h"


#ifdef ARDUINO_AVR_UNO
// UNO => pin 2
sk6812b<D,2> leds;
#endif

#ifdef ARDUINO_AVR_MEGA2560
// MEGA => pin 12
sk6812b<B,6> leds;
#endif

void draw(uint32_t *pixels, uint16_t len) {
    grbw_t pix[1];

    for (uint16_t i = 0; i < len; i++) {
        pix[0].r = (uint8_t) pixels[i];
        pix[0].g = (uint8_t) (pixels[i] >> 8);
        pix[0].b = (uint8_t) (pixels[i] >> 16);
        pix[0].w = (uint8_t) (pixels[i] >> 24);

        leds.sendPixels(1, pix);
    }
}

#include "config.h"

#ifdef ARDUINO_AVR_UNO
// UNO => pin 2
sk6812b<D,2> leds;
#endif

#ifdef ARDUINO_AVR_MEGA2560
// MEGA => pin 12
sk6812b<B,6> leds;
#endif

coord IN_CRATE_ORDER[] = {
    {0, 0}, {1, 0}, {2, 0}, {3, 0},
    {3, 1}, {2, 1}, {1, 1}, {0, 1},
    {0, 2}, {1, 2}, {2, 2}, {3, 2},
    {3, 3}, {2, 3}, {1, 3}, {0, 3},
    {0, 4}, {1, 4}, {2, 4}, {3, 4},
};

void draw(uint32_t *pixels, uint16_t len) {
    grbw_t pix[1];

    for (uint16_t i = 0; i < len; i++) {
        // BLUE RED GREEN WHITE
        pix[0].w = pixels[i];
        pix[0].r = pixels[i] >> 8;
        pix[0].g = pixels[i] >> 16;
        pix[0].b = pixels[i] >> 24;

        leds.sendPixels(1, pix);
    }
}

#include <SmartMatrix.h>
#include "FAB_LED.h"


// BLUE RED GREEN WHITE

#define BLACK 0
#define BLUE  0xff000000
#define RED   0x00ff0000
#define GREEN 0x0000ff00
#define WHITE 0x000000ff
#define P1NK  0x69ff0000


#ifdef ARDUINO_AVR_UNO
// UNO => pin 2
sk6812b<D,2> leds;
#endif

#ifdef ARDUINO_AVR_MEGA2560
// MEGA => pin 12
sk6812<B,6> leds;
#endif

void draw(uint32_t *pixels, uint16_t len) {
    grbw_t pix[1];

    for (uint16_t i = 0; i < len; i++) {
        pix[0].w = pixels[i];
        pix[0].r = pixels[i] >> 8;
        pix[0].g = pixels[i] >> 16;
        pix[0].b = pixels[i] >> 24;

        leds.sendPixels(1, pix);
    }
}

// List coordinates of each crate in "wire order"
coord crate_order[15] = {
    {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0},
    {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1},
    {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
};
CMMatrix cm = CMMatrix(20, 15, crate_order);

uint32_t column[15] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};
uint32_t row[20] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void setup() {
}

void loop() {
    for (int i=0; i<15; i++) {
        column[i] = RED;
    }

    for (int i=0; i < 20; i++) {
        cm.push_right(column);
        draw(cm.render(), 300);
        delay(100);
    }

    for (int i=0; i<20; i++) {
        row[i] = GREEN;
    }

    for (int i=0; i < 15; i++) {
        cm.push_top(row);
        draw(cm.render(), 300);
        delay(100);
    }

    for (int i=0; i<15; i++) {
        column[i] = BLUE;
    }

    for (int i=0; i < 20; i++) {
        cm.push_left(column);
        draw(cm.render(), 300);
        delay(100);
    }

    for (int i=0; i<20; i++) {
        row[i] = P1NK;
    }

    for (int i=0; i < 15; i++) {
        cm.push_bottom(row);
        draw(cm.render(), 300);
        delay(100);
    }
}

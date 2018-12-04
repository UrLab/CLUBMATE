#include <SmartMatrix.h>
#include "FAB_LED.h"

#define BLACK 0
#define WHITE 255
#define RED 65280
#define GREEN 16711680
#define BLUE 4278190080
#define PINK 4278216960

sk6812b<D,2> leds;

void draw(uint32_t *pixels, uint8_t len) {
    grbw_t pix[1];

    for (int i=0; i < len; i++) {
        pix[0].w = pixels[i];
        pix[0].r = pixels[i] >> 8;
        pix[0].g = pixels[i] >> 16;
        pix[0].b = pixels[i] >> 24;

        leds.sendPixels(1, pix);
    }
}

// List coordinates of each crate in "wire order"
coord crate_order[10] = {
    {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0},
    {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1},
};
CMMatrix cm = CMMatrix(20, 10, crate_order);

uint32_t column[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t row[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
    for (int i=0; i<10; i++) {
        column[i] = RED;
    }
}

void loop() {
    for (int i=0; i<10; i++) {
        column[i] = RED;
    }

    for (int i=0; i < 20; i++) {
        cm.push_right(column);
        draw(cm.render(), 200);
        delay(100);
    }

    for (int i=0; i<20; i++) {
        row[i] = GREEN;
    }

    for (int i=0; i < 10; i++) {
        cm.push_top(row);
        draw(cm.render(), 200);
        delay(100);
    }

    for (int i=0; i<10; i++) {
        column[i] = BLUE;
    }

    for (int i=0; i < 20; i++) {
        cm.push_left(column);
        draw(cm.render(), 200);
        delay(100);
    }

    for (int i=0; i<20; i++) {
        row[i] = PINK;
    }

    for (int i=0; i < 10; i++) {
        cm.push_bottom(row);
        draw(cm.render(), 200);
        delay(100);
    }
}

#include "SmartMatrix.h"
#include "crate.h"

#include <Arduino.h>
#include <stdlib.h>

RollingMatrix::RollingMatrix(uint8_t width, uint8_t height) {
    this->w = width;
    this->h = height;

    this->w_shift = 0;
    this->h_shift = 0;

    this->matrix = (uint32_t *) malloc(sizeof(uint32_t) * w * h);

    for (
        uint32_t* pixel = this->matrix;
        pixel < this->matrix + (this->w * this->h);
        ++pixel
    ) {
        *pixel = 0;
    }
}

uint32_t RollingMatrix::mget(uint8_t x, uint8_t y) {
    return ((uint32_t*) this->matrix)[
            (((y + this->h_shift) % this->h) * this->w) +
            ((x + this->w_shift) % this->w)
            ];
}

void RollingMatrix::mset(uint8_t x, uint8_t y, uint32_t v) {
    ((uint32_t*) matrix)[
    (((y + this->h_shift) % this->h) * this->w) +
    ((x + this->w_shift) % this->w)] = v;
}

void RollingMatrix::push_right(uint32_t* column) {
    for (uint8_t i = 0; i < this->h; i++) {
        mset(0, i, column[i]);
    }
    this->w_shift = (this->w_shift + 1) % this->w;
}

void RollingMatrix::push_left(uint32_t* column) {
    for (uint8_t i = 0; i < this->h; i++) {
        mset(this->w - 1, i, column[i]);
    }
    this->w_shift = (this->w_shift - 1 + this->w) % this->w;
}

void RollingMatrix::push_bottom(uint32_t* column) {
    for  (uint8_t i = 0; i < this->w; i++) {
        mset(i, 0, column[i]);
    }
    this->h_shift = (this->h_shift + 1) % this->h;
}

void RollingMatrix::push_top(uint32_t* column) {
    for (uint8_t i = 0; i < this->w; i++) {
        mset(i, this->h - 1, column[i]);
    }
    this->h_shift = (this->h_shift - 1 + this->h) % this->h;
}

CMMatrix::CMMatrix(uint8_t width, uint8_t height, coord* crate_order)
    :RollingMatrix(width, height) {
    this->crate_nbr = (width * height) / CRATE_SIZE;
    this->crate_order = crate_order;
    this->led_array = (uint32_t *) malloc(sizeof(uint32_t) * width * height);
};

uint32_t* CMMatrix::render() {
    uint32_t* led = this->led_array;
    int i = 0;
    for (
        coord* crate_coord = this->crate_order;
        crate_coord < this->crate_order + this->crate_nbr;
        ++crate_coord
    ) {
        for (coord led_coord : IN_CRATE_ORDER) {
            int x_ = (crate_coord->x * CRATE_WIDTH) + led_coord.x;
            int y_ = (crate_coord->y * CRATE_HEIGHT) + led_coord.y;

            uint32_t tmp = mget(x_, y_);

            *led = tmp;
            led++;

            i++;
        }
    }
    return this->led_array;
};

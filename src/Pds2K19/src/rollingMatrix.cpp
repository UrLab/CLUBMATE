#include "rollingMatrix.h"

//TODO replace constant with eeprom value

RollingMatrix::RollingMatrix(uint8_t width, uint8_t height) {
    this->w = width;
    this->h = height;

    this->leds_nbr = width * height;

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

uint16_t RollingMatrix::get_leds_nbr() {
    return this->leds_nbr;
}

uint32_t RollingMatrix::convert(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return ((uint32_t) w << 24) | ((uint32_t) b << 16) | ((uint32_t) g << 8 ) | (uint32_t) r;
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

void RollingMatrix::mset(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    this->mset(x, y, this->convert(r, g, b, w));
}

void RollingMatrix::fill(uint32_t v) {
    uint32_t* m = this->matrix;
    for (; m < this->matrix + this->get_leds_nbr();) {
        *m = v;
        m++;
    }
}

void RollingMatrix::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    this->fill(this->convert(r, g, b, w));
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

void RollingMatrix::push_bottom(uint32_t* row) {
    for  (uint8_t i = 0; i < this->w; i++) {
        mset(i, 0, row[i]);
    }
    this->h_shift = (this->h_shift + 1) % this->h;
}

void RollingMatrix::push_top(uint32_t* row) {
    for (uint8_t i = 0; i < this->w; i++) {
        mset(i, this->h - 1, row[i]);
    }
    this->h_shift = (this->h_shift - 1 + this->h) % this->h;
}

CMMatrix::CMMatrix(uint8_t width, uint8_t height, coord* crate_order,
                   uint8_t crate_size,
                   uint8_t crate_width,
                   uint8_t crate_height,
                   coord* in_crate_order):RollingMatrix(width, height) {
    this->crate_size = crate_size;
    this->crate_width = crate_width;
    this->crate_height = crate_height;

    this->crate_nbr = this->get_leds_nbr() / this->crate_size;
    this->crate_order = crate_order;
    this->in_crate_order = in_crate_order;
    this->led_array = (uint32_t *) malloc(sizeof(uint32_t) * width * height);
};

uint32_t* CMMatrix::render() {
    uint32_t* led = this->led_array;
    for (
        coord* crate_coord = this->crate_order;
        crate_coord < this->crate_order + this->crate_nbr;
        ++crate_coord
    ) {
        for (
                coord* led_coord = this->in_crate_order;
                led_coord < this->in_crate_order + this->crate_size;
                ++led_coord
            ) {
            *led = mget(
                    (crate_coord->x * this->crate_width) + led_coord->x,
                    (crate_coord->y * this->crate_height) + led_coord->y
            );
            led++;
        }
    }
    return this->led_array;
};

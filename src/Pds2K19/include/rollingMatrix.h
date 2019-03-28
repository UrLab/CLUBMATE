#include <Arduino.h>

#include "utils.h"

#ifndef MATRIX_CLASS
#define MATRIX_CLASS
class RollingMatrix {
  private:
    uint8_t w, h;
    uint16_t leds_nbr;
    uint8_t w_shift, h_shift;

    uint32_t *matrix;

  public:
    RollingMatrix(uint8_t width, uint8_t height);

    uint16_t get_leds_nbr();
    uint32_t convert(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

    uint32_t mget(uint8_t x, uint8_t y);
    void mset(uint8_t x, uint8_t y, uint32_t v);
    void mset(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t w);

    void fill(uint32_t v);
    void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

    void push_right(uint32_t* column);
    void push_left(uint32_t* column);
    void push_bottom(uint32_t* row);
    void push_top(uint32_t* row);
};

class CMMatrix: public RollingMatrix {
  private:
    uint8_t crate_nbr;  // number of crate in matrix
    uint8_t crate_size;
    uint8_t crate_width;
    uint8_t crate_height;
    coord* crate_order;  // X,Y coordinates of each crate in the order of connection
    coord* in_crate_order;  // X,Y coordinates of each led in a crate
    uint32_t* led_array;

  public:
    CMMatrix(uint8_t width, uint8_t height, coord* crate_order,
            uint8_t crate_size, uint8_t crate_width, uint8_t crate_height,
            coord* in_crate_order);

    uint32_t* render();
};
#endif

#include <Arduino.h>

#ifndef COORD
#define COORD
typedef struct {
    uint8_t x;
    uint8_t y;
} coord;
#endif

#ifndef MATRIX_CLASS
#define MATRIX_CLASS
class RollingMatrix {
  private:
    uint8_t w, h;
    uint8_t w_shift, h_shift;

    uint32_t *matrix;

  public:
    RollingMatrix(uint8_t width, uint8_t height);

    uint32_t mget(uint8_t x, uint8_t y);
    void mset(uint8_t x, uint8_t y, uint32_t v);

    void push_right(uint32_t* column);
    void push_left(uint32_t* column);
    void push_bottom(uint32_t* row);
    void push_top(uint32_t* row);
};

class CMMatrix: public RollingMatrix {
  private:
    uint8_t crate_nbr;  // number of crate in matrix
    coord* crate_order;  // X,Y coordinates of each crate in the order of connection
    uint32_t* led_array;

  public:
    CMMatrix(uint8_t width, uint8_t height, coord* crate_order);

    uint32_t* render();
};
#endif

// tl;dr:
// use arduino uno => data signal on pin D2.
// we use this lib: https://github.com/sonyhome/FAB_LED

#include <FAB_LED.h>
sk6812b<D, 2> myLeds;
#include <Arduino.h>
#include <stdlib.h>


#define CRATE_SIZE 20
#define CRATE_H 5
#define CRATE_W 4
//#define uint8_t int
//#define uint32_t int


// TODO: use header files
struct coord {
  uint8_t x;
  uint8_t y;
};

coord IN_CRATE_ORDER[CRATE_SIZE] = {
  {0, 0}, {1, 0}, {2, 0}, {3, 0},
  {3, 1}, {2, 1}, {1, 1}, {0, 1},
  {0, 2}, {1, 2}, {2, 2}, {3, 2},
  {3, 3}, {2, 3}, {1, 3}, {0, 3},
  {0, 4}, {1, 4}, {2, 4}, {3, 4},
};

class RollingMatrix {
    uint8_t w, h;
    uint8_t w_shift, h_shift;

    uint32_t **matrix;

  public:
    RollingMatrix(uint8_t width, uint8_t height) {
      this->w = width;
      this->h = height;

      this->w_shift = 0;
      this->h_shift = 0;

      this->matrix = (uint32_t **) malloc(sizeof(uint32_t) * w * h);
    }

    uint32_t mget(uint8_t x, uint8_t y) {
      return ((uint32_t*)this->matrix)[
               (((y + this->h_shift) % this->h) * this->w) +
               ((x + this->w_shift) % this->w)
             ];
    }

    void mset(uint8_t x, uint8_t y, uint32_t v) {
      ((uint32_t*)matrix)[
        (((y + this->h_shift) % this->h) * this->w) +
        ((x + this->w_shift) % this->w)
      ] = v;
    }

    void push_right(uint32_t* column) {
      for (uint8_t i = 0; i < this->h; i++) {
        mset(0, i, column[i]);
      }
      this->w_shift = (this->w_shift + 1) % this->w;
    }

    void push_left(uint32_t* column) {
      for (uint8_t i = 0; i < this->h; i++) {
        mset(this->w - 1, i, column[i]);
      }
      this->w_shift = (this->w_shift - 1 + this->w) % this->w;
    }

    void push_bottom(uint32_t* column) {
      for  (uint8_t i = 0; i < this->w; i++) {
        mset(i, 0, column[i]);
      }
      this->h_shift = (this->h_shift + 1) % this->h;
    }

    void push_top(uint32_t* column) {
      for (uint8_t i = 0; i < this->w; i++) {
        mset(i, this->h - 1, column[i]);
      }
      this->h_shift = (this->h_shift - 1 + this->h) % this->h;
    }
};

//---------------------------------------//

class CMMatrix: public RollingMatrix {
    uint8_t crate_nbr;  // number of crate in matrix
    coord* crate_order;  // X,Y coordinates of each crate in the order of connection
    uint32_t* led_array;

  public:
    CMMatrix(uint8_t width, uint8_t height, coord* crate_order)
      : RollingMatrix(width, height) {
      this->crate_nbr = (width * height) / CRATE_SIZE;
      this->crate_order = crate_order;
      this->led_array = (uint32_t *) malloc(
                          sizeof(uint32_t) * width * height);

      //std::cout << this->crate_nbr << " crates" << std::endl;
    };

    uint32_t* render() {
      uint32_t* led = this->led_array;
      int i = 0;
      for (
        coord* crate_coord = this->crate_order;
        crate_coord < this->crate_order + this->crate_nbr;
        ++crate_coord
      ) {
        for (coord led_coord : IN_CRATE_ORDER) {
          int x_ = (crate_coord->x * CRATE_W) + led_coord.x;
          int y_ = (crate_coord->y * CRATE_H) + led_coord.y;

          uint32_t tmp = mget(x_, y_);

          *led = tmp;
          led++;

          i++;
        }
      }
      //std::cout << "Total : " << i << std::endl;

      return this->led_array;
    };

    //---------------------------------------//
};

void color1(uint8_t white, uint8_t red, uint8_t green, uint8_t blue) {
  grbw_t pix[1];

  pix[0].w = white;
  pix[0].r = red;
  pix[0].g = green;
  pix[0].b = blue;

  // Display the LEDs
  myLeds.sendPixels(1, pix);
}



coord crate_order[4] = {
{0, 0}, {1, 0},
{1, 1}, {0, 1},
};
CMMatrix cm = CMMatrix(8, 10, crate_order);

void setup() {
  myLeds.clear(40);
}


void show(int l) {
    if (l == 1 ) {
      color1(255, 0, 0, 0);
    } else if (l == 2) {
      color1(0, 255, 0, 0);
    } else if (l == 3) {
      color1(0, 0, 255, 0);
    } else if (l == 4) {
      color1(0, 0, 0, 255);
    } else {
      color1(0, 0, 0, 0);
    }
}


void loop() {
  uint32_t *test = cm.render();
  for (int led = 0; led < 80; led++) {
    show(test[led]);
  }

  delay(100);

  uint32_t column[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 10; i++) {
    cm.push_right(column);
    test = cm.render();
    for (int led = 0; led < 80; led++) {
        show(test[led]);
    }
    delay(300);
  }

  uint32_t column2[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  for (int i = 0; i < 10; i++) {
    cm.push_left(column2);
    test = cm.render();
    for (int led = 0; led < 80; led++) {
        show(test[led]);
    }
    delay(300);
  }

  uint32_t row[8] = {2, 2, 2, 2, 2, 2, 2, 2};
  for (int i = 0; i < 10; i++) {
    cm.push_top(row);
    test = cm.render();
    for (int led = 0; led < 80; led++) {
        show(test[led]);
    }
    delay(300);
  }

  uint32_t row2[8] = {3, 3, 3, 3, 3, 3, 3, 3};
  for (int i = 0; i < 10; i++) {
    cm.push_bottom(row2);
    test = cm.render();
    for (int led = 0; led < 80; led++) {
        show(test[led]);
    }
    delay(300);
  }

}

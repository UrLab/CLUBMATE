// #include <Arduino.h>
#include <stdlib.h>
#include <iostream>

#define uint8_t int
#define uint32_t int

// TODO: use header files
struct coord {
    uint8_t x;
    uint8_t y;
};
#define CRATE_SIZE 20
#define CRATE_H 5
#define CRATE_W 4
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

    void print() {
        for (int y = 0; y < this->h; y++) {
            for (int x = 0; x < this->w; x++) {
                std::cout << mget(x, y);
            }
            std::cout << "\n";
        }
        std::cout << "\n";
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

            std::cout << this->crate_nbr << " crates" << std::endl;
        };

        uint32_t* render(){
            uint32_t* led = this->led_array;
            int i = 0;
            for (
                    coord* crate_coord = this->crate_order;
                    crate_coord < this->crate_order + this->crate_nbr;
                    ++crate_coord
                    ) {
                for (coord led_coord : IN_CRATE_ORDER) {
                    int x_ = (crate_coord->x * CRATE_H) + led_coord.x;
                    int y_ = (crate_coord->y * CRATE_W) + led_coord.y;

                    uint32_t tmp = mget(x_, y_);
                    std::cout << "Set " << tmp << " to " << x_ << ", " << y_ << std::endl;

                    *led = tmp;
                    led++;

                    i++;
                }
            }
            std::cout << "Total : " << i << std::endl;

            return this->led_array;
        };
        void aprint(){
            for (int i = 0; i < (this->crate_nbr * CRATE_H * CRATE_W); i++)
            {
                std::cout << this->led_array[i] << ", ";

                if (((i + 1)%CRATE_W) == 0) {
                    std::cout << std::endl;
                }
                if (((i + 1)%(CRATE_W * CRATE_H)) == 0) {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        }
};

#include <Arduino.h>

#define BLACK 0
#define BLUE  0xff000000
#define RED   0x00ff0000
#define GREEN 0x0000ff00
#define WHITE 0x000000ff
#define P1NK  0x69ff0000

#ifndef COORD
#define COORD
typedef struct {
    uint8_t x;
    uint8_t y;
} coord;
#endif

#ifndef DRAW_FUNC
#define DRAW_FUNC
void draw(uint32_t *pixels, uint16_t len);
#endif

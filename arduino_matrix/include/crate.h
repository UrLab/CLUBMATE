#include "SmartMatrix.h"

// Basic informations about a crate
#define CRATE_HEIGHT 5
#define CRATE_WIDTH 4
#define CRATE_SIZE (CRATE_HEIGHT * CRATE_WIDTH)


/*
 * In-crate led order :
 *
 *   0 →  1 →  2 →  3
 *                  ↓
 *   7 ←  6 ←  5 ←  4
 *   ↓
 *   8 →  9 → 10 → 11
 *                  ↓
 *  15 ← 14 ← 13 ← 12
 *  ↓
 *  16 → 17 → 18 → 19
 *
 */

#ifndef IN_CRATE_ORDER_DEF
#define IN_CRATE_ORDER_DEF
// List coordinates of each led in "wire order"
coord IN_CRATE_ORDER[CRATE_SIZE] = {
    {0, 0}, {1, 0}, {2, 0}, {3, 0},
    {3, 1}, {2, 1}, {1, 1}, {0, 1},
    {0, 2}, {1, 2}, {2, 2}, {3, 2},
    {3, 3}, {2, 3}, {1, 3}, {0, 3},
    {0, 4}, {1, 4}, {2, 4}, {3, 4},
};
#endif

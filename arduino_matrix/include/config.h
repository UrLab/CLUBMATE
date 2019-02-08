#include <FAB_LED.h>
#include "utils.h"

/************************************
 * Basic informations about a crate *
 ************************************/
#define CRATE_HEIGHT 5
#define CRATE_WIDTH 4
#define CRATE_SIZE (CRATE_HEIGHT * CRATE_WIDTH)

/*
 * List coordinates of each led in a crate in the "wire order" :
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
extern coord IN_CRATE_ORDER[CRATE_SIZE];
#endif

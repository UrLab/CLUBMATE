#include <Arduino.h>
#include "utils.h"

#define CRATE_WIDTH_ADDR 0
#define CRATE_HEIGHT_ADDR 1
#define CRATE_SIZE_ADDR 2

#define MATRIX_WIDTH_ADDR 3
#define MATRIX_HEIGHT_ADDR 4
#define MATRIX_SIZE_ADDR 5
#define MATRIX_START_ADDR 6
#define DYN_MEMORY_ADDR 7

/* Information about a crate.
 */
uint8_t get_crate_size();

uint8_t get_crate_width();
void set_crate_width(uint8_t w);

uint8_t get_crate_height();
void set_crate_height(uint8_t h);

coord* get_crate_shape();

/* Information about the matrix (in number of crate).
 */
uint8_t get_matrix_size();

uint8_t get_matrix_width();
void set_matrix_width(uint8_t w);

uint8_t get_matrix_height();
void set_matrix_height(uint8_t h);

coord* get_crate_shape();
void set_crate_shape(coord* shape, size_t size);

coord* get_matrix_shape();

/* Set shapes of the matrix.
 */
void set_shape(coord* crate_shape,  size_t crate_size,
               coord* matrix_shape, size_t matrix_size);

#include <EEPROM.h>

#include "MateEEPROM.h"

coord* _get_range(uint8_t start, uint8_t size) {
    coord* range = (coord *) malloc(sizeof(coord) * size);
    coord* tmp = range;

    for (uint8_t ptr = start; ptr < (start + (2 * size)); ptr+=2) {
        tmp->x = (uint8_t) EEPROM.read(ptr);
        tmp->y = (uint8_t) EEPROM.read(ptr + 1);

        tmp++;
    }

    return range;
}

void _set_range(coord* values, uint8_t start, uint8_t size) {
    for (uint8_t ptr = start; ptr < start + (2 * size); ptr += 2) {
        EEPROM.write(ptr, values->x);
        EEPROM.write(ptr + 1, values->y);

        values++;
    }
}

uint8_t get_crate_size() {
    return (uint8_t) EEPROM.read(CRATE_SIZE_ADDR);
}

uint8_t get_crate_width() {
    return (uint8_t) EEPROM.read(CRATE_WIDTH_ADDR);
}

void set_crate_width(uint8_t value) {
    EEPROM.write(CRATE_WIDTH_ADDR, value);
}

uint8_t get_crate_height() {
    return (uint8_t) EEPROM.read(CRATE_HEIGHT_ADDR);
}

void set_crate_height(uint8_t value) {
    EEPROM.write(CRATE_HEIGHT_ADDR, value);
}

uint8_t get_matrix_size() {
    return (uint8_t) EEPROM.read(MATRIX_SIZE_ADDR);
}

uint8_t get_matrix_width() {
    return (uint8_t) EEPROM.read(MATRIX_WIDTH_ADDR);
}

void set_matrix_width(uint8_t value) {
    EEPROM.write(MATRIX_WIDTH_ADDR, value);
}

uint8_t get_matrix_height() {
    return (uint8_t) EEPROM.read(MATRIX_HEIGHT_ADDR);
}

void set_matrix_height(uint8_t value) {
    EEPROM.write(MATRIX_HEIGHT_ADDR, value);
}

coord* get_matrix_shape() {
    uint8_t size = (uint8_t) EEPROM.read(MATRIX_SIZE_ADDR);
    uint8_t start_addr = (uint8_t) EEPROM.read(MATRIX_START_ADDR);

    return _get_range(start_addr, size);
}

coord* get_crate_shape() {
    uint8_t size = (uint8_t) EEPROM.read(CRATE_SIZE_ADDR);
    uint8_t start_addr = (uint8_t) DYN_MEMORY_ADDR;

    return _get_range(start_addr, size);
}

void set_shape(coord* crate_shape,  size_t crate_size,
               coord* matrix_shape, size_t matrix_size) {

    EEPROM.write(CRATE_SIZE_ADDR, crate_size);
    EEPROM.write(MATRIX_SIZE_ADDR, matrix_size);

    uint8_t matrix_start_addr = DYN_MEMORY_ADDR + (2 * crate_size) + 1;
    EEPROM.write(MATRIX_START_ADDR, matrix_start_addr);

    _set_range(crate_shape, DYN_MEMORY_ADDR, crate_size);
    _set_range(matrix_shape, matrix_start_addr, matrix_size);
}

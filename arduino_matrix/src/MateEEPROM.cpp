#include <EEPROM.h>

#include "MateEEPROM.h"


//TODO use basic memoization on all get to avoid reading EEPROM everytime

MateEEPROM::MateEEPROM() {
      this->matrix_shape = (coord *) malloc(sizeof(coord) * ((uint8_t) EEPROM.read(MATRIX_SIZE_ADDR)));
      this->crate_shape  = (coord *) malloc(sizeof(coord) * ((uint8_t) EEPROM.read(CRATE_SIZE_ADDR)));
}

void MateEEPROM::_get_range(coord* mem, uint8_t start, size_t size) {
    for (uint8_t ptr = start; ptr < (start + (2 * size)); ptr+=2) {
        mem->x = (uint8_t) EEPROM.read(ptr);
        mem->y = (uint8_t) EEPROM.read(ptr + 1);

        mem++;
    }
}

void MateEEPROM::_set_range(coord* mem, uint8_t start, size_t size) {
    for (uint8_t ptr = start; ptr < start + (sizeof(coord) * size); ptr += 2) {
        EEPROM.update(ptr, mem->x);
        EEPROM.update(ptr + 1, mem->y);

        mem++;
    }
}

uint8_t MateEEPROM::get_crate_size() {
    return (uint8_t) EEPROM.read(CRATE_SIZE_ADDR);
}

uint8_t MateEEPROM::get_crate_width() {
    return (uint8_t) EEPROM.read(CRATE_WIDTH_ADDR);
}

void MateEEPROM::set_crate_width(uint8_t value) {
    EEPROM.update(CRATE_WIDTH_ADDR, value);
}

uint8_t MateEEPROM::get_crate_height() {
    return (uint8_t) EEPROM.read(CRATE_HEIGHT_ADDR);
}

void MateEEPROM::set_crate_height(uint8_t value) {
    EEPROM.update(CRATE_HEIGHT_ADDR, value);
}

uint8_t MateEEPROM::get_matrix_size() {
    return (uint8_t) EEPROM.read(MATRIX_SIZE_ADDR);
}

uint8_t MateEEPROM::get_matrix_width() {
    return (uint8_t) EEPROM.read(MATRIX_WIDTH_ADDR);
}

void MateEEPROM::set_matrix_width(uint8_t value) {
    EEPROM.update(MATRIX_WIDTH_ADDR, value);
}

uint8_t MateEEPROM::get_matrix_height() {
    return (uint8_t) EEPROM.read(MATRIX_HEIGHT_ADDR);
}

void MateEEPROM::set_matrix_height(uint8_t value) {
    EEPROM.update(MATRIX_HEIGHT_ADDR, value);
}

coord* MateEEPROM::get_matrix_shape() {
    uint8_t size = (uint8_t) EEPROM.read(MATRIX_SIZE_ADDR);
    uint8_t start_addr = (uint8_t) EEPROM.read(MATRIX_START_ADDR);

    _get_range(this->matrix_shape, start_addr, size);

    return this->matrix_shape;
}

coord* MateEEPROM::get_crate_shape() {
    uint8_t size = (uint8_t) EEPROM.read(CRATE_SIZE_ADDR);
    uint8_t start_addr = (uint8_t) DYN_MEMORY_ADDR;

    _get_range(this->crate_shape, start_addr, size);

    return this->crate_shape;
}

void MateEEPROM::set_shape(coord* crate_shape,  size_t crate_size,
                           coord* matrix_shape, size_t matrix_size) {

    EEPROM.update(CRATE_SIZE_ADDR, crate_size);
    EEPROM.update(MATRIX_SIZE_ADDR, matrix_size);

    uint8_t matrix_start_addr = DYN_MEMORY_ADDR + (sizeof(coord) * crate_size) + 1;
    EEPROM.update(MATRIX_START_ADDR, matrix_start_addr);

    this->_set_range(crate_shape, DYN_MEMORY_ADDR, crate_size);
    this->_set_range(matrix_shape, matrix_start_addr, matrix_size);
}

void MateEEPROM::reset_eeprom() {
    coord crate_order[15] = {
        {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0},
        {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1},
        {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}
    };

    coord in_crate_order[20] = {
        {0, 0}, {1, 0}, {2, 0}, {3, 0},
        {3, 1}, {2, 1}, {1, 1}, {0, 1},
        {0, 2}, {1, 2}, {2, 2}, {3, 2},
        {3, 3}, {2, 3}, {1, 3}, {0, 3},
        {0, 4}, {1, 4}, {2, 4}, {3, 4},
    };
    this->set_shape(in_crate_order, 20, crate_order, 15);
}

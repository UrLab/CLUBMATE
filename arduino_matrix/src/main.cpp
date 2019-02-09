#include <PacketSerial.h>
#include <FastCRC.h>

#include "SmartMatrix.h"


void onPacketReceived(const uint8_t* buffer, size_t size);

// List coordinates of each crate in "wire order"
coord crate_order[15] = {
    {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0},
    {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1},
    {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
};

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
coord in_crate_order[CRATE_SIZE] = {
    {0, 0}, {1, 0}, {2, 0}, {3, 0},
    {3, 1}, {2, 1}, {1, 1}, {0, 1},
    {0, 2}, {1, 2}, {2, 2}, {3, 2},
    {3, 3}, {2, 3}, {1, 3}, {0, 3},
    {0, 4}, {1, 4}, {2, 4}, {3, 4},
};

COBSPacketSerial packetSerial;
FastCRC16 CRC16;
CMMatrix cm = CMMatrix(20, 15, crate_order, in_crate_order);

void setup() {
    packetSerial.begin(115200);
    packetSerial.setPacketHandler(&onPacketReceived);
}

void loop() {
    packetSerial.update();
}

void crc_and_send(uint8_t *data, size_t size) {
    uint16_t crc = CRC16.modbus(data + 2, size - 2);
    data[0] = (uint8_t)((crc & 0xFF00) >> 8);
    data[1] = (uint8_t)( crc & 0x00FF);

    packetSerial.send(data, size);
}

void onPacketReceived(const uint8_t* buffer, size_t size){
    //TODO
}

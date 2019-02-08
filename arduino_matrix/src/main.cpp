#include <PacketSerial.h>

#include "SmartMatrix.h"


void onPacketReceived(const uint8_t* buffer, size_t size);

// List coordinates of each crate in "wire order"
coord crate_order[15] = {
    {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0},
    {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1},
    {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
};

COBSPacketSerial packetSerial;
CMMatrix cm = CMMatrix(20, 15, crate_order);

void setup() {
    packetSerial.begin(115200);
    packetSerial.setPacketHandler(&onPacketReceived);
}

void loop() {
    packetSerial.update();
}

void onPacketReceived(const uint8_t* buffer, size_t size){
    //TODO
}

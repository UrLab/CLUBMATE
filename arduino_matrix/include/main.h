#include <PacketSerial.h>
#include <FastCRC.h>

#include "MateEEPROM.h"
#include "SmartMatrix.h"

void onPacketReceived(const uint8_t* buffer, size_t size);

#include "main.h"
#include "utils.h"
#include "messages.h"


COBSPacketSerial packetSerial;

FastCRC16 CRC16;

MateEEPROM mate_eeprom;
CMMatrix cm(
        mate_eeprom.get_crate_size(),
        mate_eeprom.get_matrix_size(),
        mate_eeprom.get_matrix_shape(),
        20, 4, 5,  //TODO put that in eeprom
        mate_eeprom.get_crate_shape()
);

void setup() {
    mate_eeprom.reset_eeprom();
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

uint8_t is_crc_correct(const uint8_t *data, size_t size) {
    uint16_t crc = CRC16.modbus(data + 2, size - 2);
    if (data[0] == (uint8_t)((crc & 0xFF00) >> 8) &&
        data[1] == (uint8_t)( crc & 0x00FF)) {
        return 1;
    } else {
        return 0;
    }
}

void onPacketReceived(const uint8_t* buffer, size_t size) {
    Serial.print("Received : [");
    for (int i = 0; i < (int)  size; i++) {
        Serial.print(i);
        Serial.print(" -> ");
        Serial.print(buffer[i]);
        Serial.print(", ");
    }
    Serial.println("]");

    if (size < 5) {
        Serial.println("size < 5");
        uint8_t resp[5] = {0, 0, 0, 0, MSG_BAD_MSG};
        crc_and_send(resp, 5);
        return;
    }
    if (! is_crc_correct(buffer, size)) {
        Serial.println("bad crc");
        uint8_t resp[5] = {0, 0, 0, 0, MSG_BAD_MSG};
        crc_and_send(resp, 5);
        return;
    }
    switch (buffer[4]) {
        case INIT_MATRIX:
            break; //TODO
        case RESET:
            {
                mate_eeprom.reset_eeprom();
                uint8_t resp[5] = {0, 0, buffer[2], buffer[3], OK};
                crc_and_send(resp, 5);
            };
            break;
        case UNI_COLOR:
            {
                Serial.println("UNI_COLOR");
                if (size == 9) {
                    cm.fill(buffer[5], buffer[6], buffer[7], buffer[8]);
                    draw(cm.render(), cm.get_leds_nbr());
                    Serial.println("Done ...");
                    uint8_t resp[5] = {0, 0, buffer[2], buffer[3], OK};
                    crc_and_send(resp, 5);
                } else {
                    uint8_t resp[5] = {0, 0, buffer[2], buffer[3], MSG_BAD_MSG};
                    crc_and_send(resp, 5);
                }
            };
            break;
        case SET_PIXEL:
            {
                Serial.println("SET_PIXEL");
                Serial.print("x: ");
                Serial.print(buffer[6]);
                Serial.print(", y: ");
                Serial.println(buffer[8]);

                Serial.print(", y: ");
                if (size == 11) {
                    cm.mset(buffer[5], buffer[6], buffer[7], buffer[8], buffer[9], buffer[10]);
                    draw(cm.render(), cm.get_leds_nbr());
                    uint8_t resp[5] = {0, 0, buffer[2], buffer[3], OK};
                    crc_and_send(resp, 5);
                } else {
                    uint8_t resp[5] = {0, 0, buffer[2], buffer[3], MSG_BAD_MSG};
                    crc_and_send(resp, 5);
                }
            };
            break;
        case SET_PIXELS:
            break; //TODO
        case TOP_ROW:
            break; //TODO
        case BOTTOM_ROW:
            break; //TODO
        case RIGHT_COLUMN:
            break; //TODO
        case LEFT_COLUMN:
            break; //TODO
        case FRAME:
            break; //TODO
    }
}

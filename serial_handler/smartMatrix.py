import serial
import struct
import itertools

import libscrc
from cobs import cobs

from time import sleep



UNI_COLOR = 3
SET_PIXEL = 4
SET_FRAME = 10


class SerialHandler:
    def __init__(self, serial_name):
        self.ser = serial.Serial(serial_name, baudrate=115200)

    def send(self, msg):
        crc = libscrc.modbus(msg)
        msg = bytes([(crc & 0xFF00) >> 8, crc & 0x00FF]) + msg  # add CRC
        # print("Msg  : %s" % msg)
        encoded = cobs.encode(msg) + b'\x00'  # encode with COBS
        # print("Send : %s" % encoded)
        self.ser.write(encoded)  # send


class SmartMatrix(SerialHandler):
    def __init__(self, serial_name):
        super().__init__(serial_name)

    def pixel(self, x, y, r, g, b, w, refresh=True):
        #todo: refresh
        self.send(bytes([0, 0, SET_PIXEL, x, y, r, g, b, w]))

    def fill(self, r, g, b, w, refresh=True):
        #todo: refresh
        self.send(bytes([0, 0, UNI_COLOR, r, g, b, w]))

    def refresh(self):
        #todo : force a refresh after sending messages with "refresh=False".
        pass

if __name__ == "__main__":
    # test code

    from sys import argv
    if len(argv) > 1:
        port = argv[1]
    else:
        port = "/dev/ttyUSB0"
        print("Use default port %s\nYou can use $ %s <port>" % (port, argv[0]))

    print("Connection to the matrix ...")
    sm = SmartMatrix(serial_name=port)

    print("Send 3 times a full-screen color")
    for i in range(3):
        sm.fill(255, 0, 0, 0)
        sleep(.5)
        sm.fill(0, 255, 0, 0)
        sleep(.5)
        sm.fill(0, 0, 255, 0)
        sleep(.5)
        sm.fill(0, 0, 0, 255)
        sleep(.5)

    print("Test all the pixels")
    for i in range(3):
        for r, g, b, w in itertools.cycle([
             (255, 0, 0, 0),
             (0, 255, 0, 0),
             (0, 0, 255, 0),
             (0, 0, 0, 255),
            ]):
            for x in range(0, 20):
                for y in range(0, 15):
                    sm.pixel(x, y, r, g, b, w)
                    sleep(.06)

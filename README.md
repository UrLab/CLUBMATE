C.L.U.B.M.A.T.E.
=======
## Cyber Lightbubble Ultra Bright Managing Arbitrary Text Enhanced

We are building a large led matrix with Club-Mate crates @urlab.

![Showing urlab text on C.L.U.B.M.A.T.E.](https://framapic.org/l3dHXUKKojOr/PqEPaVc097nu.jpg)

See [our incubator (fr)](https://urlab.be/projects/74).

Structure :
---------
- There is a Club-Mate [crates matrix](#Crates-and-soldering) plug to ...
- an [arduino reading data](arduino_matrix/README.md) in [serial](arduino_matrix/serial.md) from a
- raspberry pi (with its [API](#Local-API)) available through
- the network ([internet API](#Internet-API)).

TODO: add schema here


### Crates and soldering

TODO:
* documentation about hardware
* include PCB sketch


### Local API

TODO:
* a python API to wrap the serial communication with the arduino (maybe use [this](https://github.com/bakercp/PacketSerial) ?)
* a "smart server" (with priority queue ?) to feed the serial with data from different sources


### Internet API

TODO:
* some web API to feed the server and fetch some metrix from outside
* a MQTT client to include the matrix in HAL1 (see [project](https://urlab.be/projects/84) and [wiki](https://urlab.be/wiki/hal1/))

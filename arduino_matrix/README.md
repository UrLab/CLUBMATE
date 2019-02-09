Arduino code
---------

For insides about the code, see [doc](doc/)


How to build :
---------

Start by fetching library/submodule :
`git submodule update --init --recursive`

Then compile and upload :

`pio run`

`pio run --target upload`

To specify a device :

`pio run -e uno --target upload`

`pio run -e mega --target upload`


Useful commands :
---------
* `pio run` - process/build project from the current directory
* `pio run -t upload` - upload firmware to a target
* `pio run --target clean` - clean project (remove compiled files)
* `pio run --help` - additional information


TODO :
---------
* Being able to read/write data on serial to receive row/column/bitmap from serial
* Store some config about the shape of the matrix in eeprom

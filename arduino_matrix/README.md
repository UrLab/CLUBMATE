How to :
---------

Start by fetching library/submodule :
`git submodule update --init --recursive`

Then compile and upload :

`pio run`

`pio run --target upload`


Useful commands :
---------
* `pio run` - process/build project from the current directory
* `pio run -t upload` - upload firmware to a target
* `pio run --target clean` - clean project (remove compiled files)
* `pio run --help` - additional information


Doc :
---------
Pixel are store in int of 32 bits `uint32_t`. Each color is on 8 bits:
00000000 00000000 00000000 00000000
  BLUE    GREEN     RED     WHITE

```
uint8_t white_= pixels;
uint8_t red = pixels >> 8;
uint8_t green = pixels >> 16;
uint8_t blue = pixels >> 24;
```


* `CMMatrix(uint8_t width, uint8_t height, coord* crate_order);`
  * Width/height of the matrix in pixel
  * List coordinates of each crate in "wire order" ex: {{0, 0}, {0, 1}}

* `uint32_t mget(uint8_t x, uint8_t y);`
  * get pixel at x, y
* `void mset(uint8_t x, uint8_t y, uint32_t v);`
  * set pixel at x, y

* Push row/column on a size of the matrix to rotate the whol content :
  * `void push_right(uint32_t* column);`
  * `void push_left(uint32_t* column);`
  * `void push_bottom(uint32_t* column);`
  * `void push_top(uint32_t* column);`

* `uint32_t* render();`
  * render the matrix as an array of led to send in the wire

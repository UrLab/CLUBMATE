How the matrix and leds are handled :
---------
Pixel are store in int of 32 bits `uint32_t`. Each color is on 8 bits:
<table>
  <tr>
    <td>00000000</td>
    <td>00000000</td>
    <td>00000000</td>
    <td>00000000</td>
  </tr>
  <tr>
    <td>RED</td>
    <td>GREEN</td>
    <td>BLUE</td>
    <td>WHITE</td>
  </tr>
</table>

```
uint8_t white_= pixels;
uint8_t red = pixels >> 8;
uint8_t green = pixels >> 16;
uint8_t blue = pixels >> 24;
```


* `CMMatrix(uint8_t width, uint8_t height, coord* crate_order, coord* in_crate_order);`
  * Width/height of the matrix in pixel
  * List coordinates of each crate in "wire order" ex: {{0, 0}, {0, 1}}
  * List coordinates of each led in a crate in "wire order" ex: {{0, 0}, {0, 1}}

* `uint32_t mget(uint8_t x, uint8_t y);`
  * get pixel at x, y
* `void mset(uint8_t x, uint8_t y, uint32_t v);`
  * set pixel at x, y

* Push new row/column on a side of the matrix to rotate the whole content :
  * `void push_right(uint32_t* column);`
  * `void push_left(uint32_t* column);`
  * `void push_bottom(uint32_t* row);`
  * `void push_top(uint32_t* row);`

* `uint32_t* render();`
  * render the matrix as an array of led to "send in the wire"

/*
 * 0 -> 127: server to matrix
 * 128 -> 255: matrix to server
 */

/*
 * Server to matrix
 */

//send shape of the matrix as an array of  { {x, y}, (...) }
#define INIT_MATRIX 1

//reset EEPROM with default param'
#define RESET 2

//send a color to fill the matrix
#define UNI_COLOR 3

//send a pixel {x, y, r, g, b, w}
#define SET_PIXEL 4

//send array of pixels: size, { {x, y, r, g, b, w}, (...) }
#define SET_PIXELS 5

//send row
#define TOP_ROW 6
#define BOTTOM_ROW 7

//send column
#define RIGHT_COLUMN 8
#define LEFT_COLUMN 9

//send frame
#define FRAME 10


/*
 * Matrix to server
 */
// I do not understand your message
#define MSG_BAD_MSG 129
// Corrupted message
#define MSG_WRONG_CRC 130

// Everything is fine ! <3
#define OK 200

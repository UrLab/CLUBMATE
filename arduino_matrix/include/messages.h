/*
 * 0 -> 127: server to matrix
 * 128 -> 255: matrix to server
 */

/*
 * Server to matrix
 */

//send shape of the matrix as an array of  { {x, y}, (...) }
#define INIT_MATRIX 1

//send a color to fill the matrix
#define UNI_COLOR 2

//TODO

/*
 * Matrix to server
 */
#define MSG_BAD_MSG 129
#define MSG_WRONG_CRC 130
//TODO

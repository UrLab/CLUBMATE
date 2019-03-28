#ifndef snake_h
  #define snake_h

#include "rollingMatrix.h"

void printMap(CMMatrix);
void printScore(CMMatrix cm);
void initMap();
bool move(int, int);
bool updateSnake();
void changeDir();
void generateFood();
char getMapValue(int value);
void reinitSnake();

#endif

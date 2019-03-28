#ifndef gameLife_h
  #define gameLife_h

#include "rollingMatrix.h"
#include "constant.h"

void initGame();
int countNeighbours(int x, int y);
void update();
void copyMatrix();
void CreateGlider();
void display(CMMatrix cm);
void fillMatrix(bool);

#endif

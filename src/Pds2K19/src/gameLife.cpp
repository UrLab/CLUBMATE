#include "gameLife.h"
#include <Arduino.h>
#include "utils.h"
#include "constant.h"

bool currentState[MATRIX_W][MATRIX_H];
bool lastState[MATRIX_W][MATRIX_H];

void initGame(){
  for(int x=0;x<MATRIX_W;x++){
    for(int y=0;y<MATRIX_H;y++){
      currentState[x][y] = (bool)random(2);
    }
  }
}

void CreateGlider(){
  currentState[0][3] = true;
  currentState[1][3] = true;
  currentState[2][3] = true;
  currentState[2][2] = true;
  currentState[1][1] = true;
}

void fillMatrix(bool whatTheFill){
  for(int x=0;x<MATRIX_W;x++){
    for(int y=0;y<MATRIX_H;y++){
      currentState[x][y] = whatTheFill;
    }
  }
}

int countNeighbours(int x, int y){
  int aliveNeighbours = 0;
  for(int deltaColumn=-1;deltaColumn < 2;deltaColumn++){
    for(int deltaRow=-1;deltaRow < 2;deltaRow++){
      if(deltaRow != 0 || deltaColumn != 0){
        if(y+deltaRow >= 0 && y+deltaRow < MATRIX_H && x+deltaColumn >= 0 && x+deltaColumn < MATRIX_W){
          aliveNeighbours += (int)lastState[x+deltaColumn][y+deltaRow];
        }
      }
    }
  }
  return aliveNeighbours;
}

void update(){
  for(int x=0;x<MATRIX_W;x++){
    for(int y=0;y<MATRIX_H;y++){
      int nbNeighbours = countNeighbours(x, y);
      if(lastState[x][y]){
        if(nbNeighbours < 2 || nbNeighbours > 3){
          currentState[x][y] = false;
        }
      }
      else if(nbNeighbours == 3){
          currentState[x][y] = true;
      }
    }
  }
}

void copyMatrix(){
  for(int x=0;x<MATRIX_W;x++){
    for(int y=0;y<MATRIX_H;y++){
       lastState[x][y] = currentState[x][y];
    }
  }
}

void display(CMMatrix cm){
  for(int x=0;x<MATRIX_W;x++){
    for(int y=0;y<MATRIX_H;y++){
      if(currentState[x][y]){
        cm.mset(x, y, 0, 255, 0, 0);
      }else{
        cm.mset(x, y, 0, 0, 0, 0);
      }
    }
  }
  draw(cm.render(), NUM_LEDS);
}

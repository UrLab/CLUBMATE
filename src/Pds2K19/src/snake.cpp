#include <Arduino.h>
#include "snake.h"
#include "rollingMatrix.h"
#include "constant.h"
#include "utils.h"

// Map dimensions
const int mapwidth = 20;
const int mapheight = 15;
int HighestScore = 38;

const int size = mapwidth * mapheight;

// The tile values for the map
int mapArray[size];

// Snake head details
int headxpos;
int headypos;
int direction;

// Amount of food the snake has (How long the body is)
int food = 0;
int snak_size = 3;


void reinitSnake(){
  food = 0;
  snak_size = 3;
  for(int x=0;x<size;x++){
    mapArray[x] = NULL;
  }
  initMap();
}

bool move(int dx, int dy) {
    // determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // Check if there is food at location
    if (mapArray[newx + newy * mapwidth] == -2) {
        // Increase food value (body length)
        food++;
        snak_size++;

        // Generate new food on map
        generateFood();
    }

    // Check location is free
    else if (mapArray[newx + newy * mapwidth] != 0) {
      return false;
    }

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    mapArray[headxpos + headypos * mapwidth] = snak_size + 1;
    return true;
}

void generateFood(){
  int x = 0;
  int y = 0;
  do {
    // Generate random x and y values within the map
    x = random() % (mapwidth - 2) + 1;
    y = random() % (mapheight - 2) + 1;

    // If location is not free try again
  } while (mapArray[x + y * mapwidth] != 0);

  // Place new food
  mapArray[x + y * mapwidth] = -2;
}

void changeDir(){
  if(!digitalRead(5)){
    if (direction != 2) direction = 0;
  }else if(!digitalRead(2)){
    if (direction != 3) direction = 1;
  }else if(!digitalRead(3)){
    if (direction != 0) direction = 2;
  }else if(!digitalRead(4)){
    if (direction != 1) direction = 3;
  }
}

void printScore(CMMatrix cm){
  int nbLoop = HighestScore;
  if(food > HighestScore){
    nbLoop = food;
  }
  for(int count=0;count<nbLoop;count++){
    if(count < food){
      cm.mset(count%20, 5+count/20, 0, 0, 255, 0);
    }else{
      cm.mset(count%20, 5+count/20, 255, 0, 0, 0);
    }
    if(count > HighestScore){
      cm.mset(count%20, 5+count/20, 0, 255, 0, 0);
    }
    draw(cm.render(), NUM_LEDS);
    delay(50);
  }
  if(food > HighestScore){
    HighestScore = food;
  }
}

bool updateSnake() {
  bool res = true;
  switch(direction){
    case 0:
      res = move(-1, 0);
      break;
    case 1:
      res = move(0, 1);
      break;
    case 2:
      res = move(1, 0);
      break;
    case 3:
      res = move(0, -1);
      break;
  }

  // Reduce snake values on map by 1
  for (int i = 0; i < size; i++) {
      if (mapArray[i] > 0) mapArray[i]--;
  }
  return res;
}

void initMap(){
    // Places the initual head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    mapArray[headxpos + headypos * mapwidth] = 1;

    // Places top and bottom walls
    for (int x = 0; x < mapwidth; ++x) {
        mapArray[x] = -1;
        mapArray[x + (mapheight - 1) * mapwidth] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < mapheight; y++) {
        mapArray[0 + y * mapwidth] = -1;
        mapArray[(mapwidth - 1) + y * mapwidth] = -1;
    }

    // Generates first food
    generateFood();
}

void printMap(CMMatrix cm){
    for (int x = 0; x < mapwidth; ++x) {
      for (int y = 0; y < mapheight; ++y) {
        // Prints the value at current x,y location
        if(getMapValue(mapArray[x + y * mapwidth]) == 'o'){
          cm.mset(x, y, 0, 255, 0, 0);
        }else if(getMapValue(mapArray[x + y * mapwidth]) == 'X'){
          cm.mset(x, y, 0, 0, 255, 0);
        }else if(getMapValue(mapArray[x + y * mapwidth]) == 'O'){
          cm.mset(x, y, 255, 0, 0, 0);
        }else if(getMapValue(mapArray[x + y * mapwidth]) == ' '){
          cm.mset(x, y, 0, 0, 0, 0);
        }
      }
    }
    draw(cm.render(), NUM_LEDS);
}

char getMapValue(int value){
  // Returns a part of snake body
  if (value > 0) return 'o';

  switch (value) {
      case -1:
        return 'X';
        break;
      case -2:
        return 'O';
        break;
  }
  return ' ';
}

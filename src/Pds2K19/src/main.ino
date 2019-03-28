/*
  Author : minigrim0
  last Update : 22/03/2019
*/
#include <math.h>
#include "gameLife.h"
#include "snake.h"

#include "../lib/FAB_LED/FAB_LED.h"
#include "rollingMatrix.h"
#include "constant.h"

#define BUTTONUP    4
#define BUTTONDOWN  2
#define BUTTONLEFT  5
#define BUTTONRIGHT 3

int startTime = millis();
int timeElapsed = 0;

int lastAnalog = 0;

bool playing = true;

coord matrix_shape[15] = {
        {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0},
        {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1},
        {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}
};

coord in_crate_order[20] = {
        {0, 0}, {1, 0}, {2, 0}, {3, 0},
        {3, 1}, {2, 1}, {1, 1}, {0, 1},
        {0, 2}, {1, 2}, {2, 2}, {3, 2},
        {3, 3}, {2, 3}, {1, 3}, {0, 3},
        {0, 4}, {1, 4}, {2, 4}, {3, 4},
};

CMMatrix cm(20, 15, matrix_shape, 20, 4, 5, in_crate_order);

void setup() {
  randomSeed(analogRead(0));

  cm.fill(255, 0, 0, 0);
  draw(cm.render(), NUM_LEDS);
  delay(500);
  initGame();
  initMap();
}

void blinkDie(){
  for(int x=0;x<5;x++){
    cm.fill(random()%255, random()%255, random()%255, 0);
    draw(cm.render(), NUM_LEDS);
    delay(50);
  }
  cm.fill(0, 0, 0, 0);

  //THE
  for(int x=2;x<7;x++)            //T upbar
    cm.mset(x, 0, 255, 0, 0, 0);  //T

  for(int x=1;x<5;x++)            //T middlebar
    cm.mset(4, x, 255, 0, 0, 0);  //T

  for(int x=0;x<5;x++)            //H left bar
    cm.mset(8, x, 255, 0, 0, 0);  //H left bar

  for(int x=0;x<5;x++)            //H right bar
    cm.mset(11, x, 255, 0, 0, 0); //H right bar

  cm.mset(9, 2, 255, 0, 0, 0);    //H middle bar
  cm.mset(10, 2, 255, 0, 0, 0);   //H middle bar

  for(int x=0;x<5;x++)            //E left bar
    cm.mset(14, x, 255, 0, 0, 0); //E left bar

  for(int x=15;x<18;x++)          //E up bar
    cm.mset(x, 0, 255, 0, 0, 0);  //E up bar

  for(int x=15;x<18;x++)          //E down bar
    cm.mset(x, 4, 255, 0, 0, 0);  //E down bar

  cm.mset(15, 2, 255, 0, 0, 0);   //E middle bar
  cm.mset(16, 2, 255, 0, 0, 0);   //E middle bar

  //END
  for(int x=10;x<15;x++)          //E left bar
    cm.mset(2, x, 255, 0, 0, 0);  //E left bar

  for(int x=3;x<6;x++)            //E up bar
    cm.mset(x, 10, 255, 0, 0, 0); //E up bar

  for(int x=3;x<6;x++)            //E down bar
    cm.mset(x, 14, 255, 0, 0, 0); //E down bar

  cm.mset(3, 12, 255, 0, 0, 0);   //E middle hor bar
  cm.mset(4, 12, 255, 0, 0, 0);   //E middle hor bar

  for(int x=10;x<15;x++)          //N left bar
    cm.mset(8, x, 255, 0, 0, 0);  //N left bar

  for(int x=10;x<15;x++)          //N right bar
    cm.mset(11, x, 255, 0, 0, 0); //N right bar

  cm.mset(9, 11, 255, 0, 0, 0);   //N middle bar
  cm.mset(9, 12, 255, 0, 0, 0);   //N middle bar
  cm.mset(10, 12, 255, 0, 0, 0);  //N middle bar
  cm.mset(10, 13, 255, 0, 0, 0);  //N middle bar

  for(int x=10;x<15;x++)          //D left bar
    cm.mset(14, x, 255, 0, 0, 0); //D left bar

  cm.mset(15, 10, 255,0, 0, 0);   //D up hor and down hor
  cm.mset(15, 14, 255,0, 0, 0);   //D up hor and down hor
  cm.mset(16, 10, 255,0, 0, 0);   //D up hor and down hor
  cm.mset(16, 14, 255,0, 0, 0);   //D up hor and down hor

  for(int x=11;x<14;x++)          //D right bar
    cm.mset(17, x, 255, 0, 0, 0); //D right bar

  draw(cm.render(), NUM_LEDS);
  printScore(cm);
  delay(2500);
}

void blinkLong(){
  cm.fill(255, 255, 255, 0);
  delay(400);
  draw(cm.render(), NUM_LEDS);
  cm.fill(0, 0, 0, 0);
  delay(400);
  draw(cm.render(), NUM_LEDS);

}

void blinkShort(){
  cm.fill(255, 255, 255, 0);
  delay(150);
  draw(cm.render(), NUM_LEDS);
  cm.fill(0, 0, 0, 0);
  delay(150);
  draw(cm.render(), NUM_LEDS);
}

void loop() {
  timeElapsed += millis()-startTime;
  startTime = millis();
  if(analogRead(A2) > 1020 && lastAnalog < 1000){
    initGame();
    timeElapsed = 0;
  }else if(analogRead(A2) < 1000 && lastAnalog > 1020){
    initGame();
    timeElapsed = 0;
  }

  lastAnalog = analogRead(A2);
  if(analogRead(A2) > 1020){

    if(!digitalRead(BUTTONUP)) initGame();
    if(!digitalRead(BUTTONDOWN)) CreateGlider();
    if(!digitalRead(BUTTONLEFT)) fillMatrix(false);

    if(!digitalRead(BUTTONRIGHT)){
      for(int x=0;x<2;x++)
        blinkLong();

      delay(200);

      for(int x=0;x<3;x++)
        blinkLong();

      delay(200);

      blinkShort();
      blinkLong();
      blinkShort();

      delay(200);

      for(int x=0;x<3;x++)
        blinkShort();

      delay(200);

      blinkLong();

      delay(200);

      for(int x=0;x<2;x++)
        blinkShort();

      delay(500);

      initGame();
    }
    if(timeElapsed > (2048.0-2.0*analogRead(A1))){
      timeElapsed = 0;
      copyMatrix();
      display(cm);
      update();
    }
  }else{
    changeDir();
    if(timeElapsed > (2048.0-2.0*analogRead(A1))){
      timeElapsed = 0;
      playing = updateSnake();
      printMap(cm);
      if(playing == false){
        blinkDie();
        reinitSnake();
      }
    }
  }
}

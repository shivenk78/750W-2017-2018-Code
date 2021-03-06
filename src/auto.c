#include "main.h"

int distance;
int enc;
int dir;
int selector;
bool side; //TRUE = left FALSE = right

int claw = 10;
int frontleft = 2;
int frontright = 3;
int mainlift = 5;
int chainlift = 4;
int mobileliftleft = 6;
int mobileliftright = 7;
int backright = 8;
int backleft = 9;

void mogoDown(){
  motorSet(mobileliftleft,127);
  motorSet(mobileliftright,127);
  delay(950); //Lowers Mobile Goal Lift
  motorStop(mobileliftleft);
  motorStop(mobileliftright);
}
void moGoDown(int del){
  motorSet(mobileliftleft,127);
  motorSet(mobileliftright,127);
  delay(del); //Lowers Mobile Goal Lift
  motorStop(mobileliftleft);
  motorStop(mobileliftright);
}
void mogoUp(){
  motorSet(mobileliftleft,-127);
  motorSet(mobileliftright,-127);
  delay(800); //Raises Mobile Goal
  motorStop(mobileliftleft);
  motorStop(mobileliftright);
}
void forward(int del){
  motorSet(backright,-127);
  motorSet(backleft,-127);
  motorSet(frontright,-127);
  motorSet(frontleft,-127);
  delay(del);
  motorStop(backright);
  motorStop(backleft);
  motorStop(frontright);
  motorStop(frontleft);
}
void enForward(int dist){
  encoderReset(encoder);
  enc = encoderGet(encoder);
  while(enc<dist){
    enc = encoderGet(encoder);
    motorSet(backright,-127);
    motorSet(backleft,-127);
    motorSet(frontright,-127);
    motorSet(frontleft,-127);
  }
  motorStop(backright);
  motorStop(backleft);
  motorStop(frontright);
  motorStop(frontleft);
}
void reverse(int del){
  motorSet(backright,127);
  motorSet(backleft,127);
  motorSet(frontright,127);
  motorSet(frontleft,127);
  delay(del);
  motorStop(backright);
  motorStop(backleft);
  motorStop(frontright);
  motorStop(frontleft);
}
void slowReverse(int del){
  motorSet(backright,30);
  motorSet(backleft,30);
  motorSet(frontright,30);
  motorSet(frontleft,30);
  delay(del);
  motorStop(backright);
  motorStop(backleft);
  motorStop(frontright);
  motorStop(frontleft);
}
void preload(){
  motorSet(chainlift,80);
  motorSet(claw,127);
  delay(1000);
  motorSet(chainlift,-80);
  motorSet(claw,127);
  delay(1200);
  motorStop(chainlift);
  delay(500);
  motorSet(claw,-127);
  delay(1500);
  motorStop(chainlift);
  motorStop(claw);
}

void  coneLoad(){
  motorSet(chainlift,80);
  motorSet(claw,127);
  delay(1400);
  motorSet(chainlift,-80);
  delay(1200);
  motorStop(chainlift);
  delay(600);
  motorSet(claw,-127);
  delay(1700);
  motorStop(chainlift);
  motorStop(claw);
}
void turnLeft(int angle){
  gyroReset(gyro);
    dir = gyroGet(gyro);
    dir+=4;
    while(abs(dir)<angle){
      dir = gyroGet(gyro);
      motorSet(backright,-127);
      motorSet(backleft,127);
      motorSet(frontright,-127);
      motorSet(frontleft,127);
    }
    motorStop(backright);
    motorStop(backleft);
    motorStop(frontright);
    motorStop(frontleft);
}
void slowturnLeft(int angle){
  gyroReset(gyro);
    dir = gyroGet(gyro);
    dir+=4;
    while(abs(dir)<angle){
      dir = gyroGet(gyro);
      motorSet(backright,-35);
      motorSet(backleft,35);
      motorSet(frontright,-35);
      motorSet(frontleft,35);
    }
    motorStop(backright);
    motorStop(backleft);
    motorStop(frontright);
    motorStop(frontleft);
}
void turnRight(int angle){
  gyroReset(gyro);
  dir = gyroGet(gyro);
  dir+=4;
    while(abs(dir)<angle){
      dir = gyroGet(gyro); //Right Auton
      motorSet(backright,127);
      motorSet(backleft,-127);
      motorSet(frontright,127);
      motorSet(frontleft,-127);
    }
    motorStop(backright);
    motorStop(backleft);
    motorStop(frontright);
    motorStop(frontleft);
}
void liftUp(int del){
  motorSet(mainlift,127);
  delay(del);
  motorStop(mainlift);
}
void autonomous() {

  distance = ultrasonicGet(mogoSonar);
  dir = gyroGet(gyro);
  selector = analogReadCalibrated(1);

  lcdPrint(uart1,1,"Bat: %1.3f V",(double)powerLevelMain()/1000);
  lcdSetText(uart1,2,"<<750 WOLVES>>");

  gyroReset(gyro);

  if(digitalRead(3)==LOW){
    //first
    mogoDown();
    forward(1200);
    mogoUp();
    preload();
    reverse(1250);
    turnRight(154);
    forward(500);
    moGoDown(800);
    //second
    reverse(600);
    slowturnLeft(175);
    //slowReverse(1300);
    forward(2200);
    mogoUp();
    forward(800);
    moGoDown(700);
    //third
    reverse(380);
    moGoDown(200);
    turnLeft(57);
    enForward(600);
    turnLeft(62);
    forward(1350);
    mogoUp();
    reverse(1400);
    turnRight(155);
    forward(600);
    moGoDown(700);
    //fourth
    reverse(600);
    moGoDown(200);
    turnLeft(155);
    forward(2300);
    mogoUp();
    forward(1000);
    mogoDown();
    moGoDown(300);
    //fifth
    reverse(350);
    turnRight(65);
    forward(400);
    turnRight(20);
    forward(1750);
    mogoUp();
    reverse(1400);
    turnLeft(170);
    motorSet(backright,50);
    motorSet(backleft,127);
    motorSet(frontright,50);
    motorSet(frontleft,127);
    delay(2000);
    motorStop(backright);
    motorStop(backleft);
    motorStop(frontright);
    motorStop(frontleft);
    mogoDown();
    reverse(1500);
    //park
    reverse(1000);
    turnLeft(50);
    reverse(700);
  }
  else{
    if(selector>2500){ //LEFT AUTON ////////////////////////////////
      liftUp(100);
      mogoDown();
      forward(1500);
       //Goes forward until mobile goal is reached
      mogoUp();
      preload();
      //coneLoad();
      reverse(1000);
      turnLeft(170);
      forward(1000);
      turnRight(23);
      forward(300);
      mogoDown();
      reverse(700);
    }

    else if(selector<1000){ //RIGHT AUTON ////////////////////////////////
      liftUp(500);
      mogoDown();
      forward(1600);
       //Goes forward until mobile goal is reached 
      mogoUp();
      preload();
      //coneLoad();
      reverse(750);
      turnRight(180);
      forward(1400);
      turnLeft(18);
      forward(300);
      mogoDown();
      reverse(700);
    }
    else{
      //Off Auton ////////////////////////////////////////////////////
        liftUp(500);
        mogoDown();
        forward(1450);
         //Goes forward until mobile goal is reached
        mogoUp();
        preload();
        //forward(100);
        coneLoad();
        forward(100);
        coneLoad();
    }
  }
}

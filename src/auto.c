#include "main.h"
//Port Definitions
//8-frontleft
//3-backleft
//9-frontright
//5 backright
//6,7 mobile goal lift
//2-main lift
//4 chain bar lift
//1 claw

//1 - LiftRight
//2 - ChainbarRight
//3 - ChainbarLeft
//4 - LiftLeft
int distance;
int dir;
int selector;
bool side; //TRUE = left FALSE = right

void mogoDown(){
  motorSet(6,127);
  motorSet(7,127);
  delay(800); //Lowers Mobile Goal Lift
  motorStop(6);
  motorStop(7);
}
void mogoUp(){
  motorSet(6,-127);
  motorSet(7,-127);
  delay(700); //Raises Mobile Goal
  motorStop(6);
  motorStop(7);
}
void forward(int del){
  motorSet(8,-127);
  motorSet(3,-127);
  motorSet(9,127);
  motorSet(5,127);
  delay(del);
  motorStop(8);
  motorStop(3);
  motorStop(9);
  motorStop(5);
}
void reverse(int del){
  motorSet(8,127);
  motorSet(3,127);
  motorSet(9,-127);
  motorSet(5,-127);
  delay(del);
  motorStop(8);
  motorStop(3);
  motorStop(9);
  motorStop(5);
}
void preload(){
  motorSet(4,127);
  motorSet(1,127);
  delay(800);
  motorSet(4,-127);
  motorSet(1,127);
  delay(700);
  motorStop(4);
  delay(500);
  motorSet(1,-127);
  delay(500);
  motorStop(4);
  motorStop(1);
}
void turnLeft(int angle){
  gyroReset(gyro);
    dir = gyroGet(gyro);
    dir+=4;
    while(abs(dir)<angle){
      dir = gyroGet(gyro);
    motorSet(8,-127);
    motorSet(3,-127);
    motorSet(9,-127);
    motorSet(5,-127);
    }
    motorStop(8);
    motorStop(3);
    motorStop(9);
    motorStop(5);
}
void turnRight(int angle){
  gyroReset(gyro);
  dir = gyroGet(gyro);
  dir+=4;
    while(abs(dir)<170){
      dir = gyroGet(gyro); //Right Auton
    motorSet(8,127);
    motorSet(3,127);
    motorSet(9,127);
    motorSet(5,127);
    }
    motorStop(8);
    motorStop(3);
    motorStop(9);
    motorStop(5);
}
void liftUp(int del){
  motorSet(2,127);
  delay(del);
  motorStop(2);
}
void autonomous() {

  distance = ultrasonicGet(mogoSonar);
  dir = gyroGet(gyro);
  selector = analogReadCalibrated(1);

  gyroReset(gyro);
  if(selector>2500){ //LEFT AUTON ////////////////////////////////
    liftUp(500);

    mogoDown();
    forward(1750);
     //Goes forward until mobile goal is reached
    mogoUp();
    preload();
    reverse(1000);

    turnLeft(170);
    forward(2500);
    mogoDown();
    reverse(1500);
  }

  else if(selector<1000){ //RIGHT AUTON ////////////////////////////////
    liftUp(500);

    mogoDown();
    forward(1750);
     //Goes forward until mobile goal is reached
    mogoUp();
    preload();
    reverse(1500);

    turnRight(170);
    forward(1500);
    mogoDown();
    reverse(1500);
  }

}

/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
*/
//Port Definitions
//6,7 mobile goal lift
//8-main lift
//9 chain bar lift
//10 claw
//1 - LiftRight
//2 - ChainbarRight
//3 - ChainbarLeft
//4 - LiftLeft
//2, 3 left
//4, 5 right
int distance;
bool side = false; //TRUE = left FALSE = right
void autonomous() {
  distance = ultrasonicGet(sonar);
  motorSet(6,127);
  motorSet(7,127);
  delay(800); //Lowers Mobile Goal Lift
  motorStop(6);
  motorStop(7);

    motorSet(2,-127);
    motorSet(3,-127);
    motorSet(4,127);
    motorSet(5,127);
    delay(1500);
    motorStop(2);
    motorStop(3);
    motorStop(4);
    motorStop(5);
   //Goes forward until mobile goal is reached
  motorSet(6,-127);
  motorSet(7,-127);
  delay(800); //Raises Mobile Goal
  motorStop(6);
  motorStop(7);
  if(side){
    motorSet(2,-127);
    motorSet(3,-127);
    motorSet(4,-127);
    motorSet(5,-127);
    delay(860); //Turns Left for LEFT AUTON
    motorStop(2);
    motorStop(3);
    motorStop(4);
    motorStop(5);
  }
  if(!side){
    motorSet(2,127);
    motorSet(3,127);
    motorSet(4,127);
    motorSet(5,127);
    delay(860); //Turns right for RIGHT AUTON
    motorStop(2);
    motorStop(3);
    motorStop(4);
    motorStop(5);
  }
  motorSet(2,-127);
  motorSet(3,-127);
  motorSet(4,127);
  motorSet(5,127);
  delay(2250);
  motorStop(2);
  motorStop(3);
  motorStop(4);
  motorStop(5);

  motorSet(6,127);
  motorSet(7,127);
  delay(800); //Lowers Mobile Goal Lift
  motorStop(6);
  motorStop(7);

  motorSet(2,127);
  motorSet(3,127);
  motorSet(4,-127);
  motorSet(5,-127);
  delay(500);
  motorStop(2);
  motorStop(3);
  motorStop(4);
  motorStop(5);

}

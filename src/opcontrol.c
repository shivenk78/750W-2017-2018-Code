/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
#define LIFT_RIGHT 1
#define CHAIN_RIGHT 2
#define CHAIN_LEFT 3
#define LIFT_LEFT 4

void operatorControl() {
	while (1) {
		int rightDrive;
		int leftDrive;
		int leftDrive2;
		int rightDrive2;
		bool liftUp;
		bool liftDown;
		bool chainUp;
		bool chainDown;
		bool clawOpen;
		bool clawClose;
		bool baseUp;
		bool baseDown;
		bool baseUp2;
		bool baseDown2;

		int leftLift;
		int leftChain;
		int rightChain;
		int rightLift;

		Ultrasonic sonar = ultrasonicInit(7,8);
		int ultraSonic = ultrasonicGet(sonar);

		int Ch3;
		int Ch4;
		int Ch3joy2;
		int Ch4joy2;

		//int LIFT_UPPER_LIMIT = 2040;
		int LIFT_LOWER_LIMIT = 560;
		//Port Definitions
		//2-frontleft
		//3-backleft
		//4-frontright
		//5 backright
		//6,7 mobile goal lift
		//8-main lift
		//9 chain bar lift
		//10 claw

		//1 - LiftRight
		//2 - ChainbarRight
		//3 - ChainbarLeft
		//4 - LiftLeft

		leftLift = analogReadCalibrated(LIFT_LEFT);
		leftChain = analogReadCalibrated(CHAIN_LEFT);
		rightChain = analogReadCalibrated(CHAIN_RIGHT);
		rightLift = analogReadCalibrated(LIFT_RIGHT);

		Ch3 = (abs(joystickGetAnalog(1, 3)) < 20) ? 0 : -joystickGetAnalog(1, 3);
		Ch4 = (abs(joystickGetAnalog(1, 4)) < 20) ? 0 : joystickGetAnalog(1, 4);
		Ch3joy2 = (abs(joystickGetAnalog(2, 3)) < 20) ? 0 : -joystickGetAnalog(2, 3);
		Ch4joy2 = (abs(joystickGetAnalog(2, 4)) < 20) ? 0 : joystickGetAnalog(2, 4);

		rightDrive = Ch4 - (2*Ch3);
		leftDrive = Ch4 + (2*Ch3);
		rightDrive2 = Ch4joy2 - (2*Ch3joy2);
		leftDrive2 = Ch4joy2 + (2*Ch3joy2);

		liftUp = joystickGetDigital(1, 5, JOY_UP);
		liftDown = joystickGetDigital(1, 5, JOY_DOWN);

		chainUp = joystickGetDigital(1, 8, JOY_UP);
		chainDown = joystickGetDigital(1, 8, JOY_DOWN);

		clawOpen = joystickGetDigital(1,6,JOY_DOWN);
		clawClose = joystickGetDigital(1, 6, JOY_UP);

		baseUp = joystickGetDigital(1,8,JOY_RIGHT);
		baseDown = joystickGetDigital(1,8,JOY_LEFT);
		baseUp2 = joystickGetDigital(2,6,JOY_UP);
		baseDown2 = joystickGetDigital(2,6,JOY_DOWN);

		//Single Stick Drive
		if(abs(leftDrive)>20){
		 motorSet(2,leftDrive);
		 motorSet(3,leftDrive);
	 }else{
		 motorStop(2);
		 motorStop(3);
	 }
	 if(abs(rightDrive)>20){
		 motorSet(4,rightDrive);
		 motorSet(5,rightDrive);
	 }else{
		 motorStop(4);
		 motorStop(5);
	 }
	 if(abs(leftDrive2)>20){
		motorSet(2,leftDrive2);
		motorSet(3,leftDrive2);
	}else{
		motorStop(2);
		motorStop(3);
	}
	if(abs(rightDrive2)>20){
		motorSet(4,rightDrive2);
		motorSet(5,rightDrive2);
	}else{
		motorStop(4);
		motorStop(5);
	}

			//Claw control
		if(clawOpen){
			motorSet(10, 127);
		}
		else if (clawClose){
			motorSet(10, -127);
		}
		else motorStop(10);

			//Lift control
		if (liftUp&&leftLift<LIFT_UPPER_LIMIT){
			motorSet(8, 127);
		}
		else if (liftDown&&leftLift>LIFT_LOWER_LIMIT){
			motorSet(8, -127);
		}
		else{
			motorStop(8);
		}

			//Chain lift control
		if (chainUp){
			motorSet(9, -127);
		}
		else if (chainDown){
			motorSet(9, 127);
		}
		else{
			motorStop(9);
		}

			//Mobile goal lift
		if (baseDown||baseDown2){
			motorSet(6, 127);
			motorSet(7, 127);
		}else if (baseUp||baseUp2){
			motorSet(6, -127);
			motorSet(7, -127);
		}
		else{
			motorStop(6);
			motorStop(7);
		}

		//First Cone Macro
		/*if (joystickGetDigital(1, 7, JOY_DOWN)){
			while(rightChain>870){
				motorSet(9, -127);
				rightChain = analogReadCalibrated(CHAIN_RIGHT);
			}
			motorStop(9);
			motorSet(10,127);
			delay(500);
		}*/

		//LCD
		lcdClear(uart1);
		lcdPrint(uart1,1,"LL %d US %d",leftLift,ultraSonic);
		lcdPrint(uart1,2,"LC %d RC %d",leftChain,rightChain);
		printf("LL: %d RL: %d \n",leftLift,rightLift);
		printf("LC: %d RC: %d \n",leftChain,rightChain);
		//TODO: Start System!
		delay(20);
	}


}

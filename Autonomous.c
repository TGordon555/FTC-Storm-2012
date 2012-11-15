#pragma config(Motor,  mtr_S1_C1_1,     backRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, openLoop)
#include "JoystickDriver.c"

#include "omniDrive.h"

OmniMotors motors;

task main() {
    waitForStart();
    
    motors.frontLeft  = frontLeft;
    motors.frontRight = frontRight;
    motors.backLeft   = backLeft;
    motors.backRight  = backRight;

    while(true) {
    }
}

#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          motorE,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorG,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorF,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorH,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorNone, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo2,               tServoNone)
#include "JoystickDriver.c"
void initializeRobot()
{
  return;
}
#pragma platform(Tetrix)
void omniDrive(int joyx, int joyy);
task main()
{
  initializeRobot();
while(true){
getJoystickSettings(joystick);
omniDrive(joystick.joy1_x1, joystick.joy1_y1);
  }
}
void omniDrive(int joyx, int joyy)
{
	int NmotorValue1, NmotorValue2;
	float FmotorValue1, FmotorValue2;
	if joy1btn()
 /* motor[motorD] =*/ FmotorValue1 = ((100.0/128)*(float)joyx + (100.0/128)*(float)joyy)/sqrt(2);
 /* motor[motorF] =*/ FmotorValue2 = ((100.0/128)*-(float)joyx + (100.0/128)*(float)joyy)/sqrt(2);
//FmotorValue1 = ((100.0/128.0)*(float)joyx);
NmotorValue1 = FmotorValue1;
motor[motorE] = NmotorValue1;
//FmotorValue2 = ((100.0/128.0)*(float)joyy);
NmotorValue2 = FmotorValue2;
motor[motorG] = NmotorValue2;
writeDebugStreamLine("(%d, %d, %d, %d)",NmotorValue1, NmotorValue2, joyx, joyy);
}


#include "JoystickDriver.c"
#include "ProportionalControl.h"
#include "range.h"

task main()
{
    ProportionalSettings settings;
    settings.kP        = 2;
    settings.maxError  = 5;
    settings.minOutput = -100;
    settings.maxOutput = 100;

    float roughSetpoint = 0,
          fineSetpoint  = 0;

    while(1) {
        getJoystickSettings(joystick);
        if(joy1Btn(5)) {
            roughSetpoint = scaleJoystickValue(-720,720,joystick.joy1_y1);
        }
        if(joy1Btn(6)) {
            fineSetpoint  = scaleJoystickValue(-90,90,joystick.joy1_y2);
        }
        nxtDisplayCenteredTextLine(4,"%d: %d",joystick.joy1_y1,nMotorEncoder[motorA]);
        proportionalControl(motorA,settings,roughSetpoint+fineSetpoint);
    }
}

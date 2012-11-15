#ifndef OMNIDRIVE_H
#define OMNIDRIVE_H

typedef struct {
    tMotor frontLeft,
           frontRight,
           backLeft,
           backRight;
} OmniMotors;

void omniDrive(OmniMotors motors,float x, float y, float scale, float spin) {
    int upRightSpeed = (x + y)  / sqrt(2);
    int upLeftSpeed  = (-x + y) / sqrt(2);

    int frontRightSpeed = clamp(upLeftSpeed  - spin,-100,100) * scale,
        frontLeftSpeed  = clamp(upRightSpeed + spin,-100,100) * scale,
        backRightSpeed  = clamp(upRightSpeed - spin,-100,100) * scale,
        backLeftSpeed   = clamp(upLeftSpeed  + spin,-100,100) * scale;

    motor[motors.frontLeft]  = frontLeftSpeed;
    motor[motors.backRight]  = backRightSpeed;
    motor[motors.backLeft]   = backLeftSpeed;
    motor[motors.frontRight] = frontRightSpeed;

    //writeDebugStreamLine("frontRight:%d,frontLeft:%d,backRight:%d,backLeft:%d", frontRightSpeed,frontLeftSpeed,backRightSpeed,backLeftSpeed);
}

void omniDrivePolar(OmniMotors motors,float speed,float angle) {
    float x = speed*cosDegrees(angle),
          y = speed*sinDegrees(angle);
    omniDrive(motors,x,y,1,0);
}

#endif

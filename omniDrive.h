#ifndef OMNIDRIVE_H
#define OMNIDRIVE_H

#include "range.h"


#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct {
  tMotor frontLeft;
  tMotor frontRight;
  tMotor backLeft;
  tMotor backRight;
} OmniMotors;


/**
 * Set the motor speeds from 2d velocity vector
 * @param motors      a map of motor position to motor id
 * @param vx          the velocity direction component in the x direction
 * @param vy          the velocity direction component in the y direction
 * @param mag         the output magnitude (-100 to 100 inclusive)0
 * @param spin        spin power. when used in combination with velocity this will do swing turn
 */
void omniDrive( OmniMotors motors, float vx, float vy, float mag, float spin ) {
  // project the velocity into the wheel planes
  float upRightSpeed = (vx + vy)  * M_SQRT1_2;
  float upLeftSpeed  = (-vx + vy) * M_SQRT1_2;

  // mix the wheel plane velocity with a forward bias and a spin
  // TODO: fix different units
  float frontRightSpeed = upLeftSpeed  - spin;
  float frontLeftSpeed  = upRightSpeed + spin;
  float backRightSpeed  = upRightSpeed - spin;
  float backLeftSpeed   = upLeftSpeed  + spin;

  // normalize motor power
#ifdef USE_AGRESSIVE_NORMALIZATION
  float recipNorm = 1.0 /
                    sqrt( frontRightSpeed*frontRightSpeed + frontLeftSpeed*frontLeftSpeed +
                          backRightSpeed*backRightSpeed + backLeftSpeed*backLeftSpeed );
#else
  float recipNorm = 1.0 /
                    max( max( frontRightSpeed, frontLeftSpeed ),
                         max( backRightSpeed, backLeftSpeed ) );
#endif

  // apply motor power
  motor[motors.frontLeft]  = clamp( frontLeftSpeed*recipNorm*mag,  -100, 100 );
  motor[motors.backRight]  = clamp( backRightSpeed*recipNorm*mag,  -100, 100 );
  motor[motors.backLeft]   = clamp( backLeftSpeed*recipNorm*mag,   -100, 100 );
  motor[motors.frontRight] = clamp( frontRightSpeed*recipNorm*mag, -100, 100 );
}

void omniDrivePolar( OmniMotors motors, float speed, float angleDeg ) {
    float x = cosDegrees( angleDeg );
    float y = sinDegrees( angleDeg );
    omniDrive( motors, x, y, speed, 0 );
}

#endif

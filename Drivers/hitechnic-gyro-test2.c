#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-gyro-test2.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * hitechnic-gyro.h provides an API for the HiTechnic Gyroscopic Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 06 April 2012
 * version 0.1
 */

#include "drivers/hitechnic-gyro.h"

task main ()
{
  float rotSpeed = 0;
  float heading = 0;

  // Calibrate the gyro, make sure you hold the sensor still
  HTGYROstartCal(HTGYRO);

  // Reset the timer.
  time1[T1] = 0;

  while (true)
  {
    // Wait until 20ms has passed
    while (time1[T1] < 20)
      wait1Msec(1);

    // Reset the timer
    time1[T1]=0;

    // Read the current rotation speed
    rotSpeed = HTGYROreadRot(HTGYRO);

    // Calculate the new heading by adding the amount of degrees
    // we've turned in the last 20ms
    // If our current rate of rotation is 100 degrees/second,
    // then we will have turned 100 * (20/1000) = 2 degrees since
    // the last time we measured.
    heading += rotSpeed * 0.02;

    // Display our current heading on the screen
    nxtDisplayCenteredBigTextLine(3, "%2.0f", heading);
  }
}

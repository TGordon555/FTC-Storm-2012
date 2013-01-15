#pragma config(Sensor, S1,     HTCS2,               sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-colour-v2-test2.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * hitechnic-colour-v2.h provides an API for the HiTechnic Color V2 Sensor.  This program
 * demonstrates how to use that API.
 *
 * For a short youTube video about this program: http://www.youtube.com/watch?v=RZRQBfw46CM
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 * - 0.3: Removed common.h from includes
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 20 February 2011
 * version 0.3
 */

#include "drivers/hitechnic-colour-v2.h"

task main () {
  long red = 0;
  long green = 0;
  long blue = 0;
  bool passive = false;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Color V2");
  nxtDisplayCenteredTextLine(3, "Test 2");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  nxtDisplayCenteredTextLine(7, "[Enter] to switch");
  wait1Msec(2000);

  eraseDisplay();
  nxtDisplayCenteredTextLine(7, "[Enter] to switch");
  while (true) {
    while(nNxtButtonPressed != kEnterButton) {

      // Read the RAW RGB values from the sensor, these are
      // 10 bit values returned from the internal sensor.
      // You can read these values with or without the aid of the
      // ambient light cancelling white LED.  This is done with
      // the "passive" variable.  If it is set to true, the white LED
      // will be switched off, otherwise the LED is used to cancel
      // out the ambient light.

      // A return value of false implies an error has occurred
      if (!HTCS2readRawRGB(HTCS2, passive, red, green, blue)) {
        nxtDisplayTextLine(4, "ERROR!!");
        wait1Msec(2000);
        StopAllTasks();
      }

      nxtDisplayBigTextLine(0, "R: %5d", red);
      nxtDisplayBigTextLine(2, "G: %5d", green);
      nxtDisplayBigTextLine(4, "B: %5d", blue);
      wait1Msec(100);
    }

    // Toggle the "passive" variable to enable or disable
    // the ambient light cancelling white LED on the sensor
    if (nNxtButtonPressed == kEnterButton) {
      passive = !passive;
      PlaySound(soundBeepBeep);
      while (bSoundActive) {
        wait1Msec(10);
      }

      // Wait until no button is pressed (debounce)
      while (nNxtButtonPressed != kNoButton) {
        wait1Msec(10);
      }
    }
  }
}

/*
 * $Id: hitechnic-colour-v2-test2.c 123 2012-11-02 16:35:15Z xander $
 */

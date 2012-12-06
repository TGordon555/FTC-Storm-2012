#pragma config(Sensor, S1,     HTPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-protoboard-test3.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * hitechnic-protoboard.h provides an API for the HiTechnic Protoboard.  This program
 * demonstrates how to use that API.
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 16 July 2009
 * version 0.1
 */

#include "drivers/hitechnic-protoboard.h"

task main() {
  int adch0, adch1, adch2, adch3, adch4 = 0;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Proto");
  nxtDisplayCenteredTextLine(3, "Test 3");
  nxtDisplayCenteredTextLine(5, "Connect HTPB");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);


  while(true) {
    // get the value for ADC channels, we want a 10 bit answer
    if (!HTPBreadAllADC(HTPB, adch0, adch1, adch2, adch3, adch4, 10)) {
      eraseDisplay();
      PlaySound(soundException);
      nxtDisplayTextLine(5, "ERR READING ADC");
      wait1Msec(2000);
      StopAllTasks();
    }
    nxtDisplayBigTextLine(1, "ADC VALS");
    nxtDisplayTextLine(3, "CH0: %4d", adch0);
    nxtDisplayTextLine(4, "CH1: %4d", adch1);
    nxtDisplayTextLine(5, "CH2: %4d", adch2);
    nxtDisplayTextLine(6, "CH3: %4d", adch3);
    nxtDisplayTextLine(7, "CH4: %4d", adch4);
    wait1Msec(100);
  }
}

/*
 * $Id: hitechnic-protoboard-test3.c 123 2012-11-02 16:35:15Z xander $
 */

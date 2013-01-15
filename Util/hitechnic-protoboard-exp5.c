#pragma config(Sensor, S1,     HTPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-protoboard-exp5.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * hitechnic-protoboard.h provides an API for the HiTechnic Protoboard.  This is program 5
 * for the HTPB experimenter's kit.
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
 * 07 May 2010
 * version 0.1
 */

#include "drivers/hitechnic-protoboard.h"

int wlight;
int wolight;
int lightdelta;


task main() {
  // The data to be written: 0x3F = 111111 binary,
  // makes all digital ports outputs.
  HTPBsetupIO(HTPB, 0x3F);

  while(true) {
    // Switch off LED on port B0
    HTPBwriteIO(HTPB, 0x00);
    wait1Msec(30);
    wolight = HTPBreadADC(HTPB, 0, 10);

    // Switch on LED on port B0
    HTPBwriteIO(HTPB, 0x01);
    wait1Msec(30);
    wlight = HTPBreadADC(HTPB, 0, 10);

    // Calculate the difference
    lightdelta = wlight - wolight;

    eraseDisplay();
		nxtDisplayTextLine(1, "%4d", wlight);
		nxtDisplayTextLine(2, "%4d", wolight);
		nxtDisplayTextLine(3, "%4d", lightdelta);
    wait1Msec(30);
  }
}

/*
 * $Id: hitechnic-protoboard-exp5.c 123 2012-11-02 16:35:15Z xander $
 */

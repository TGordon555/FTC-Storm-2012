#pragma config(Sensor, S4,     NXT2WIFI,       sensorHighSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: benedettelli-nxt2wifi-test3.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * benedettelli-nxt2wifi.h provides an API for Daniele's NXT2WiFi Sensor. This program
 * demonstrates how to use that API.  This program is opens a listening socket on port
 * 6666 and waits for a client to connect.  It returns a simple message as follows:
 * "Hi there, <IP address>".
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Daniele Benedettelli for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.00 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 22 July 2012
 * version 0.1
 */

#include "drivers/common.h"
#include "drivers/benedettelli-nxt2wifi.h"

long txbytes = 0;
long rxbytes = 0;
string IPaddress = "0.0.0.0";
string connStatus = "disconnected";
string returnMsg;
string dataStrings[4];
tBigByteArray buffer;


task updateScreen()
{
  while(true)
  {
    nxtDisplayTextLine(0, "Stat: %s", connStatus);
    nxtDisplayTextLine(1, "%s",IPaddress);
    nxtDisplayTextLine(2, "-------------------");
    nxtDisplayTextLine(3, "%s", dataStrings[0]);
		nxtDisplayTextLine(4, "%s", dataStrings[1]);
		nxtDisplayTextLine(5, "%s", dataStrings[2]);
		nxtDisplayTextLine(6, "%s", dataStrings[3]);
    nxtDisplayTextLine(7, "RX/TX: %d/%d", rxbytes, txbytes);
    wait1Msec(100);
  }
}

task main ()
{
  int index;
  // port to use for the socket
  int BOFHport = 6666;
  string dataString;

  // get our bluetooth name
  getFriendlyName(dataString);

  int avail = 0;

  nNxtButtonTask = -2;
  StartTask(updateScreen);

  // initialise the port, etc
  RS485initLib();

  memset(RS485rxbuffer, 0, sizeof(RS485rxbuffer));
  memset(RS485txbuffer, 0, sizeof(RS485txbuffer));

  N2WchillOut();

  // Disconnect if already connected
  N2WDisconnect();
  N2WchillOut();

  // if a custom profile exists, use that instead
  if (N2WCustomExist())
  {
    N2WLoad();
  }
  else
  {
    // enable DHCP
    N2WsetDHCP(true);
    wait1Msec(100);
    // Disable adhoc
	  N2WsetAdHoc(false);
	  wait1Msec(100);
	  // SSID to connect to
	  N2WsetSSID("YOURWIFINETWORK");
	  wait1Msec(100);
	  // The passphrase to use
	  N2WSecurityWPA2Passphrase("YOURWIFIPASSPHRASE");
	  wait1Msec(100);
	  // Save this profile to the custom profile
	  N2WSave();
	  wait1Msec(100);
	  // Load the custom profile
	  N2WLoad();
	}

  wait1Msec(100);
  N2WConnect(true);
  connStatus = "connecting";

  while (!N2WConnected())
    wait1Msec(1000);

  connStatus = "connected";
  PlaySound(soundBeepBeep);

  wait1Msec(3000);
  N2WgetIP(IPaddress);

  wait1Msec(1000);

  // Open a listening socket on port 6666
  if (!N2WTCPOpenServer(1, BOFHport))
  {
    writeDebugStreamLine("Err open port %d", BOFHport);
    PlaySound(soundException);
    while(bSoundActive) EndTimeSlice();
    StopAllTasks();
  }

  while (true)
  {
    // Check if anyone has sent us anything
    avail = N2WTCPAvail(1);
    if (avail > 0)
    {
      rxbytes += avail;
      N2WchillOut();


      PlaySound(soundFastUpwardTones);

      // Read what the client sent us
      sprintf(dataStrings[0], "%d bytes from", avail);
      N2WTCPRead(1, avail);
      N2WchillOut();

      // Get the MAC address of the client
      dataStrings[2] = "Remote MAC:";
      N2WTCPClientMAC(1, dataStrings[3]);

      writeDebugStream("MAC: ");
      writeDebugStreamLine(dataStrings[3]);
      N2WchillOut();

      // check the IP address of the client
      N2WTCPClientIP(1, dataStrings[1]);
      N2WchillOut();

      // Send back a hearty "Hi there, <IP>!"
      index = 0;
      returnMsg = "Hi there, ";
      index = RS485appendToBuff(buffer, index, returnMsg);
      index = RS485appendToBuff(buffer, index, dataStrings[1]);
      returnMsg = "\n";
      index = RS485appendToBuff(buffer, index, returnMsg);
      txbytes += index;
      N2WTCPWrite(1, (tHugeByteArray)buffer, index);
      N2WchillOut();

      // Terminate the connection to the client
      N2WTCPDetachClient(1);
      N2WchillOut();
	  }
	  // Wait a bit
    wait1Msec(50);
  }
}

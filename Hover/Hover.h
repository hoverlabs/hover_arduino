/*************************************************** 
  This is the library for our Hover board. 
  
  Hover is a development kit that lets you control your Arduino projects in a whole new way.  
  Wave goodbye to physical buttons. Hover detects hand movements in the air for touch-less interaction.  
  It also features five touch-sensitive regions for even more options.
  Hover uses I2C and 2 digital pins to communicate with any Arduino board.

  Hover can be purchased from here: http://www.justhover.com

  Written by Emran Mahbub and Jonathan Li for Gearseven Studios.  
  BSD license, all text above must be included in any redistribution

  HOOKUP GUIDE
  ts - Any digital pin. This example uses D6.
  reset - Any digitial pin. This example uses D5.
  SCL / SDA - For Arduino UNO, I2C pins are: A4 -> SDA, A5 -> SCL. For Arduino Leonardo/Lilypad, I2C pins are: D2 -> SDA, D3 -> SCL
  GND - Ground pin. 
  3V3 - Connect to 3V3 pin on Arduino
  HostV - If using a 5V board like Arduino Uno/Leonardo/etc, connect to 5V pin. If using a 3.3V board like the Arduino Due/Lilypad/etc, connect to 3V3 pin. 
  
  HISTORY
  v1.0  -  Initial Release

  SUPPORT
  For questions and comments, email us at support@gearseven.com

***************************************************/


#ifndef _Hover_H
#define _Hover_H

#include "Arduino.h"


class Hover {
 public:
  Hover(uint8_t addr = 0x42);
  void begin(int ts, int mclr);
  void setRelease(int ts);
  boolean getStatus(int ts);
  byte getEvent(void);

 private:
  uint8_t _i2caddr;
};




#endif
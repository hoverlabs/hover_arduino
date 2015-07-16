/*  ===========================================================================
#  This is the library for Hover. 
#  
#  Hover is a development kit that lets you control your hardware projects in a whole new way.  
#  Wave goodbye to physical buttons. Hover detects hand movements in the air for touch-less interaction.  
#  It also features five touch-sensitive regions for even more options.
#  Hover uses I2C and 2 digital pins. It is compatible with Arduino, Raspberry Pi and more.
#
#  Hover can be purchased here: http://www.hoverlabs.co
#
#  Written by Emran Mahbub and Jonathan Li for Hover Labs.  
#  BSD license, all text above must be included in any redistribution
#  ===========================================================================
#
#  INSTALLATION
#  The 3 library files (Hover.cpp, Hover.h and keywords.txt) in the Hover folder should be placed in your Arduino Library folder.
#  Run the HoverDemo.ino file from your Arduino IDE.
#
#  SUPPORT
#  For questions and comments, email us at support@hoverlabs.co
#  v3.0
#  ===========================================================================*/


#ifndef _Hover_H
#define _Hover_H

#include "Arduino.h"

class Gesture {
  public: 
    Gesture ();
    Gesture(char * gestureType, uint8_t gestureID, uint8_t gestureValue); 
    char gestureType[15];
    uint8_t gestureID; 
    uint8_t gestureValue;
};

class Touch {
  public:
    Touch();
    Touch(char * touchType, uint8_t touchID, uint8_t touchValue);
    char touchType[20];
    uint8_t touchID;
    uint8_t touchValue;
};

class Position {
 public:
  Position(uint16_t x, uint16_t y, uint16_t z);
  uint16_t x, y, z;
};

class Hover {
 public:
  Hover(uint8_t ts, uint8_t rst, uint8_t gestmode, uint8_t touchmode, uint8_t tapmode, uint8_t posmode);
  void begin();
  Position getPosition(void);
  Gesture getGesture(void);
  Touch getTouch(void);
  void readI2CData(void);

 private:
  boolean _valid;
  uint8_t _dat[26], _i2caddr, _ts, _rst, _gestmode, _touchmode, _tapmode, _posmode;
  void setRelease();
  boolean getStatus();
  void readPositionData(uint16_t *x, uint16_t *y, uint16_t *z);
  void readGestureData(char * gtype, uint8_t * gid, uint8_t * gval);
  void readTouchData(char * ttype, uint8_t * tid, uint8_t * tval);

};


#endif
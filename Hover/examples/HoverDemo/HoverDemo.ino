/*************************************************************************************************************
#  This is an example for Hover. 
#  
#  Hover is a development kit that lets you control your hardware projects in a whole new way.  
#  Wave goodbye to physical buttons. Hover detects hand movements in the air for touch-less interaction.  
#  It also features five touch-sensitive regions for even more options.
#  Hover uses I2C and 2 digital pins. It is compatible with Arduino, Raspberry Pi and more.
#
#  Hover can be purchased here: http://www.justhover.com
#
#  Written by Emran Mahbub and Jonathan Li for Gearseven Studios.  
#  BSD license, all text above must be included in any redistribution
#  ===========================================================================
#
#  HOOKUP GUIDE (For Raspberry Pi)
#  
#    =============================
#   | 1 2 3 4 5 6 7               |                               
#   |                      HOVER  |
#   |                             |
#   | +++++++++++++++++++++++++++ |
#   | +                         + |
#   | +                         + |
#   | *                         + |
#   | *                         + |
#   | *                         + |
#   |_+++++++++++++++++++++++++++_|
#   
#  PIN 1 - HOST_V+    ----    3V3 pin 
#  PIN 2 - RESET      ----    Any Digital Pin.  This example uses GPIO 24 (BCM Mode). 
#  PIN 3 - SCL        ----    SCL pin
#  PIN 4 - SDA        ----    SDA pin
#  PIN 5 - GND        ----    Ground Pin
#  PIN 6 - 3V3        ----    3V3 pin
#  PIN 7 - TS         ----    Any Digital Pin.  This example uses GPIO 23 (BCM Mode).
#   
#  =============================================================================
#
#  OUTPUT DEFINITION
#  The message variable outputs an 8-bit binary value to indicate the event type, gesture direction, and tap location.  
#  Upper 3 bits indicates the event type: gesture or tap.
#  Lower 5 bits indicates the gesture direction or tap location. 
#
#    EVENT TYPE     DIRECTION 
#       000           00000
#  ---------------------------------------------------------
#    GESTURES       DIRECTION FOR GESTURE
#       001            00010 - Right Swipe
#                      00100 - Left Swipe
#                      01000 - Up Swipe 
#                      10000 - Down Swipe
#
#    TAP            DIRECTION FOR TAP
#       010            00001 - South Tap
#                      00010 - West Tap
#                      00100 - North Tap
#                      01000 - East Tap
#                      10000 - Center Tap
#  ----------------------------------------------------------
#                         
#  HISTORY
#  v1.0  -  Initial Release
#  v2.0  -  Standardized Output Definition, On Github
#  
#  INSTALLATION
#  Place the Hover_library.py file in the same folder as the Hover_example.py file.
#  Then run Hover_example.py by typing: sudo python Hover_example.py
#
#  SUPPORT
#  For questions and comments, email us at support@gearseven.com
#
*********************************************************************************************************/

#include <Wire.h>
#include <Hover.h>

// Pin declarations for Hover
int ts = 5;
int reset = 6;

Hover hover = Hover();
byte event;

void setup() {
  Serial.begin(9600);
  delay(4000);
  Serial.println("Initializing Hover...please wait.");
  hover.begin(ts, reset);        
}

void loop(void) {
  
  // Check if Hover is ready to send gesture or touch events
  if (hover.getStatus(ts) == 0) {
    
    //Get the event over i2c and print it
    event = hover.getEvent();

    if (event == B00100010) {
        Serial.println("Right swipe"); 
    } else if (event == B00100100) {
        Serial.println("Left swipe"); 
    } else if (event == B00101000) {
        Serial.println("Up swipe");         
    } else if (event == B00110000) {
        Serial.println("Down swipe"); 
    } else if (event == B01000001) {
        Serial.println("Tap south");
    } else if (event == B01000010) {
        Serial.println("Tap West");
    } else if (event == B01010000) {
        Serial.println("Tap Center");
    } else if (event == B01001000) {
        Serial.println("Tap East"); 
    } else if (event == B01000100) {
        Serial.println("Tap NORTH");         
    }
    
    //Reset Hover for next event
    event = B0;
    hover.setRelease(ts);

  }
}

    
    














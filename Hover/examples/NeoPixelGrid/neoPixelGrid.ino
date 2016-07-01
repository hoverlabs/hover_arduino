// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
// Hover example built using the Neopixel Ring as a base.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64
#define PIN            7

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second

#include <Wire.h>
#include <Hover.h>

// pin declarations for Hover
int ts = 5;
int reset = 6;
int circle_count = 999;

// Enable or disable different modes. Only gestures and taps are enabled by default. 
// Set the following four options to 0x01 if you want to capture every event. Note that the Serial console will be 'spammy'. 
#define GESTUREMODE 0x01    //0x00 = disable gestures, 0x01 = enable gestures
#define TOUCHMODE 0x00      //0x00 = disable touch, 0x01 = enable touch 
#define TAPMODE 0x01        //0x00 = disable taps, 0x01 = enable taps, 0x02 = single taps only, 0x03 = double taps only
#define POSITIONMODE 0x00   //0x00 = disable position tracking, 0x01 = enable position tracking

// initialize Hover
Hover hover = Hover(ts, reset, GESTUREMODE, TOUCHMODE, TAPMODE, POSITIONMODE);    

// used when printing 3D position coordinates. Using a smaller interval will result in a 'spammy' console. Set to update every 150ms by default.  
long interval = 10;        
long previousMillis = 0;
int light;

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Initializing Hover...please wait.");
  hover.begin(); 
  pixels.begin();
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  unsigned long currentMillis = millis();    // used for updating 3D position coordinates. Set to update every 150ms by default. 

  // read incoming data stream from Hover
  hover.readI2CData();
  
  Gesture g = hover.getGesture();
  Touch t = hover.getTouch();
  Position p = hover.getPosition();
  

////////////////////////////////////Touch Example
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   

  if ( t.touchID == 0x03) {
    if (t.touchValue == 0x5) {
      for (int i=0; i<8; i++){ 
        pixels.setPixelColor(0+i, pixels.Color(90,0,90));
        pixels.setPixelColor(56+i, pixels.Color(90,0,90));        
        pixels.setPixelColor(7+(i*8), pixels.Color(90,0,90));
        pixels.setPixelColor(0+(i*8), pixels.Color(90,0,90));        
      }
      pixels.show();
      delay(100);
      for (int i=0; i<8; i++){ 
        pixels.setPixelColor(0+i, 0);
        pixels.setPixelColor(56+i, 0);        
        pixels.setPixelColor(7+(i*8), 0);
        pixels.setPixelColor(0+(i*8), 0);        
      }      
      pixels.show();
    }
  } else if ( t.touchID == 0x2){  
    if (t.touchValue == 0x1) {
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(24+i, pixels.Color(0,30,10));
        pixels.setPixelColor(32+i, pixels.Color(0,30,10));
      }
      pixels.show();
      delay(100);
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(24+i, 0);
        pixels.setPixelColor(32+i, 0);
        delay(12);
        pixels.show();
      }      
    }
    else if (t.touchValue == 0x2) {
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(24+i, pixels.Color(40,0,00));
        pixels.setPixelColor(32+i, pixels.Color(40,0,00));
      }
      pixels.show();
      delay(100);
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(31-i, 0);
        pixels.setPixelColor(39-i, 0);
        delay(12);
        pixels.show();
      }
    }    
    else if (t.touchValue == 0x3) {
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(3+(i*8), pixels.Color(50,30,0));
        pixels.setPixelColor(4+(i*8), pixels.Color(50,30,0));
      }
      pixels.show();
      delay(100);
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(59-(i*8), 0);
        pixels.setPixelColor(60-(i*8), 0);
        delay(12);
        pixels.show();
      }
    } 
    else if (t.touchValue == 0x4) {
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(3+(i*8), pixels.Color(0,0,30));
        pixels.setPixelColor(4+(i*8), pixels.Color(0,0,30));
      }
      pixels.show();
      delay(100);
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(3+(i*8), 0);
        pixels.setPixelColor(4+(i*8), 0);
        delay(12);
        pixels.show();
      }
    } 
    else if (t.touchValue == 0x5) {
      for (int i = 0; i<4; i++){
        pixels.setPixelColor(0+(i*9), pixels.Color(90,0,90));
        pixels.setPixelColor(7+(i*7), pixels.Color(90,0,90));           
        pixels.setPixelColor(63-(i*9), pixels.Color(90,0,90));           
        pixels.setPixelColor(56-(i*7), pixels.Color(90,0,90)); 
        pixels.show();
        delay(60);        
      }
      pixels.show();
      delay(10);
      for (int i = 0; i<8; i++){
        pixels.setPixelColor(0+(i*9), 0);
        pixels.setPixelColor(7+(i*7), 0);           
        pixels.setPixelColor(63-(i*9), 0);           
        pixels.setPixelColor(56-(i*7), 0);     
      }
      pixels.show();
    }    
  }


////////////////////////////////////Gestures Example
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   

   int r2 = 0;
   int g2 = 0;
   int b2 = 10;
   int x = 0;

   
   
  if (g.gestureID == 0x2){
    if (g.gestureValue > 0 && g.gestureValue < 21 && circle_count !=0) {
      //print 0
      circle_count = 0;
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show(); 
      for (int i=0; i< 4; i++) {
        pixels.setPixelColor(2+i, pixels.Color(5,5,2));         
        pixels.setPixelColor(50+i, pixels.Color(5,5,2));
      }
      for (int i=0; i< 7; i++) {    
        pixels.setPixelColor(2+(i*8), pixels.Color(5,5,2));     
        pixels.setPixelColor(5+(i*8), pixels.Color(5,5,2));     
      }      
      pixels.show();     
    } else if (g.gestureValue > 20 && g.gestureValue < 46 && circle_count != 1) {
      //print 1
      circle_count = 1;
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show();       
      for (int i=0; i< 7; i++) {
        pixels.setPixelColor(5+(8*i), pixels.Color(5,5,2)); 
      }
      pixels.show();       
    } else if (g.gestureValue > 45 && g.gestureValue < 71 && circle_count != 2) {
      //print 2
      circle_count = 2;
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show();       
      for (int i=0; i< 4; i++) {
        pixels.setPixelColor(2+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(26+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(50+i, pixels.Color(5,5,2));
        pixels.setPixelColor(5+(8*i), pixels.Color(5,5,2));
        pixels.setPixelColor(26+(8*i), pixels.Color(5,5,2));     
      }
      pixels.show();
    } else if (g.gestureValue > 70 && g.gestureValue < 96 && circle_count != 3) {
        circle_count = 3;
        //print 3
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show(); 
      for (int i=0; i< 4; i++) {        
        pixels.setPixelColor(2+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(26+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(50+i, pixels.Color(5,5,2));
        pixels.setPixelColor(5+(8*i), pixels.Color(5,5,2));
        pixels.setPixelColor(29+(8*i), pixels.Color(5,5,2)); 
      }      
        pixels.show();
    } else if (g.gestureValue > 95 && g.gestureValue < 121 && circle_count != 4) {
        circle_count = 4;
      //print 4
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show(); 
     for (int i=0; i< 4; i++) {
        pixels.setPixelColor(26+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(2+(8*i), pixels.Color(5,5,2));
        pixels.setPixelColor(5+(8*i), pixels.Color(5,5,2));       
        pixels.setPixelColor(29+(8*i), pixels.Color(5,5,2));  
      }
      pixels.show();
    } else if (g.gestureValue > 120 && g.gestureValue < 156 && circle_count != 5) {
        circle_count = 5;
      //print 5
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show(); 
     for (int i=0; i< 4; i++) {
        pixels.setPixelColor(2+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(26+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(50+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(2+(8*i), pixels.Color(5,5,2));
        pixels.setPixelColor(29+(8*i), pixels.Color(5,5,2)); 
      }      
      pixels.show();
    } else if (g.gestureValue > 155 && g.gestureValue < 181 && circle_count != 6) {
        circle_count = 6;
      //print 6
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show();       
      for (int i=0; i< 4; i++) {
        pixels.setPixelColor(26+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(50+i, pixels.Color(5,5,2));       
        pixels.setPixelColor(2+(8*i), pixels.Color(5,5,2));
        pixels.setPixelColor(29+(8*i), pixels.Color(5,5,2));       
        pixels.setPixelColor(26+(8*i), pixels.Color(5,5,2));               
      }
      pixels.show();
    } else if (g.gestureValue > 180 && g.gestureValue < 206 && circle_count != 7) {
      circle_count = 7;
      //print 7
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show(); 
      for (int i=0; i< 4; i++) {
        pixels.setPixelColor(2+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(5+(8*i), pixels.Color(5,5,2));
        pixels.setPixelColor(29+(8*i), pixels.Color(5,5,2));                      
      }
      pixels.show();      
    } else if (g.gestureValue > 205 && g.gestureValue < 231 && circle_count != 8) {
        circle_count = 8;
      //print 8
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show();       
      for (int i=0; i< 4; i++) {
        pixels.setPixelColor(2+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(26+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(50+i, pixels.Color(5,5,2));                   
      }
      for (int i=0; i< 7; i++) {    
        pixels.setPixelColor(2+(i*8), pixels.Color(5,5,2));     
        pixels.setPixelColor(5+(i*8), pixels.Color(5,5,2));     
      }
      pixels.show();
    } else if (g.gestureValue > 230 && g.gestureValue < 256 && circle_count != 9) {
        circle_count = 9;
      //print 9
      for (int i=0; i<7; i++) {
        for (int j=0; j<4; j++){
           pixels.setPixelColor(2+j+(i*8), 0); 
        } 
      }
      pixels.show(); 
      for (int i=0; i< 4; i++) {
        pixels.setPixelColor(2+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(26+i, pixels.Color(5,5,2));     
        pixels.setPixelColor(50+i, pixels.Color(5,5,2));
        pixels.setPixelColor(2+(i*8), pixels.Color(5,5,2));           
      }
      for (int i=0; i< 7; i++) {       
        pixels.setPixelColor(5+(i*8), pixels.Color(5,5,2));     
      }
      pixels.show();
    } 
  }
/*

////////////////////////////////////Counter
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   
   if ( g.gestureID != 0){
    if ( g.gestureValue == 0x1){
      for (int i = 0; i<10; i++){
        for (int j = 0; j < 4; j++) {
          if (i > 1-j && i < 9-j){
            pixels.setPixelColor(-2+i+(9*j), pixels.Color(0,30,10));
            pixels.setPixelColor(54+i-(7*j), pixels.Color(0,30,10));
            
          } else if (i > 8-j){
            pixels.setPixelColor(7+(j*8), pixels.Color(0,30,10));
            pixels.setPixelColor(63-(j*8), pixels.Color(0,30,10));        
          }
        }    
        pixels.show();
        delay(i*9);        
        for (int j = 0; j < 4; j++) {        
          if (i > 1-j && i < 9-j){
            pixels.setPixelColor(-2+i+(9*j), 0);
            pixels.setPixelColor(54+i-(7*j), 0);        
          } else if (i > 8-j){
            pixels.setPixelColor(7+(j*8), 0);
            pixels.setPixelColor(63-(j*8), 0);        
          }
          pixels.show();  
        }
      }
     } else if ( g.gestureValue == 0x2) {
        for (int i = 0; i<10; i++){
          for (int j = 0; j < 4; j++) {
            if (i > 1-j && i < 9-j){
              pixels.setPixelColor(9-i+(7*j), pixels.Color(40,0,0));
              pixels.setPixelColor(65-i-(9*j), pixels.Color(40,0,0));
              
            } else if (i > 8-j){
              pixels.setPixelColor(0+(j*8), pixels.Color(40,0,0));
              pixels.setPixelColor(56-(j*8), pixels.Color(40,0,0));        
            }
          }    
          pixels.show();
          delay(i*9);        
          for (int j = 0; j < 4; j++) {        
            if (i > 1-j && i < 9-j){
              pixels.setPixelColor(9-i+(7*j), 0);
              pixels.setPixelColor(65-i-(9*j), 0);        
            } else if (i > 8-j){
              pixels.setPixelColor(0+(j*8), 0);
              pixels.setPixelColor(56-(j*8), 0);        
            }
            pixels.show();  
          }
        }
      } else if ( g.gestureValue == 0x3) {
        for (int i = 0; i<10; i++){
          for (int j = 0; j < 4; j++) {
            if (i > 1-j && i < 9-j){
              pixels.setPixelColor(72-(i*8)-(j*7), pixels.Color(50,30,00));
              pixels.setPixelColor(79-(i*8)-(j*9), pixels.Color(50,30,00));      
            } else if (i > 8-j){
              pixels.setPixelColor(0+j, pixels.Color(50,30,00));
              pixels.setPixelColor(7-j, pixels.Color(50,30,00));        
            }
          }    
          pixels.show();
          delay(i*9);        
          for (int j = 0; j < 4; j++) {        
            if (i > 1-j && i < 9-j){
              pixels.setPixelColor(72-(i*8)-(j*7), 0);
              pixels.setPixelColor(79-(i*8)-(j*9), 0);  
            } else if (i > 8-j){
              pixels.setPixelColor(0+j, 0);
              pixels.setPixelColor(7-j, 0);        
            }
            pixels.show();  
          }
        }
      } else if ( g.gestureValue == 0x4) {
        for (int i = 0; i<10; i++){
          for (int j = 0; j < 4; j++) {
            if (i > 1-j && i < 9-j){
              pixels.setPixelColor(-16+(i*8)+(j*9), pixels.Color(0,0,30));
              pixels.setPixelColor(-9+(i*8)+(j*7), pixels.Color(0,0,30));      
            } else if (i > 8-j){
              pixels.setPixelColor(56+j, pixels.Color(0,0,30));
              pixels.setPixelColor(63-j, pixels.Color(0,0,30));        
            }
          }    
          pixels.show();
          delay(i*9);        
          for (int j = 0; j < 4; j++) {        
            if (i > 1-j && i < 9-j){
              pixels.setPixelColor(-16+(i*8)+(j*9), 0);
              pixels.setPixelColor(-9+(i*8)+(j*7), 0);  
            } else if (i > 8-j){
              pixels.setPixelColor(56+j, 0);
              pixels.setPixelColor(63-j, 0);        
            }
            pixels.show();  
          }
        }
      }
   }

*/
/*  



////////////////////////////////////Position Example
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  if( (currentMillis - previousMillis > interval)) {
    
    previousMillis = currentMillis;
    if ( !(p.x==0 && p.y==0 && p.x==0) ) {          
      
      // scale raw position coordinates from (0,65535) to (0, 100). Set to 100 by default. Can be changed to any positive value for the desired granularity.   
      p.x = map(p.x, 0, 65535, 0, 7);
      p.y = map(p.y, 0, 65535, 0, 7);
      p.z = map(p.z, 0, 65535, 0, 7);
    
      light = (64+(p.x))-(8*(p.y)); 
      Serial.println(light);
      
      int r = 0;
      int g = 0;
      int b = 10;
      int a = 4;
      
      for (int i = 0; i<64; i++){
        pixels.setPixelColor(i, pixels.Color(r+(p.z*a),g,b));
      }
      //3 colors
      //1 - 2x2 square.  The point we use as center is top right.
      //2 - Surrounding flower petals.  2 on each side of 2x2 square.  
      //3 - The rest.
      
      pixels.setPixelColor(light, pixels.Color(r+(p.z*a),g,b+40));
      pixels.setPixelColor(light+8, pixels.Color(r+(p.z*a),g,b+40));
      pixels.setPixelColor(light-8, pixels.Color(r+(p.z*a),g,b+80));
      pixels.setPixelColor(light+16, pixels.Color(r+(p.z*a),g,b+80));                     
      
      //make sure we don't go over the edge      
      if (light % 8 != 7){
            pixels.setPixelColor(light+1, pixels.Color(r+(p.z*a),g,b+40));
            pixels.setPixelColor(light+9, pixels.Color(r+(p.z*a),g,b+40));
            
            pixels.setPixelColor(light-7, pixels.Color(r+(p.z*a),g,b+80));         
            pixels.setPixelColor(light+17, pixels.Color(r+(p.z*a),g,b+80));            
      }
      if (light % 8 != 7 && light % 8 != 6){
            pixels.setPixelColor(light+2, pixels.Color(r+(p.z*a),g,b+80));         
            pixels.setPixelColor(light+10, pixels.Color(r+(p.z*a),g,b+80));   
      }
      if (light % 8 != 0){
            pixels.setPixelColor(light-1, pixels.Color(r+(p.z*a),g,b+80));    
            pixels.setPixelColor(light+7, pixels.Color(r+(p.z*a),g,b+80));               
      }
      
      pixels.show();
    }
  }
*/
}
   

/*  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }*/


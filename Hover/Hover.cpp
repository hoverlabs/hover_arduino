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

#include <Hover.h>
#include <Wire.h>

#ifdef __AVR__
 #define WIRE Wire
#endif

Hover::Hover(uint8_t ts, uint8_t rst, uint8_t gestmode, uint8_t touchmode, uint8_t tapmode, uint8_t posmode) {
  _i2caddr = 0x42;
  _ts = ts;
  _rst = rst;
  _gestmode = gestmode;
  _touchmode = touchmode;
  _tapmode = tapmode;
  _posmode = posmode;
}

void Hover::begin() {
	WIRE.begin();
	pinMode(_ts, INPUT);    
	pinMode(_rst, OUTPUT);    
	digitalWrite(_rst, LOW);
	pinMode(_rst, INPUT);    
	//delay(3000);
	Serial.println("Hover is ready");
}

void Hover::setRelease() {
    digitalWrite(_ts, HIGH);
    pinMode(_ts, INPUT);
}

boolean Hover::getStatus() {
	if (digitalRead(_ts) == 0) {
		pinMode(_ts, OUTPUT);
		digitalWrite(_ts, LOW);
		return 0;
	}	
	return 1;
}


void Hover::readI2CData(void) {
	if (getStatus() == 0){
		int c = 0;
	    WIRE.requestFrom((uint8_t)_i2caddr, (uint8_t)26);    // request 26 bytes from slave device at 0x42
	    while(WIRE.available())    // slave may send less than requested
	    {     
			_dat[c] = WIRE.read(); // receive a byte as character 
			c++;
		}
		setRelease();
		_valid = 1;
		delay(6);
	} else {
		_valid = 0;
	}

}

Gesture::Gesture(){
	strcpy(gestureType, "none");
	gestureID = 0;
	gestureValue = 0;
}

Gesture::Gesture (char * type, uint8_t id, uint8_t value){
	strcpy(gestureType, type);
	gestureID = id;
	gestureValue = value;
}

Gesture Hover::getGesture(void) {
	char gtype[15];
	uint8_t gid; 
	uint8_t gval;

	if (_valid == 1 && _gestmode == 0x01) {
		readGestureData(gtype, &gid, &gval);
	} else {
		strcpy(gtype, "none");
		gid = 0x00;
		gval = 0x00;
	}
		
	return Gesture(gtype, gid, gval);
}

Airwheel::Airwheel (uint16_t value){
		wheelValue = value;
}

Airwheel Hover::getAirWheelData(void){
	uint16_t value;
	value = _dat[19] << 8 | _dat[18];
	return Airwheel(value);
}

void Hover::readGestureData(char * gtype, uint8_t * gid, uint8_t * gval) {
		
	
	switch (_dat[10]){
		case 2: 
			strcpy(gtype, "Right Swipe");
			*gid = 0x01;
			*gval = 0x01;		
		break;
		case 3: 
			strcpy(gtype, "Left Swipe");
			*gid = 0x01;
			*gval = 0x02;		
		break;
		case 4: 
			strcpy(gtype, "Up Swipe");
			*gid = 0x01;
			*gval = 0x03;		
		break;
		case 5: 
			strcpy(gtype, "Down Swipe");
			*gid = 0x01;
			*gval = 0x04;		
		break;	
		default:
			strcpy(gtype, "None");
			*gid = 0x00;
			*gval = 0x00;		
		break;			
	}

}

Touch::Touch(){
	strcpy(touchType, "none");
	touchID = 0;
	touchValue = 0;
}

Touch::Touch (char * type, uint8_t id, uint8_t value){
	strcpy(touchType, type);
	touchID = id;
	touchValue = value;
}

Touch Hover::getTouch(void) {
	char ttype[20];
	uint8_t tid; 
	uint8_t tval; 

	if (_valid == 1) {
		readTouchData(ttype, &tid, &tval);
	} else {
		strcpy(ttype, "None");
		tid = 0x00;	
		tval = 0x00;	
	}

	return Touch(ttype, tid, tval);
}

void Hover::readTouchData(char * ttype, uint8_t * tid, uint8_t * tval) {

	uint8_t touch, tap, doubleTap;

	touch = (_touchmode==0x01) ? (touch = (_dat[14] & 0x1F)) : (0);

	if (_tapmode!=0x00){
		if (_tapmode == 0x01){
			tap = (((_dat[15] & 0x03) << 3 ) | (_dat[14]>>5));
			doubleTap = ((_dat[15]>>2) & 0x1F);
		} else {
			tap = (_tapmode==0x02) ? (tap = (((_dat[15] & 0x03) << 3 ) | (_dat[14]>>5))) : (0);
			doubleTap = (_tapmode==0x03) ? (doubleTap = ((_dat[15]>>2) & 0x1F)) : (0);
		}
	} else {
		tap = 0;
		doubleTap = 0;
	}


	if (doubleTap != 0) {
		switch (doubleTap) {
			case 1:
				strcpy(ttype, "Double Tap South");
				*tid = 0x03;
				*tval = 0x04;
			break;
			case 2: 
				strcpy(ttype, "Double Tap West");
				*tid = 0x03;
				*tval = 0x02;
			break;
			case 4: 
				strcpy(ttype, "Double Tap North");
				*tid = 0x03;
				*tval = 0x03;
			break;
			case 8: 
				strcpy(ttype, "Double Tap East");
				*tid = 0x03;
				*tval = 0x01;
			break;
			case 16: 
				strcpy(ttype, "Double Tap Center");
				*tid = 0x03;
				*tval = 0x05;
			break;		
			default:
				strcpy(ttype, "None");
				*tid = 0x00;	
				*tval = 0x00;	
			break;
		}

	} else if (tap != 0) {
		switch (tap){
			case 1:
				strcpy(ttype, "Tap South");
				*tid = 0x02;
				*tval = 0x04;
			break;
			case 2: 
				strcpy(ttype, "Tap West");
				*tid = 0x02;
				*tval = 0x02;
			break;
			case 4: 
				strcpy(ttype, "Tap North");
				*tid = 0x02;
				*tval = 0x03;
			break;
			case 8: 
				strcpy(ttype, "Tap East");
				*tid = 0x02;
				*tval = 0x01;
			break;
			case 16: 
				strcpy(ttype, "Tap Center");
				*tid = 0x02;
				*tval = 0x05;
			break;
			default:
				strcpy(ttype, "None");
				*tid = 0x00;	
				*tval = 0x00;	
			break;
		}

	} else if (touch!=0) {
		switch (touch){
			case 1:
				strcpy(ttype, "Touch South");
				*tid = 0x01;
				*tval = 0x04;
			break;
			case 2: 
				strcpy(ttype, "Touch West");
				*tid = 0x01;
				*tval = 0x02;
			break;
			case 4: 
				strcpy(ttype, "Touch North");
				*tid = 0x01;
				*tval = 0x03;
			break;
			case 8: 
				strcpy(ttype, "Touch East");
				*tid = 0x01;
				*tval = 0x01;
			break;
			case 16: 
				strcpy(ttype, "Touch Center");
				*tid = 0x01;
				*tval = 0x05;
			break;
			default:
				strcpy(ttype, "None");
				*tid = 0x00;	
				*tval = 0x00;	
			break;
		}

	}  else {

		strcpy(ttype, "None");
		*tid = 0x00;	
		*tval = 0x00;	

	}

}

Position::Position (uint16_t x0, uint16_t y0, uint16_t z0) {
	x = x0;
	y = y0;
	z = z0;
}

Position Hover::getPosition(void) {

	uint16_t x, y, z;

	if (_valid == 1 && _posmode == 0x01) {

		readPositionData(&x, &y, &z);

	} else {

		x = 0;
		y = 0;
		z = 0;

	}

	return Position(x, y, z);
}

void Hover::readPositionData(uint16_t *x, uint16_t *y, uint16_t *z) {

	if ((_dat[7] & 0x01) == 1){

		*x = ((_dat[21] << 8) | _dat[20]);
		*y = ((_dat[23] << 8) | _dat[22]);
		*z = ((_dat[25] << 8) | _dat[24]);

	} else {

		*x = 0;
		*y = 0;
		*z = 0;

	}

}






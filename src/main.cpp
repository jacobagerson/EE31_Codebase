#include "main.h"

typedef enum { 
  START, 
  firstWALL,
  findCOLOR_X,
  laneFOLLOW_X,
  findCOLOR_Y,
  laneFOLLOW_Y,
  findSTART 
} State;

State currentState = START;



void setup() {
	//initialize serial monitor
    Serial.begin(9600);

	//initialize motor pins
	setupMotorPins();


	//start websocket up
    setupSocket();
    
}

void loop() {

    //Serial.println("inside loop");

    //Serial.println(value);
    Serial.println(ir_read());
    delay(200);

	if (ir_read() < 700) {
        setLSpeed(150);
        setRSpeed(150);
		leftMotorForward();
		rightMotorForward();
	} else {
		leftMotorStop();
		rightMotorStop();
	}

    // // put your main code here, to run repeatedly:
    // switch (currentState){
    // case START:
        
    //     break;
    
    // case firstWALL:

    //     break;

    // case findCOLOR_X:

    //     break;

    // case laneFOLLOW_X:

    //     break;

    // case findCOLOR_Y:

    //     break;
    
    // case laneFOLLOW_Y:

    //     break;

    // case findSTART:

    //     break;

    // default:
    //     currentState = START;
    //     break;
    // }

}

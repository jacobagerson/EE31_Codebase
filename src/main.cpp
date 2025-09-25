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
    //setupSocket();

    // String message = readMessage();
    // while(1){
    //     String message = readMessage();
    //     if(message.length() > 0){
    //         Serial.println(message);
    //         message.remove(0, 10);
    //         String id = parseID(message);
    //         Serial.println(id);
    //         String sent = getMessage(message);
    //         Serial.println("message = " + sent);

    //         if(id == "8050D1451904"){
    //             Serial.println("Our ID");
    //         }
    //         else Serial.println("not our id");
    //         //String nMessage = parseID(message);
    //         // Serial.println(nMessage);
    //     }
    
}

void loop() {

    //Serial.println("inside loop");

    //Serial.println(value);
    Serial.println(ir_read());
    delay(200);

	if (ir_read() < 700) {
		leftMotorForward(150);
		rightMotorForward(150);
	} else {
		leftMotorStop();
		rightMotorStop();
	}

    // writeMessage("test message");
    // delay(1000);
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

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
  // put your setup code here, to run once:
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    // pinMode(A0, INPUT_PULLUP);

    digitalWrite(4, HIGH); //Set enable high
    digitalWrite(6, LOW);
    analogWrite(5, 250);
    
    //start websocket up 
    setupSocket();

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

    // ir_read();
    float value = analogRead(A0);
    Serial.println(value);
    delay(200);
    
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

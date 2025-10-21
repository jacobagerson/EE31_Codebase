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

void blink(int pin, int num){
    for(int i = 0; i < num; i++){
        digitalWrite(pin, HIGH);
        delay(500);
        digitalWrite(pin, LOW);
        delay(500);
    }
}

void setup() {
	//initialize serial monitor
    Serial.begin(9600);

	//initialize motor pins
	//setupMotorPins();

    pinMode(4, OUTPUT); // Enable pin (orange)
    pinMode(5, OUTPUT); //PWM pin (green)
    pinMode(6, OUTPUT); //Reference pin (green)

    //left Motor
    pinMode(8, OUTPUT); // Enable pin (orange)
    pinMode(9, OUTPUT); //PWM pin (green)
    pinMode(10, OUTPUT); //Reference pin (green)

    pinMode(LED_BUILTIN, OUTPUT);

    //setRSpeed(240);

    //Color Sensing
    //setUpColorPins();

	//start websocket up
    //setupSocket();

    // String message = readMessage();
    // Serial.println(message);
    // while(1){
    //     String message = readMessage();
    //     if(message.length() > 0){
    //         Serial.println(message);
    //         //message.remove(0, 10);
    //         String id = parseID(message);
    //         Serial.print("id = ");
    //         Serial.println(id);
    //         String sent = getMessage(message);
    //         Serial.println("message = " + sent);

    //         if(id == "8050D1451904"){
    //             Serial.println("Our ID");
    //         }
    //         else Serial.println("not our id");
    //     }
    // }
}

int communicate(){
    String message = readMessage();
    int state = -1;
    if(parseID(message) == "8050D1451904"){
        state = getMessage(message).toInt();
        Serial.println(message);
        //writeMessage("Write to server");
    }
    return state; 
}

void loop(){
    int num = 0;

    // setLSpeed(150);
    // leftMotorForward();

	// if (ir_read() < 700) {
	// 	leftMotorForward(150);
	// 	leftMotorForward(150);
	// } else {
	// 	leftMotorStop();
	// 	leftMotorStop();
	// }

    float val = ir_read();
    Serial.print("Analong IR: ");
    Serial.println(val);
    while (wall_close())
    {
        Serial.println("wall detected");
    }
    
    //when moving along lanes, want to check our distance each step with the wall_close();
    //if we get this = true, then we can turn around/L/R and continue on with our bot motion
    //just set a global bool to help us change states

    // writeMessage("test message");
    // delay(1000);


    // switch (currentState){
    // case START:
    //     {
    //         //Serial.println("inside start state");
    //         num = communicate();
    //         if(num == -1){
    //             currentState = START; 
    //         } else currentState = (State) num; 
    //         setLSpeed(240);
    //         leftMotorForward();
    //         //delay(3000);
    //         break;
    //     }
    // case firstWALL:
    //     {
    //         //Serial.println("inside first wall state");
    //         num = communicate();
    //         if(num == -1){
    //             currentState = firstWALL; 
    //         } else currentState = (State) num; 
    //         setLSpeed(150);
    //         leftMotorBackward();
    //         //delay(3000);
    //         break;
    //     }
    // case findCOLOR_X:
    //     {            
    //         //Serial.println("inside findColor_X state");
    //         num = communicate();
    //         if(num == -1){
    //             currentState = findCOLOR_X; 
    //         } else currentState = (State) num; 
    //         leftMotorStop();
    //         setLSpeed(50);
    //         leftMotorBackward();
    //         //delay(1000);
    //         break;
    //     }
    // case laneFOLLOW_X:

    //     //Serial.println("inside laneFollow_x state");
    //     num = communicate();
    //     if(num == -1){
    //         currentState = laneFOLLOW_X; 
    //     } else currentState = (State) num; 
    //     setLSpeed(200);
    //     leftMotorForward();
    //     //delay(1000);
    //     break;

    // case findCOLOR_Y:

    //     //Serial.println("inside findColor_Y state");
    //     num = communicate();
    //     if(num == -1){
    //         currentState = findCOLOR_Y; 
    //     } else currentState = (State) num; 
    //     setLSpeed(255);
    //     leftMotorBackward();
    //     //delay(1000);
    //     break;
    
    // case laneFOLLOW_Y:
    //     //Serial.println("inside laneFollow_y state");
    //     num = communicate();
    //     if(num == -1){
    //         currentState = laneFOLLOW_Y; 
    //     } else currentState = (State) num; 
    //     setLSpeed(50);
    //     leftMotorBackward();
    //     //delay(1000);
    //     break;

    // case findSTART:

    //     //Serial.println("inside findStart state");
    //     num = communicate();
    //     if(num == -1){
    //         currentState = findSTART; 
    //     } else currentState = (State) num; 
    //     setLSpeed(250);
    //     leftMotorForward();
    //     //delay(1000);
    //     break;

    // default:
    //     currentState = START;
    //     break;
    // }

}

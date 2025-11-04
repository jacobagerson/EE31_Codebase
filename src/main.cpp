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
    setUpColorPins();

	//start websocket up
    //setupSocket();
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

    int color[2] = {0};

    while(1) {
        digitalWrite(11, HIGH);
        // getColor(color[2]);
        // Serial.print("Sensor 1: ");
        // Serial.print(color[0]);
        // Serial.print(" Sensor 2: ");
        // Serial.println(color[1]);
    }

    digitalWrite(4, HIGH); //Enable = Yellow
    digitalWrite(6, LOW); //Reference = white
    analogWrite(5, 250); //PWM = Orange

    
    // digitalWrite(8, HIGH); //Enable = Yellow
    // digitalWrite(10, LOW); //Reference = white
    // analogWrite(9, 200); //PWM = Orange


    // setLSpeed(150);
    // leftMotorForward();
    // delay(1000);
    // motorsStop();
    // delay(1000);

	// if (ir_read() < 700) {
	// 	leftMotorForward(150);
	// 	leftMotorForward(150);
	// } else {
	// 	leftMotorStop();
	// 	leftMotorStop();
	// }

    // float val = ir_read();
    // Serial.print("Analong IR: ");
    // Serial.println(val);
    // while (wall_close())
    // {
    //     Serial.println("wall detected");
    // }
    
    //when moving along lanes, want to check our distance each step with the wall_close();
    //if we get this = true, then we can turn around/L/R and continue on with our bot motion
    //just set a global bool to help us change states

 //   delay(1000);


    // switch (currentState){
    // case START:
    //     {
    //         Serial.println("inside start state");
    //         num = communicate();
    //         if(num == -1){
    //             currentState = START; 
    //         } else currentState = (State) num; 

    //         motorsStop();
    //         setSpeed(150);
    //         delay(1000);
    //         turnL90();
    //         delay(1000);
    //         turnR90();
    //         delay(1000);
    //         setSpeed(10);
    //         moveForward();
    //         break;
    //     }
    // case firstWALL:
    //     {
    //         Serial.println("inside first wall state");
    //         num = communicate();
    //         if(num == -1){
    //             currentState = firstWALL; 
    //         } else currentState = (State) num; 
    //         motorsStop();
    //         setSpeed(150);
    //         moveBackward();
    //         delay(1000);
    //         turnL90();
    //         delay(1000);
    //         turnR90();
    //         delay(1000);
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
    //     {
    //         //Serial.println("inside laneFollow_x state");
    //         num = communicate();
    //         if(num == -1){
    //             currentState = laneFOLLOW_X; 
    //         } else currentState = (State) num; 
    //         setLSpeed(200);
    //         leftMotorForward();
    //         //delay(1000);
    //         break;
    //     }
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

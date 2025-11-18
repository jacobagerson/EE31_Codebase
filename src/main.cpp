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
	setupMotorPins();


    pinMode(LED_BUILTIN, OUTPUT);

    setRSpeed(240);
    setLSpeed(240);

    //Color Sensing
    setUpColorPins();

	//start websocket up
    //setupSocket();
    delay(2500);
}

int communicate() {
    String message = readMessage();
    int state = -1;

    if (message.length() > 0 && parseID(message) == "8050D1451904") {
        String stateStr = getMessage(message);
        state = stateStr.toInt();
        //Serial.println(state);
    }

    if(state <= 6 && state >= 0){
        return state; 
    } else return -1; 
}


void loop(){
    int num = 0;
    int color[2] = {0};

    // to get a color just do: getColor(color);, where color[0] is the right hand side sensor
    // and color[1] is the lefthand side sensor

    // digitalWrite(4, HIGH); //Enable = Yellow
    // digitalWrite(6, LOW); //Reference = white
    // analogWrite(5, 250); //PWM = Orange

    Serial.print(ir_read());

    //when moving along lanes, want to check our distance each step with the wall_close();
    //if we get this = true, then we can turn around/L/R and continue on with our bot motion
    //just set a global bool to help us change states

 //   delay(1000);
    // for(int i = 0; i < 10; i++){
    //     setSpeed(150);
    //     leftMotorForward();
    //     rightMotorForward();
    //     delay(200);
    // }
    // motorsStop();
    // delay(2000);
    // for(int i = 0; i < 10; i++){
    //     setSpeed(150);
    //     leftMotorBackward();
    //     rightMotorBackward();
    //     delay(200);
    // }

    // motorsStop();
    // setSpeed(150);
    // turnL90();
    // // // leftMotorForward();
    // // // rightMotorBackward();
    // motorsStop();
    // delay(2000);
    // setSpeed(150);
    // turnR90();
    // // leftMotorBackward();
    // // rightMotorForward();
    // motorsStop();
    // delay(2000);

    // switch (currentState){
    // case START:
    //     {
    //         //Serial.println("inside start state");
    //         num = communicate();
    //         if(num == -1){
    //             currentState = START; 
    //         } else currentState = (State) num; 
    //         //motorsStop();
    //         delay(500);
    //         //setSpeed(150);
    //         Serial.println(ir_read());
            
    //         //turnL90();
    //         //motorsStop();
    //         delay(500);
    //         break;
    //     }
    // case firstWALL:
    //     {
    //         //Serial.println("inside first wall state");
    //         num = communicate();
    //         if(num == -1){
    //             currentState = firstWALL; 
    //         } else currentState = (State) num; 
    //         motorsStop();
    //         delay(500);
    //         setSpeed(150);
    //         turnR90();
    //         //motorsStop();
    //         delay(500);
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

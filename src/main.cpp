#include <Wire.h>
#include <LiquidCrystal_I2C.h>
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

// 16x2 I2C LCD at address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// show one or two lines of status on the LCD
void lcdShowStatus(const char* line1, const char* line2 = "") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);

    if (line2 && line2[0] != '\0') {
        lcd.setCursor(0, 1);
        lcd.print(line2);
    }
}

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

    lcd.init();       // initialize the lcd
    lcd.backlight();  // open the backlight
    lcdShowStatus("Booting...", "Please wait");
    delay(500);
    lcdShowStatus("Idle", "Waiting...");
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


void loop() {
    int num = 0;
    int color[2] = {0};

    // to get a color just do: getColor(color);
    // color[0] = right sensor, color[1] = left sensor

    Serial.println(ir_read());  

    //when moving along lanes, want to check our distance each step with wall_close();
    //if wall_close() == true, then turn around / L/R and continue with bot motion
    //just set a global bool to help us change states

    // delay(1000);
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
    // motorsStop();
    // delay(2000);
    // setSpeed(150);
    // turnR90();
    // motorsStop();
    // delay(2000);

    // switch (currentState){
    // case START:
    //     {
    //         num = communicate();
    //         if(num == -1){
    //             currentState = START; 
    //         } else currentState = (State) num; 
    //         delay(500);
    //         Serial.println(ir_read());
    //         lcdShowStatus("State: START", "Waiting...");
    //         delay(500);
    //         break;
    //     }

    // case firstWALL:
    //     {
    //         num = communicate();
    //         if(num == -1){
    //             currentState = firstWALL; 
    //         } else currentState = (State) num; 
    //         motorsStop();
    //         delay(500);
    //         setSpeed(150);
    //         turnR90();
    //         lcdShowStatus("firstWALL", "Turning right");
    //         delay(500);
    //         break;
    //     }

    // case findCOLOR_X:
    //     {            
    //         num = communicate();
    //         if(num == -1){
    //             currentState = findCOLOR_X; 
    //         } else currentState = (State) num; 
    //         leftMotorStop();
    //         setLSpeed(50);
    //         leftMotorBackward();
    //         lcdShowStatus("Find Color X", "Backing up");
    //         break;
    //     }

    // case laneFOLLOW_X:
    //     {
    //         num = communicate();
    //         if(num == -1){
    //             currentState = laneFOLLOW_X; 
    //         } else currentState = (State) num; 
    //         setLSpeed(200);
    //         leftMotorForward();
    //         lcdShowStatus("LaneFollow X", "Forward");
    //         break;
    //     }

    // case findCOLOR_Y:
    //     num = communicate();
    //     if(num == -1){
    //         currentState = findCOLOR_Y; 
    //     } else currentState = (State) num; 
    //     setLSpeed(255);
    //     leftMotorBackward();
    //     lcdShowStatus("Find Color Y", "Backing up");
    //     break;
    
    // case laneFOLLOW_Y:
    //     num = communicate();
    //     if(num == -1){
    //         currentState = laneFOLLOW_Y; 
    //     } else currentState = (State) num; 
    //     setLSpeed(50);
    //     leftMotorBackward();
    //     lcdShowStatus("LaneFollow Y", "Backward");
    //     break;

    // case findSTART:
    //     num = communicate();
    //     if(num == -1){
    //         currentState = findSTART; 
    //     } else currentState = (State) num; 
    //     setLSpeed(250);
    //     leftMotorForward();
    //     lcdShowStatus("Find START", "Forward");
    //     break;

    // default:
    //     currentState = START;
    //     break;
    // }

}

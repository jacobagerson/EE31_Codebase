#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "main.h"

typedef enum { 
  START, 
  firstWALL,
  findRed,
  findBlue,
  followRed,
  findYellow,
  followYellow,
  laneFOLLOW_Y,
  findSTART, 
  idle 
} State;

State currentState = idle;

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

    //Color Sensing
    setUpColorPins();

	//start websocket up
    setupSocket();
    //delay(2500);
    writeMessage("Done with setup.");

    // lcd.init();       // initialize the lcd
    // lcd.backlight();  // open the backlight
    // lcdShowStatus("Booting...", "Please wait");
    // delay(500);
    // lcdShowStatus("Idle", "Waiting...");
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

    // // to get a color just do: getColor(color);
    // // color[0] = right sensor, color[1] = left sensor

    // //Serial.println(ir_read());  
    // getColor(color);
    // String left = "Left Color Sensor: " + (String)(color[1]);
    // String right = "Right Color Sensor: " + (String)(color[0]);
    // writeMessage(left);
    // writeMessage(right);
    // delay(500);

    // int a_amb, b_amb, a_red, b_red, a_blue, b_blue;

    // // reads values below

    // digitalWrite(13, HIGH); delay(25);
    // a_amb = analogRead(A0);
    // b_amb = analogRead(A1);

    // digitalWrite(7, HIGH); delay(25);
    // a_red = analogRead(A0) - a_amb;
    // b_red = analogRead(A1) - b_amb;
    // digitalWrite(7, LOW);

    // digitalWrite(12, HIGH); delay(25);
    // a_blue = analogRead(A0) - a_amb;
    // b_blue = analogRead(A1) - b_amb;
    // digitalWrite(12, LOW);
    // digitalWrite(13, LOW);


    // // debugging print 
    // // Serial.print("Sensor A:"); Serial.print(a_amb); Serial.print(", "); Serial.print(a_red); Serial.print(", "); Serial.println(a_blue); 
    // // Serial.print("Sensor B:"); Serial.print(b_amb); Serial.print(", "); Serial.print(b_red); Serial.print(", "); Serial.println(b_blue); 
        

    // // calculates the angles of the vector created by 
    // // the sensor reads

    // String a_blue_string = "Sensor A Blue: " + (String)(a_blue);
    // String a_red_string = "Sensor A Red: " + (String)(a_red);
    // String b_blue_string = "Sensor B Blue: " + (String)(b_blue);
    // String b_red_string = "Sensor B Red: " + (String)(b_red);
    // writeMessage(a_blue_string);
    // writeMessage(a_red_string);
    // writeMessage(b_blue_string);
    // writeMessage(b_red_string);
    // delay(50);

    //when moving along lanes, want to check our distance each step with wall_close();
    //if wall_close() == true, then turn around / L/R and continue with bot motion
    //just set a global bool to help us change states

    switch (currentState){
    // case START:
    //     {
    //         // num = communicate();
    //         // if(num == -1){
    //         //     currentState = START; 
    //         // } else currentState = (State) num; 
    //         // delay(500);
    //         // Serial.println(ir_read());
    //         // lcdShowStatus("State: START", "Waiting...");
    //         // delay(500);
    //         // break;
    //     }
    case firstWALL:
        {
            num = communicate();
            if(num == -1){
                currentState = firstWALL; 
            } else currentState = (State) num; 
            motorsStop();
            delay(500);
            //setSpeed(150);
            //turnR90();
            //lcdShowStatus("firstWALL", "Turning right");
            //delay(500);
            while(!wall_close()){
                moveForward();
                writeMessage((String)ir_read());
                //lcdShowStatus("firstWALL", "Moving to wall");
            }
            writeMessage(String(ir_read()));
            motorsStop();
            delay(500);
            writeMessage("Hit first wall.");
            //Serial.println(getMessage(readMessage()));
            turn180();
            delay(200);
            currentState = findRed;
            break;
        }
    case findRed: 
        {
            num = communicate();
            if(num == -1){
                currentState = firstWALL; 
            } else currentState = (State) num; 
            motorsStop();
            delay(500);
            // moveForward();
            // delay(2000);
            //setSpeed(150);
            //turnR90();
            //lcdShowStatus("firstWALL", "Turning right");
            //delay(500);
            getColor(color);
            while(color[0] != 1 || color[1] != 1){
                moveForward();
                getColor(color);
                String left = "Left Color Sensor: " + (String)(color[1]);
                String right = "Right Color Sensor: " + (String)(color[0]);
                writeMessage(left);
                writeMessage(right);
                //writeMessage((String)ir_read());
                //lcdShowStatus("firstWALL", "Moving to wall");
            }
            motorsStop();
            delay(500);
            writeMessage("Hit red strip wall.");
            //Serial.println(getMessage(readMessage()));
            getColor(color);
            while(color[1] == 1){
                turnLeftSmall();
                getColor(color);
            }
            delay(200);
            currentState = followRed;
            break;
        }
    case followRed:
        {
            // num = communicate();
            // if(num == -1){
            //     currentState = laneFOLLOW_X; 
            // } else currentState = (State) num; 
            //0 - black, 1 - red, 2 - blue, 3 - yellow
            //color[0] = right 
            //color[1] = left
            //lcdShowStatus("LaneFollow X", "Forward");
            while(!wall_close()){
                getColor(color);
                String left = "Left Color Sensor: " + (String)(color[1]);
                String right = "Right Color Sensor: " + (String)(color[0]);
                writeMessage(left);
                writeMessage(right);
                if (color[0] == 0 && color[1] == 1){
                    turnLeftSmall();
                    moveSlow();
                }
                else if (color[0] == 1 && color[1] == 0){
                    turnRightSmall();
                    moveSlow();
                }
                else {
                    moveSlow();
                }
            }
            if(wall_close()){
                motorsStop();
                delay(500);
                writeMessage("Wall detected during red lane follow.");
                while(color[0] == 1){
                    turnLeftSmall();
                    getColor(color);
                }
                currentState = findYellow;
                // //go to the yellow line
                // lcdShowStatus("Find Yellow", "Forward");
                // currentState = findCOLOR_Y;
                // break;
            }
            break;
        }
    case findYellow:
        {
            num = communicate();
            if(num == -1){
                currentState = findYellow; 
            } else currentState = (State) num; 
            lcdShowStatus("Find Yellow", "Backing up");
            getColor(color);
            while(color[0] != 3 || color[1] != 3){
                moveForward();
                getColor(color);
                String left = "Left Color Sensor: " + (String)(color[1]);
                String right = "Right Color Sensor: " + (String)(color[0]);
                writeMessage(left);
                writeMessage(right);
                //writeMessage((String)ir_read());
                //lcdShowStatus("firstWALL", "Moving to wall");
            }
            motorsStop();
            delay(500);
            writeMessage("Hit yellow strip.");
            //Serial.println(getMessage(readMessage()));
            while(color[1] == 3){
                turnLeftSmall();
                getColor(color);
            }
            delay(200);
            currentState = followYellow;
            break;
        }
    
    case followYellow:
        {            
            // num = communicate();
            // if(num == -1){
            //     currentState = findCOLOR_X; 
            // } else currentState = (State) num; 
            //looking for red
            while(!wall_close()){
                getColor(color);
                String left = "Left Color Sensor: " + (String)(color[1]);
                String right = "Right Color Sensor: " + (String)(color[0]);
                writeMessage(left);
                writeMessage(right);
                if (color[0] == 0 && color[1] == 3){
                    turnLeftSmall();
                    moveSlow();
                }
                else if (color[0] == 3 && color[1] == 0){
                    turnRightSmall();
                    moveSlow();
                }
                else {
                    moveSlow();
                }
            }
            motorsStop();
            writeMessage("Hit yellow wall");
            //delay(5000);
            turnL90();
            delay(200);
            currentState = idle;

            // leftMotorStop();
            // setLSpeed(50);
            // leftMotorBackward();
            // lcdShowStatus("Find Color X", "Backing up");
            break;
        }
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

    case idle:
        num = communicate();
        if(num == -1){
            currentState = idle; 
        } else currentState = (State) num; 
        motorsStop();
        //lcdShowStatus("Idle", "Waiting...");
        break;
    default:
        currentState = idle;
        break;
    }

}

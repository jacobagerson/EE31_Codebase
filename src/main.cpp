/**
 * main.cpp
 * Written by Cooper Bailey, Asher Milberg, Jacob Gerson, Mason Doshi
 * 
 * Main control program for the single-robot system.
 * 
 * This file contains the primary state-machine logic used to run
 * the standalone (single) robot configuration. It handles all
 * movement, color sensing, wall detection, and communication
 * required for autonomous operation of a single bot.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "main.h"

typedef enum { 
    firstWALL_R,
    firstWALL_B,
    findRed,
    findBlue,
    followBlue,
    followRed,
    findYellow_R,
    followYellow_R,
    findYellow_B,
    followYellow_B,
    finish,
    idle
} State;

State currentState = idle;
String ID = "YOUR ID";

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

//Set up all the pins and connect our bot to the websocket
//writes a message to the websocket saying it is done and switches to the idle state
void setup() {
	//initialize serial monitor
    Serial.begin(9600);

	//initialize motor pins
	setupMotorPins();
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);

    //Color Sensing
    setUpColorPins();
    lcd.init();       // initialize the lcd
    lcd.backlight();  // open the backlight
    lcdShowStatus("Booting...", "Please wait");

	//start websocket up
    setupSocket();
    writeMessage("Done with setup.");
    lcdShowStatus("Setup Complete", "Ready To Start");
}
//Communicate with the bot by parsing for only our ID and the specific commands we send
int communicate() {
    String message = readMessage();
    int state = -1;

    if (message.length() > 0 && parseID(message) == ID) {
        String stateStr = getMessage(message);
        state = stateStr.toInt();
    }

    if(state <= 11 && state >= 0){
        return state; 
    } else return -1; 
}


void loop() {
    int num = 0;
    int color[2] = {0};

    switch (currentState){
    // ============================
    // FIRST WALL (RED BOT)
    // - Drives forward until a wall is detected
    // - Backs up and turns left 180 degrees
    // - Transitions to findRed
    // ============================
    case firstWALL_R:
        {
            num = communicate();
            if(num == -1){
                currentState = firstWALL_R; 
            } else currentState = (State) num; 
            motorsStop();
            delay(500);
            lcdShowStatus("firstWALL", "Moving to wall");
            while(!wall_close()){
                moveForward();
            }
            motorsStop();
            delay(500);
            writeMessage("Hit first wall.");
            lcdShowStatus("firstWALL", "Hit first wall");
            moveBackward();
            delay(200);
            motorsStop();
            turnL180();
            delay(200);
            currentState = findRed;
            break;
        }
    // ============================
    // FIRST WALL (BLUE BOT)
    // - Drives forward until a wall is detected
    // - Backs up and turns right 180 degrees
    // - Transitions to findBlue
    // ============================
    case firstWALL_B: 
        {
            num = communicate();
            if(num == -1){
                currentState = firstWALL_B; 
            } else currentState = (State) num; 
            motorsStop();
            delay(500);
            while(!wall_close()){
                moveForward();
                lcdShowStatus("firstWALL", "Moving to wall");
            }

            motorsStop();
            moveBackward();
            delay(200);
            writeMessage("Hit first wall.");
            lcdShowStatus("firstWALL", "Hit first wall");

            turnR180();
            delay(200);
            currentState = findBlue;
            break;
        }   
    // ============================
    // FIND RED LANE
    // - Moves into lane region
    // - Rotates until both sensors detect red
    // - Turns left and transitions to followRed
    // ============================
    case findRed: 
        {
            num = communicate();
            if(num == -1){
                currentState = findRed; 
            } else currentState = (State) num; 
            motorsStop();
            delay(500);
            moveForward();
            delay(1500);
            getColor(color);
            while(color[0] != RED || color[1] != RED){
                moveSlowR();
                getColor(color);
                lcdShowStatus("", "Finding Red");
            }
            motorsStop();
            delay(500);
            writeMessage("Hit red strip wall.");
            lcdShowStatus("", "Found Red");
            turnL90();
            delay(200);
            currentState = followRed;
            break;
        }
    // ============================
    // FOLLOW RED LANE
    // - Tracks red lane using both color sensors
    // - Makes small steering corrections
    // - On wall detection, turns toward yellow
    // ============================
    case followRed:
        {
            writeMessage("Following red lane.");
            lcdShowStatus("", "Follow Red Lane");
            while(!wall_close()){
                getColor(color);
                if (color[0] == BLACK && color[1] == RED){
                    turnLeftSmall();
                    moveSlow();
                    delay(25);
                }
                else if (color[0] == RED && color[1] == RED){
                    turnRightSmall();
                    moveSlow();
                    delay(25);
                }
                else {
                    moveSlow();
                }
            }
            if(wall_close()){
                motorsStop();
                delay(500);
                writeMessage("Wall detected during red lane follow.");
                moveBackward();
                delay(350);
                lcdShowStatus("", "Turn to Yellow");

                turnL135();
                currentState = findYellow_R;
            }
            break;
        }
    // ============================
    // FIND BLUE LANE
    // - Moves into lane region
    // - Searches until both sensors detect blue
    // - Turns right and transitions to followBlue
    // ============================
    case findBlue:{
            num = communicate();
            if(num == -1){
                currentState = findBlue; 
            } else currentState = (State) num; 
            motorsStop();
            delay(500);
            moveForward();
            delay(1500);
            getColor(color);
            lcdShowStatus("", "Find Blue");
            while(color[0] != BLUE || color[1] != BLUE){
                moveSlow();
                getColor(color);
            }
            motorsStop();
            delay(500);
            writeMessage("Hit blue strip wall.");
            lcdShowStatus("", "Found Blue");
            turnR90();
            moveBackward();
            delay(200);
            motorsStop();
            delay(200);
            currentState = followBlue;
            break;
    }
    // ============================
    // FOLLOW BLUE LANE
    // - Tracks blue lane using both sensors
    // - Makes steering corrections
    // - On wall detection, turns toward yellow
    // ============================
    case followBlue:
        {
            lcdShowStatus("Lane Follow", "Follow Blue");
            writeMessage("Following blue lane.");
            while(!wall_close()){
                getColor(color);
                if (color[0] == BLACK && color[1] == BLUE){
                    turnLeftSmall();
                    moveSlow();
                    delay(25);
                }
                else if (color[0] == BLUE && color[1] == BLACK){
                    turnRightSmall();
                    moveSlow();
                    delay(25);
                }
                else {
                    moveSlow();
                }
            }
            if(wall_close()){
                motorsStop();
                delay(500);
                writeMessage("Wall detected during blue lane follow.");
                lcdShowStatus("", "Turn to Yellow");
                moveBackward();
                delay(350);

                turnR135();
                currentState = findYellow_B;
            }
            break;
        }
    // ============================
    // FIND YELLOW (FROM RED PATH)
    // - Searches for yellow strip
    // - Turns left and transitions to followYellow_R
    // ============================
    case findYellow_R:
        {
            num = communicate();
            if(num == -1){
                currentState = findYellow_R; 
            } else currentState = (State) num; 
            lcdShowStatus("Find Yellow", "");
            getColor(color);
            while(color[0] != YELLOW || color[1] != YELLOW){
                moveSlow();
                getColor(color);
            }
            motorsStop();
            delay(500);
            writeMessage("Hit yellow strip.");
            lcdShowStatus("","Hit Yellow");
            turnL90();
            delay(200);
            currentState = followYellow_R;
            break;
        }
    // ============================
    // FOLLOW YELLOW (FROM RED PATH)
    // - Follows yellow lane
    // - On wall detection transitions to finish
    // ============================
    case followYellow_R:
        {            
            writeMessage("Follow yellow");
            lcdShowStatus("Follow Yellow", "");
            while(!wall_close()){
                getColor(color);
                if (color[0] == BLACK && color[1] == YELLOW){
                    turnLeftSmall();
                    moveSlow();
                    delay(25);
                }
                else if (color[0] == YELLOW && color[1] == BLACK){
                    turnRightSmall();
                    moveSlow();
                    delay(25);
                }
                else {
                    moveSlow();
                }
            }
            motorsStop();
            writeMessage("Hit yellow wall");
            lcdShowStatus("", "Hit Wall");
            moveBackward();
            delay(200);
            motorsStop();
            turnL90();
            delay(200);
            currentState = finish;
            break;
        }
    // ============================
    // FIND YELLOW (FROM BLUE PATH)
    // - Searches for yellow strip
    // - Turns right and transitions to followYellow_B
    // ============================
    case findYellow_B:
        {
            num = communicate();
            if(num == -1){
                currentState = findYellow_B; 
            } else currentState = (State) num; 
            lcdShowStatus("Find Yellow", "");
            getColor(color);
            while(color[0] != YELLOW || color[1] != YELLOW){
                moveSlow();
                getColor(color);
            }
            motorsStop();
            delay(500);
            writeMessage("Hit yellow strip.");
            lcdShowStatus("","Hit Yellow");
            turnR90();
            delay(200);
            currentState = followYellow_B;
            break;
        }
    // ============================
    // FOLLOW YELLOW (FROM BLUE PATH)
    // - Follows yellow lane
    // - On wall detection transitions to finish
    // ============================
    case followYellow_B:
        {            
            lcdShowStatus("Follow Yellow", "");
            while(!wall_close()){
                getColor(color);
                if (color[0] == BLACK && color[1] == YELLOW){
                    turnLeftSmall();
                    moveSlow();
                    delay(25);
                }
                else if (color[0] == YELLOW && color[1] == BLACK){
                    turnRightSmall();
                    moveSlow();
                    delay(25);
                }
                else {
                    moveSlow();
                }
            }
            motorsStop();
            writeMessage("Hit yellow wall");
            delay(5000);
            moveBackward();
            delay(100);
            motorsStop();
            turnR90();
            delay(200);
            currentState = finish;
            break;
        }

    // ============================
    // FINISH STATE
    // - Drives forward until final wall
    // - Stops motors
    // - Displays completion message
    // - Returns to idle
    // ============================
    case finish:{
        while(!wall_close()){
            moveForward();
        }
        motorsStop();
        lcdShowStatus("Finished", "Task complete");
        writeMessage("Finished all tasks.");
        currentState = idle;
        break;
    }     
    // ============================
    // IDLE STATE
    // - Stops all motors
    // - Waits for new command via websocket
    // ============================
    case idle:
    {
        num = communicate();
        if(num == -1){
            currentState = idle; 
        } else currentState = (State) num; 
        motorsStop();
        lcdShowStatus("Idle", "Waiting...");
        break;
    }

    default:
        currentState = idle;
        break;
    }
}

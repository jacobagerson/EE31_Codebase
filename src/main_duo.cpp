/**
 * main_duo.cpp
 * Written by Cooper Bailey, Asher Milberg, Jacob Gerson, and Mason Doshi
 * 
 * Main control program for the dual-robot (duo bot) system.
 * 
 * This file contains the primary state-machine logic used to run both
 * robots in the duo configuration. The same codebase is used for both
 * Bot 1 and Bot 2; the only modification required for Bot 2 is to
 * comment out line 449.
 */


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "main.h"

typedef enum { 
    idle,  //0
    firstWALL_R,
    firstWALL_B, //2
    findRed,
    findBlue,
    followBlue,
    followRed,
    findYellow_R,
    followYellow_R,
    findYellow_B,
    followYellow_B, //10 
    finish,
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

//Set up all the pins and connect our bot to the websocket
//writes a message to the websocket saying it is done and switches to the idle state
void setup() {
	//initialize serial monitor
    Serial.begin(9600);

	//initialize motor pins
	setupMotorPins();

    //Color Sensing
    setUpColorPins();
    lcd.init();       // initialize the lcd
    lcd.backlight();  // open the backlight
    lcdShowStatus("Booting...", "Please wait");
    //Connect to Websocket
    setupSocket();
    writeMessage("Done with setup.");
    lcdShowStatus("Setup Complete", "Ready To Start");
}



void loop() {
    int num = 0;
    int color[2] = {0};
    switch (currentState) {
        // ============================
    // IDLE STATE
    // - Stops all motors
    // - Displays "Idle - Waiting..." on the LCD
    // - Listens for incoming WebSocket messages
    // - Parses MACJ command for new state
    // - Transitions to new state if valid command is received
    // ============================
    case idle:
    {
        String msg = readMessage();
        int msgSize = msg.length();
        if (msgSize > 0) {
          int pos = msg.indexOf('.');
          if (pos != -1) {
            String stateStr = msg.substring(pos + 1);
            if (stateStr.startsWith("MACJ")) {
              stateStr = stateStr.substring(5);
              int stateNum = stateStr.toInt();
              currentState = (State) stateNum;
            }
          }
        }
        else currentState = idle;
        motorsStop();
        lcdShowStatus("Idle", "Waiting...");
        break;
    }
    // ============================
    // FIRST WALL (RED BOT)
    // - Drives forward until the wall is detected
    // - Sends IR sensor reading and wall hit message
    // - Backs up slightly after contact
    // - Turns left 180 degrees
    // - Transitions to findRed
    // ============================
    case firstWALL_R:
        {
            motorsStop();
            delay(500);
            lcdShowStatus("firstWALL", "Moving to wall");
            while(!wall_close()){
                moveForward();
            }
            writeMessage(String(ir_read()));
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
    // - Drives forward until the wall is detected
    // - Backs up after contact
    // - Sends wall hit message
    // - Turns right 180 degrees
    // - Transitions to findBlue
    // ============================
    case firstWALL_B: {
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
    // - Moves forward into lane region
    // - Rotates slowly until both color sensors detect red
    // - Displays "Found Red" on LCD
    // - Sends WebSocket confirmation
    // - Backs up and aligns with lane
    // - Transitions to followRed
    // ============================
    case findRed: 
        {
            motorsStop();
            delay(500);
            moveForward();
            delay(1500);
            getColor(color);
            while(color[0] != 1 || color[1] != 1){
                moveSlowR();
                getColor(color);
                lcdShowStatus("", "Finding Red");
            }
            motorsStop();
            delay(500);
            lcdShowStatus("", "Found Red");
            writeMessage("red lane found");
            writeMessage("RIDJ 1");
            moveBackward();
            delay(200);
            motorsStop();
            turnLSmall();
            moveMedium();
            delay(25);
            delay(200);
            currentState = followRed;
            break;
        }
    // ============================
    // FOLLOW RED LANE
    // - Follows red lane using dual color sensors
    // - Makes left/right corrections based on color position
    // - Continues until wall is detected
    // - Backs up and turns left toward yellow
    // - Transitions to findYellow_R
    // ============================
    case followRed:
        {
            writeMessage("Following red lane.");
            lcdShowStatus("", "Follow Red Lane");
            while(!wall_close()){
                getColor(color);
                if (color[0] == 0 && color[1] == 1){
                    turnLeftSmall();
                    moveSlow();
                    delay(15);
                }
                else if (color[0] == 1 && color[1] == 0){
                    turnRightSmall();
                    moveSlow();
                    delay(15);
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
    // - Moves forward into lane region
    // - Scans until both sensors detect blue
    // - Displays "Found Blue" on LCD
    // - Sends WebSocket confirmation
    // - Turns right and aligns with lane
    // - Transitions to followBlue
    // ============================
    case findBlue:{
            motorsStop();
            delay(500);
            moveForward();
            delay(1500);
            getColor(color);
            lcdShowStatus("", "Find Blue");
            while(color[0] != 2 || color[1] != 2){
                moveSlow();
                getColor(color);
            }
            motorsStop();
            delay(500);
            writeMessage("blue lane found");
            writeMessage("RIDJ 5");
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
    // - Follows blue lane using dual color sensors
    // - Makes left/right corrections based on color position
    // - Continues until wall is detected
    // - Backs up and turns right toward yellow
    // - Transitions to findYellow_B
    // ============================
    case followBlue:
        {
            lcdShowStatus("Lane Follow", "Follow Blue");
            writeMessage("Following blue lane.");
            while(!wall_close()){
                getColor(color);
                if (color[0] == 0 && color[1] == 2){
                    turnLeftSmall();
                    moveSlow();
                    delay(25);
                }
                else if (color[0] == 2 && color[1] == 0){
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
    // - Scans for yellow strip
    // - Moves slowly until both sensors detect yellow
    // - Sends confirmation message
    // - Turns left 90 degrees
    // - Returns to idle
    // ============================
    case findYellow_R:
        {
            lcdShowStatus("Find Yellow", "");
            getColor(color);
            while(color[0] != 3 || color[1] != 3){
                moveSlow();
                getColor(color);
            }
            motorsStop();
            delay(500);
            writeMessage("Hit yellow strip.");
            lcdShowStatus("","Hit Yellow");
            turnL90();
            delay(200);
            currentState = idle;
            break;
        }
    // ============================
    // FOLLOW YELLOW (FROM RED PATH)
    // - Follows yellow lane using color sensors
    // - Makes left/right corrections
    // - Continues until wall is detected
    // - Backs up and turns left 90 degrees
    // - Transitions to finish
    // ============================
    case followYellow_R:
        {            
            writeMessage("Follow yellow");
            lcdShowStatus("Follow Yellow", "");
            while(!wall_close()){
                getColor(color);
                if (color[0] == 0 && color[1] == 3){
                    turnLeftSmall();
                    moveSlow();
                    delay(15);
                }
                else if (color[0] == 3 && color[1] == 0){
                    turnRightSmall();
                    moveSlow();
                    delay(15);
                }
                else {
                    moveMedium();
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
    // - Scans for yellow strip
    // - Moves slowly until both sensors detect yellow
    // - Sends confirmation message
    // - Turns right 90 degrees
    // - Returns to idle
    // ============================
    case findYellow_B:
        {
            lcdShowStatus("Find Yellow", "");
            getColor(color);
            while(color[0] != 3 || color[1] != 3){
                moveSlow();
                getColor(color);
            }
            motorsStop();
            delay(500);
            writeMessage("Hit yellow strip.");
            lcdShowStatus("","Hit Yellow");
            turnR90();
            delay(200);
            currentState = idle;
            break;
        }
    // ============================
    // FOLLOW YELLOW (FROM BLUE PATH)
    // - Follows yellow lane using color sensors
    // - Makes left/right corrections
    // - Continues until wall is detected
    // - Backs up and turns right 90 degrees
    // - Transitions to finish
    // ============================
    case followYellow_B:
        {            
            lcdShowStatus("Follow Yellow", "");
            while(!wall_close()){
                getColor(color);
                if (color[0] == 0 && color[1] == 3){
                    turnLeftSmall();
                    moveSlow();
                    delay(25);
                }
                else if (color[0] == 3 && color[1] == 0){
                    turnRightSmall();
                    moveSlow();
                    delay(25);
                }
                else {
                    moveMedium();
                }
            }
            motorsStop();
            writeMessage("Hit yellow wall");
            moveBackward();
            delay(100);
            motorsStop();
            turnR90Y();
            delay(200);
            currentState = finish;
            break;
        }
    // ============================
    // FINISH STATE
    // - Drives forward until final wall is detected
    // - Stops all motors
    // - Displays "Finished - Task Complete"
    // - Sends completion message
    // - Waits for new MACJ command to restart
    // ============================
    case finish:{
        while(!wall_close()){
            moveForward();
        }
        motorsStop();
        lcdShowStatus("Finished", "Task complete");
        writeMessage("RIDJ 5");
        String msg = readMessage();
        int msgSize = msg.length();
        if (msgSize > 0) {
          int pos = msg.indexOf('.');
          if (pos != -1) {
            String stateStr = msg.substring(pos + 1);
            if (stateStr.startsWith("MACJ")) {
              stateStr = stateStr.substring(5);
              int stateNum = stateStr.toInt();
              currentState = (State) stateNum;
            }
          }
        }
        else {
            currentState = finish;
            delay(500);
        }
        break;
    }  

    default:
        currentState = idle;
        break;
    }
}
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include "main.h"

// typedef enum { 
//     START, 
//     firstWALL_R,
//     firstWALL_B,
//     findRed,
//     findBlue,
//     followBlue,
//     followRed,
//     findYellow_R,
//     followYellow_R,
//     findYellow_B,
//     followYellow_B,
//     laneFOLLOW_Y,
//     findSTART, 
//     finish,
//     idle
// } State;

// State currentState = idle;

// // 16x2 I2C LCD at address 0x27
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// // show one or two lines of status on the LCD
// void lcdShowStatus(const char* line1, const char* line2 = "") {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print(line1);

//     if (line2 && line2[0] != '\0') {
//         lcd.setCursor(0, 1);
//         lcd.print(line2);
//     }
// }

// void blink(int pin, int num){
//     for(int i = 0; i < num; i++){
//         digitalWrite(pin, HIGH);
//         delay(500);
//         digitalWrite(pin, LOW);
//         delay(500);
//     }
// }

// void setup() {
// 	//initialize serial monitor
//     Serial.begin(9600);

// 	//initialize motor pins
// 	setupMotorPins();
//     pinMode(2, OUTPUT);
//     digitalWrite(2, HIGH);

//     //Color Sensing
//     setUpColorPins();
//     lcd.init();       // initialize the lcd
//     lcd.backlight();  // open the backlight
//     lcdShowStatus("Booting...", "Please wait");

// 	//start websocket up
//     setupSocket();
//     //delay(2500);
//     writeMessage("Done with setup.");
//     lcdShowStatus("Setup Complete", "Ready To Start");
//     //delay(500);
//     //lcdShowStatus("Idle", "Waiting...");
// }

// int communicate() {
//     String message = readMessage();
//     int state = -1;

//     if (message.length() > 0 && parseID(message) == "8050D1451904") {
//         String stateStr = getMessage(message);
//         state = stateStr.toInt();
//         //Serial.println(state);
//     }

//     if(state <= 6 && state >= 0){
//         return state; 
//     } else return -1; 
// }


// void loop() {
//     int num = 0;
//     int color[2] = {0};

//     // to get a color just do: getColor(color);
//     // color[0] = right sensor, color[1] = left sensor

//     // //Serial.println(ir_read());  
//     // getColor(color);
//     // String left = "Left Color Sensor: " + (String)(color[1]);
//     // String right = "Right Color Sensor: " + (String)(color[0]);
//     // writeMessage(left);
//     // writeMessage(right);
//     // delay(50);

    

//     // // reads values below
//     // int a_amb, b_amb, a_red, b_red, a_blue, b_blue;

//     // digitalWrite(13, HIGH); delay(25);
//     // a_amb = analogRead(A0);
//     // b_amb = analogRead(A1);

//     // digitalWrite(7, HIGH); delay(25);
//     // a_red = analogRead(A0) - a_amb;
//     // b_red = analogRead(A1) - b_amb;
//     // digitalWrite(7, LOW);

//     // digitalWrite(12, HIGH); delay(25);
//     // a_blue = analogRead(A0) - a_amb;
//     // b_blue = analogRead(A1) - b_amb;
//     // digitalWrite(12, LOW);
//     // digitalWrite(13, LOW);

//     // float a_angle = atan2f((float)a_blue, (float)a_red)*(180/PI);
//     // float b_angle = atan2f((float)b_blue, (float)b_red)*(180/PI);

//     // writeMessage("Sensor A: " + String(a_angle));
//     // writeMessage("Sensor B: " + String(b_angle));

//     // Serial.println(ir_read());
//     // delay(200);

//     //writeMessage("IR Read: " + String(ir_read()));

//     //moveForward();


//     // // // debugging print 
//     // // // Serial.print("Sensor A:"); Serial.print(a_amb); Serial.print(", "); Serial.print(a_red); Serial.print(", "); Serial.println(a_blue); 
//     // // // Serial.print("Sensor B:"); Serial.print(b_amb); Serial.print(", "); Serial.print(b_red); Serial.print(", "); Serial.println(b_blue); 
        

//     // // calculates the angles of the vector created by 
//     // // // the sensor reads


//     switch (currentState){
//     case START:
//         {
//             // num = communicate();
//             // if(num == -1){
//             //     currentState = START; 
//             // } else currentState = (State) num; 
//             // delay(500);
//             // Serial.println(ir_read());
//             // lcdShowStatus("State: START", "Waiting...");
//             // delay(500);
//             // break;
//         }
//     case firstWALL_R:
//         {
//             num = communicate();
//             if(num == -1){
//                 currentState = firstWALL_R; 
//             } else currentState = (State) num; 
//             motorsStop();
//             delay(500);
//             //setSpeed(150);
//             //turnR90();
//             //lcdShowStatus("firstWALL", "Turning right");
//             //delay(500);
//             lcdShowStatus("firstWALL", "Moving to wall");
//             while(!wall_close()){
//                 moveForward();
//                 //writeMessage((String)ir_read());
//             }
//             writeMessage(String(ir_read()));
//             motorsStop();
//             delay(500);
//             writeMessage("Hit first wall.");
//             lcdShowStatus("firstWALL", "Hit first wall");
//             moveBackward();
//             delay(200);
//             motorsStop();
//             //Serial.println(getMessage(readMessage()));
//             turnL180();
//             delay(200);
//             currentState = findRed;
//             break;
//         }
//     case firstWALL_B: {
//             num = communicate();
//             if(num == -1){
//                 currentState = firstWALL_B; 
//             } else currentState = (State) num; 
//             motorsStop();
//             delay(500);
//             //setSpeed(150);
//             //turnR90();
//             //lcdShowStatus("firstWALL", "Turning right");
//             //delay(500);
//             while(!wall_close()){
//                 moveForward();
//                 //writeMessage((String)ir_read());
//                 lcdShowStatus("firstWALL", "Moving to wall");
//             }
//             //writeMessage(String(ir_read()));
//             motorsStop();
//             moveBackward();
//             delay(200);
//             writeMessage("Hit first wall.");
//             lcdShowStatus("firstWALL", "Hit first wall");
//             //Serial.println(getMessage(readMessage()));
//             turnR180();
//             delay(200);
//             currentState = findBlue;
//             break;

//     }
//     case findRed: 
//         {
//             num = communicate();
//             if(num == -1){
//                 currentState = findRed; 
//             } else currentState = (State) num; 
//             motorsStop();
//             delay(500);
//             // moveForward();
//             // delay(2000);
//             //setSpeed(150);
//             //turnR90();
//             //lcdShowStatus("firstWALL", "Turning right");
//             //delay(500);
//             moveForward();
//             delay(1500);
//             getColor(color);
//             while(color[0] != RED || color[1] != RED){
//                 moveSlowR();
//                 getColor(color);
//                 // String left = "Left Color Sensor: " + (String)(color[1]);
//                 // String right = "Right Color Sensor: " + (String)(color[0]);
//                 // writeMessage(left);
//                 // writeMessage(right);
//                 lcdShowStatus("", "Finding Red");
//                 //writeMessage((String)ir_read());
//                 //lcdShowStatus("firstWALL", "Moving to wall");
//             }
//             motorsStop();
//             delay(500);
//             writeMessage("Hit red strip wall.");
//             lcdShowStatus("", "Found Red");
//             //Serial.println(getMessage(readMessage()));
//             // getColor(color);
//             // while(color[1] == 1){
//             //     turnLeftSmall();
//             //     getColor(color);
//             // }
//             // moveBackward();
//             // delay(200);
//             // motorsStop();
//             turnL90();
//             delay(200);
//             currentState = followRed;
//             break;
//         }
//     case followRed:
//         {
//             // num = communicate();
//             // if(num == -1){
//             //     currentState = laneFOLLOW_X; 
//             // } else currentState = (State) num; 
//             //0 - black, 1 - red, 2 - blue, 3 - yellow
//             //color[0] = right 
//             //color[1] = left
//             //lcdShowStatus("LaneFollow X", "Forward");
//             writeMessage("Following red lane.");
//             lcdShowStatus("", "Follow Red Lane");
//             while(!wall_close()){
//                 getColor(color);
//                 // String left = "Left Color Sensor: " + (String)(color[1]);
//                 // String right = "Right Color Sensor: " + (String)(color[0]);
//                 // writeMessage(left);
//                 // writeMessage(right);
//                 if (color[0] == BLACK && color[1] == RED){
//                     turnLeftSmall();
//                     moveSlow();
//                     delay(25);
//                 }
//                 else if (color[0] == RED && color[1] == RED){
//                     turnRightSmall();
//                     moveSlow();
//                     delay(25);
//                 }
//                 else {
//                     moveSlow();
//                 }
//             }
//             if(wall_close()){
//                 motorsStop();
//                 delay(500);
//                 writeMessage("Wall detected during red lane follow.");
//                 moveBackward();
//                 delay(350);
//                 lcdShowStatus("", "Turn to Yellow");

//                 turnL135();
//                 currentState = findYellow_R;
//                 // //go to the yellow line
//                 // lcdShowStatus("Find Yellow", "Forward");
//                 // currentState = findCOLOR_Y;
//                 // break;
//             }
//             break;
//         }
//     case findBlue:{
//             num = communicate();
//             if(num == -1){
//                 currentState = findBlue; 
//             } else currentState = (State) num; 
//             motorsStop();
//             delay(500);
//             // moveForward();
//             // delay(2000);
//             //setSpeed(150);
//             //turnR90();
//             //lcdShowStatus("firstWALL", "Turning right");
//             //delay(500);
//             moveForward();
//             delay(1500);
//             getColor(color);
//             lcdShowStatus("", "Find Blue");
//             while(color[0] != BLUE || color[1] != BLUE){
//                 moveSlow();
//                 getColor(color);
//                 // String left = "Left Color Sensor: " + (String)(color[1]);
//                 // String right = "Right Color Sensor: " + (String)(color[0]);
//                 // writeMessage(left);
//                 // writeMessage(right);
//                 //writeMessage((String)ir_read());
//                 //lcdShowStatus("firstWALL", "Moving to wall");
//             }
//             motorsStop();
//             delay(500);
//             writeMessage("Hit blue strip wall.");
//             lcdShowStatus("", "Found Blue");
//             //Serial.println(getMessage(readMessage()));
//             turnR90();
//             // moveBackward();
//             // delay(200);
//             // motorsStop();
//             delay(200);
//             currentState = followBlue;
//             break;
//     }
//     case followBlue:
//         {

//             // num = communicate();
//             // if(num == -1){
//             //     currentState = laneFOLLOW_X; 
//             // } else currentState = (State) num; 
//             //0 - black, 1 - red, 2 - blue, 3 - yellow
//             //color[0] = right 
//             //color[1] = left
//             lcdShowStatus("Lane Follow", "Follow Blue");
//             writeMessage("Following blue lane.");
//             while(!wall_close()){
//                 getColor(color);
//                 // String left = "Left Color Sensor: " + (String)(color[1]);
//                 // String right = "Right Color Sensor: " + (String)(color[0]);
//                 // writeMessage(left);
//                 // writeMessage(right);
//                 if (color[0] == BLACK && color[1] == BLUE){
//                     turnLeftSmall();
//                     moveSlow();
//                     delay(25);
//                 }
//                 else if (color[0] == BLUE && color[1] == BLACK){
//                     turnRightSmall();
//                     moveSlow();
//                     delay(25);
//                 }
//                 else {
//                     moveSlow();
//                 }
//             }
//             if(wall_close()){
//                 motorsStop();
//                 delay(500);
//                 writeMessage("Wall detected during blue lane follow.");
//                 lcdShowStatus("", "Turn to Yellow");
//                 moveBackward();
//                 delay(350);

//                 turnR135();
//                 currentState = findYellow_B;
//                 // //go to the yellow line
//                 // lcdShowStatus("Find Yellow", "Forward");
//                 // currentState = findCOLOR_Y;
//                 // break;
//             }
//             break;
//         }
//     case findYellow_R:
//         {
//             num = communicate();
//             if(num == -1){
//                 currentState = findYellow_R; 
//             } else currentState = (State) num; 
//             lcdShowStatus("Find Yellow", "");
//             getColor(color);
//             while(color[0] != YELLOW || color[1] != YELLOW){
//                 moveSlow();
//                 getColor(color);
//                 // String left = "Left Color Sensor: " + (String)(color[1]);
//                 // String right = "Right Color Sensor: " + (String)(color[0]);
//                 // writeMessage(left);
//                 // writeMessage(right);
//                 //writeMessage((String)ir_read());
//                 //lcdShowStatus("firstWALL", "Moving to wall");
//             }
//             motorsStop();
//             delay(500);
//             writeMessage("Hit yellow strip.");
//             lcdShowStatus("","Hit Yellow");
//             //Serial.println(getMessage(readMessage()));
//             // moveBackward();
//             // delay(200);
//             // motorsStop();
//             turnL90();
//             delay(200);
//             currentState = followYellow_R;
//             break;
//         }
    
//     case followYellow_R:
//         {            
//             // num = communicate();
//             // if(num == -1){
//             //     currentState = findCOLOR_X; 
//             // } else currentState = (State) num; 
//             //looking for red
//             writeMessage("Follow yellow");
//             lcdShowStatus("Follow Yellow", "");
//             while(!wall_close()){
//                 getColor(color);
//                 // String left = "Left Color Sensor: " + (String)(color[1]);
//                 // String right = "Right Color Sensor: " + (String)(color[0]);
//                 // writeMessage(left);
//                 // writeMessage(right);
//                 if (color[0] == BLACK && color[1] == YELLOW){
//                     turnLeftSmall();
//                     moveSlow();
//                     delay(25);
//                 }
//                 else if (color[0] == YELLOW && color[1] == BLACK){
//                     turnRightSmall();
//                     moveSlow();
//                     delay(25);
//                 }
//                 else {
//                     moveSlow();
//                 }
//             }
//             motorsStop();
//             writeMessage("Hit yellow wall");
//             lcdShowStatus("", "Hit Wall");
//             //delay(5000);
//             moveBackward();
//             delay(200);
//             motorsStop();
//             turnL90();
//             delay(200);
//             currentState = finish;
//             //currentState = 1;

//             // leftMotorStop();
//             // setLSpeed(50);
//             // leftMotorBackward();
//             // lcdShowStatus("Find Color X", "Backing up");
//             break;
//         }
//     case findYellow_B:
//         {
//             num = communicate();
//             if(num == -1){
//                 currentState = findYellow_B; 
//             } else currentState = (State) num; 
//             lcdShowStatus("Find Yellow", "");
//             getColor(color);
//             while(color[0] != YELLOW || color[1] != YELLOW){
//                 moveSlow();
//                 getColor(color);
//                 // String left = "Left Color Sensor: " + (String)(color[1]);
//                 // String right = "Right Color Sensor: " + (String)(color[0]);
//                 // writeMessage(left);
//                 // writeMessage(right);
//                 //writeMessage((String)ir_read());
//                 //lcdShowStatus("firstWALL", "Moving to wall");
//             }
//             motorsStop();
//             delay(500);
//             writeMessage("Hit yellow strip.");
//             lcdShowStatus("","Hit Yellow");
//             //Serial.println(getMessage(readMessage()));
//             // moveBackward();
//             // delay(200);
//             // motorsStop();
//             turnR90();
//             delay(200);
//             currentState = followYellow_B;
//             break;
//         }

//     case followYellow_B:
//         {            
//             // num = communicate();
//             // if(num == -1){
//             //     currentState = findCOLOR_X; 
//             // } else currentState = (State) num; 
//             lcdShowStatus("Follow Yellow", "");
//             while(!wall_close()){
//                 getColor(color);
//                 // String left = "Left Color Sensor: " + (String)(color[1]);
//                 // String right = "Right Color Sensor: " + (String)(color[0]);
//                 // writeMessage(left);
//                 // writeMessage(right);
//                 if (color[0] == BLACK && color[1] == YELLOW){
//                     turnLeftSmall();
//                     moveSlow();
//                     delay(25);
//                 }
//                 else if (color[0] == YELLOW && color[1] == BLACK){
//                     turnRightSmall();
//                     moveSlow();
//                     delay(25);
//                 }
//                 else {
//                     moveSlow();
//                 }
//             }
//             motorsStop();
//             writeMessage("Hit yellow wall");
//             delay(5000);
//             moveBackward();
//             delay(100);
//             motorsStop();
//             turnR90();
//             delay(200);
//             currentState = finish;
//             //currentState = 1;
//             // leftMotorStop();
//             // setLSpeed(50);
//             // leftMotorBackward();
//             // lcdShowStatus("Find Color X", "Backing up");
//             break;
//         }
//     case finish:{
//         while(!wall_close()){
//             moveForward();
//         }
//         motorsStop();
//         lcdShowStatus("Finished", "Task complete");
//         writeMessage("Finished all tasks.");
//         currentState = idle;
//         break;
//     }     
//     case idle:
//     {
//         num = communicate();
//         if(num == -1){
//             currentState = idle; 
//         } else currentState = (State) num; 
//         motorsStop();
//         lcdShowStatus("Idle", "Waiting...");
//         break;
//     }
//     default:
//         currentState = idle;
//         break;
//     }
// }

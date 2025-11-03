#include "color.h"

int   a_lane[4][3] = {0};   // creates/stores average values for each LED in each condition. COLOR SENSOR 1
int   a_mag[4];             // creates the vector magnitudes between measured values and each average condition. COLOR SENSOR 1
int   b_lane[4][3] = {0};   // creates/stores average values for each LED in each condition. COLOR SENSOR 2
int   b_mag[4];
int   a_bestLane;             // returned value for most likely lane
int   a_bestValue;            // stores lowest magnitude for 'for' loop
int   b_bestLane;             // returned value for most likely lane
int   b_bestValue;            // stores lowest magnitude for 'for' loop

void setUpColorPins() {
    //setup Color Pins
    pinMode(11, OUTPUT); // red LED
    pinMode(12, OUTPUT); // blue LED
    pinMode(13, OUTPUT); // photocell, gives power for voltage divider

    digitalWrite(13, HIGH);

    Serial.print("black lane Average Calculation in: ");
    avg(a_lane[0], b_lane[0]);

    Serial.print("red lane Average Calculation in: ");
    avg(a_lane[1], b_lane[1]);

    Serial.print("blue lane Average Calculation in: ");
    avg(a_lane[2], b_lane[2]);

    Serial.print("yellow lane Average Calculation in: ");
    avg(a_lane[3], b_lane[3]);

    digitalWrite(13, LOW);
    Serial.print("Sensor 1 values: ");
    for(int i = 0; i < 4; i++) {
        Serial.print("Lane ");
        Serial.print(i);
        Serial.print(": ");
        Serial.print(a_lane[i][0]);
        Serial.print(", ");
        Serial.print(a_lane[i][1]);
        Serial.print(", ");
        Serial.println(a_lane[i][2]);
    }
    Serial.print("Sensor 2 values: ");
    for(int i = 0; i < 4; i++) {
        Serial.print("Lane ");;
        Serial.print(i);
        Serial.print(": ");
        Serial.print(b_lane[i][0]);
        Serial.print(", ");
        Serial.print(b_lane[i][1]);
        Serial.print(", ");
        Serial.println(b_lane[i][2]);
    }
}

void getColor(int color[2]) {
    int a_ambient;
    int a_red;
    int a_blue; // measured values COLOR SENSOR 1
    int b_ambient;
    int b_red;
    int b_blue; // measured values COLOR SENSOR 2

    digitalWrite(13, HIGH);
    delay(50);

    a_ambient = analogRead(A0);
    b_ambient = analogRead(A1);

    digitalWrite(11, HIGH);
    delay(50);
    a_red = analogRead(A0);
    b_red = analogRead(A1);
    digitalWrite(11, LOW);

    digitalWrite(12, HIGH);
    delay(50);
    a_blue = analogRead(A0);
    b_blue = analogRead(A1);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);

    // calculate distance metric for each lane
    for(int i = 0; i < 4; i++) {
        a_mag[i] = sqrt(
        pow((a_ambient - a_lane[i][0]), 2) +
        pow((a_red     - a_lane[i][1]), 2) +
        pow((a_blue    - a_lane[i][2]), 2)
        );

        b_mag[i] = sqrt(
        pow((b_ambient - b_lane[i][0]), 2) +
        pow((b_red     - b_lane[i][1]), 2) +
        pow((b_blue    - b_lane[i][2]), 2)
        );
        
    }


    // find smallest
    a_bestLane = 0; 
    a_bestValue = a_mag[0];
    b_bestLane = 0; 
    b_bestValue = b_mag[0];
    for (int i = 1; i < 4; i++) {
        if (a_mag[i] < a_bestValue) {
        a_bestValue = a_mag[i];
        a_bestLane = i;
        }
        if (b_mag[i] < b_bestValue) {
        b_bestValue = b_mag[i];
        b_bestLane = i;
        }
    }
    


    color[0] = a_bestLane; // 0 = Black, 1 = Red, 2 = Blue, 3 = Yellow
    color[1] = b_bestLane;
    
}


void avg(int a_lane[3], int b_lane[3]) {
    a_lane[0] = a_lane[1] = a_lane[2] = 0; // clear before summing
    b_lane[0] = b_lane[1] = b_lane[2] = 0; // clear before summing

    // countdown
    for(int i = 5; i > 0; i--){
        Serial.print(i);
        Serial.print("...");
        delay(500);
    }
    Serial.println(" ");

    // take 10 samples
    for(int i = 0; i < 10; i++) {
        a_lane[0] += analogRead(A0);   // ambient
        b_lane[0] += analogRead(A1);

        digitalWrite(11, HIGH);     // red LED on
        delay(100);
        a_lane[1] += analogRead(A0);   // red
        b_lane[1] += analogRead(A1);
        digitalWrite(11, LOW);

        digitalWrite(12, HIGH);     // blue LED on
        delay(100);
        a_lane[2] += analogRead(A0);   // blue
        b_lane[2] += analogRead(A1);
        digitalWrite(12, LOW);
    }


    // average
    a_lane[0] /= 10;
    a_lane[1] /= 10;
    a_lane[2] /= 10;
    b_lane[0] /= 10;
    b_lane[1] /= 10;
    b_lane[2] /= 10;
}

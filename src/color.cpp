#include "color.h"

int   a_lane[4][3] = {0};   // creates/stores average values for each LED in each condition. COLOR SENSOR 1
int   mag[4];             // creates the vector magnitudes between measured values and each average condition. COLOR SENSOR 1
int   b_lane[4][3] = {0};   // creates/stores average values for each LED in each condition. COLOR SENSOR 2
int   bestLane;       // returned value for most likely lane
int   bestValue;          // stores lowest magnitude for 'for' loop

void setUpColorPins() {
    //setup Color Pins
    pinMode(11, OUTPUT); // red LED
    pinMode(12, OUTPUT); // blue LED
    pinMode(13, OUTPUT); // photocell, gives power for voltage divider

    digitalWrite(13, HIGH);

    Serial.print("black lane Average Calculation in: ");
    avg(a_lane[0], 1);
    avg(b_lane[0], 2);

    Serial.print("red lane Average Calculation in: ");
    avg(a_lane[1], 1);
    avg(b_lane[1], 2);

    Serial.print("blue lane Average Calculation in: ");
    avg(a_lane[2], 1);
    avg(b_lane[2], 2);

    Serial.print("yellow lane Average Calculation in: ");
    avg(a_lane[3], 1);
    avg(b_lane[3], 2);

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

int getColor(int sensor) {
    int ambient;
    int red;
    int blue; // measured values COLOR SENSOR 1

    if (sensor == 1) {
        digitalWrite(13, HIGH);
        delay(50);

        ambient = analogRead(A0);

        digitalWrite(11, HIGH);
        delay(50);
        red = analogRead(A0);
        digitalWrite(11, LOW);

        digitalWrite(12, HIGH);
        delay(50);
        blue = analogRead(A0);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);

        // calculate distance metric for each lane
        for(int i = 0; i < 4; i++) {
            mag[i] = sqrt(
            pow((ambient - a_lane[i][0]), 2) +
            pow((red     - a_lane[i][1]), 2) +
            pow((blue    - a_lane[i][2]), 2)
            );
        }

        // find smallest
        bestLane = 0; 
        bestValue = mag[0];
        for (int i = 1; i < 4; i++) {
            if (mag[i] < bestValue) {
            bestValue = mag[i];
            bestLane = i;
            }
        }

        return bestLane; // 0 = Black, 1 = Red, 2 = Blue, 3 = Yellow
     } else {
        digitalWrite(13, HIGH);
        delay(50);

        ambient = analogRead(A1);

        digitalWrite(11, HIGH);
        delay(50);
        red = analogRead(A1);
        digitalWrite(11, LOW);

        digitalWrite(12, HIGH);
        delay(50);
        blue = analogRead(A1);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);

        // calculate distance metric for each lane
        for(int i = 0; i < 4; i++) {
            mag[i] = sqrt(
            pow((ambient - b_lane[i][0]), 2) +
            pow((red     - b_lane[i][1]), 2) +
            pow((blue    - b_lane[i][2]), 2)
            );
        }

        // find smallest
        bestLane = 0; 
        bestValue = mag[0];
        for (int i = 1; i < 4; i++) {
            if (mag[i] < bestValue) {
            bestValue = mag[i];
            bestLane = i;
            }
        }

        return bestLane; // 0 = Black, 1 = Red, 2 = Blue, 3 = Yellow
    }
    
}


void avg(int avg[3], int sensor) {
    avg[0] = avg[1] = avg[2] = 0; // clear before summing

    // countdown
    for(int i = 5; i > 0; i--){
        Serial.print(i);
        Serial.print("...");
        delay(500);
    }
    Serial.println(" ");

    if(sensor == 1) {
        // take 10 samples
        for(int i = 0; i < 10; i++) {
            avg[0] += analogRead(A0);   // ambient

            digitalWrite(11, HIGH);     // red LED on
            delay(100);
            avg[1] += analogRead(A0);   // red
            digitalWrite(11, LOW);

            digitalWrite(12, HIGH);     // blue LED on
            delay(100);
            avg[2] += analogRead(A0);   // blue
            digitalWrite(12, LOW);
        } 
    } else if (sensor == 2) {
        // take 10 samples
        for(int i = 0; i < 10; i++) {
            avg[0] += analogRead(A1);   // ambient

            digitalWrite(11, HIGH);     // red LED on
            delay(50);
            avg[1] += analogRead(A1);   // red
            digitalWrite(11, LOW);

            digitalWrite(12, HIGH);     // blue LED on
            delay(50);
            avg[2] += analogRead(A1);   // blue
            digitalWrite(12, LOW);
        }
    };


    // average
    avg[0] /= 10;
    avg[1] /= 10;
    avg[2] /= 10;
}

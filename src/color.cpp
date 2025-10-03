#include "color.h"

void setUpColorPins() {


    pinMode(11, OUTPUT); // red LED
    pinMode(12, OUTPUT); // blue LED
    pinMode(13, OUTPUT); // photocell, gives power for voltage divider

    digitalWrite(13, HIGH);

    Serial.print("black lane Average Calculation in: ");
    avg(lane[0]);

    Serial.print("red lane Average Calculation in: ");
    avg(lane[1]);

    Serial.print("blue lane Average Calculation in: ");
    avg(lane[2]);

    Serial.print("yellow lane Average Calculation in: ");
    avg(lane[3]);

    digitalWrite(13, LOW);

}


int getColor() {

    digitalWrite(13, HIGH);
    delay(100);

    ambient = analogRead(A1);

    digitalWrite(11, HIGH);
    delay(100);
    red = analogRead(A1);
    digitalWrite(11, LOW);

    digitalWrite(12, HIGH);
    delay(100);
    blue = analogRead(A1);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);

    // calculate distance metric for each lane
    for(int i = 0; i < 4; i++) {
        mag[i] = sqrt(
        pow((ambient - lane[i][0]), 2) +
        pow((red     - lane[i][1]), 2) +
        pow((blue    - lane[i][2]), 2)
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


void avg(int avg[3]) {
    avg[0] = avg[1] = avg[2] = 0; // clear before summing

    // countdown
    for(int i = 5; i > 0; i--){
        Serial.print(i);
        Serial.print("...");
        delay(500);
    }
    Serial.println(" ");

    // take 10 samples
    for(int i = 0; i < 10; i++) {
        avg[0] += analogRead(A1);   // ambient

        digitalWrite(11, HIGH);     // red LED on
        delay(100);
        avg[1] += analogRead(A1);   // red
        digitalWrite(11, LOW);

        digitalWrite(12, HIGH);     // blue LED on
        delay(100);
        avg[2] += analogRead(A1);   // blue
        digitalWrite(12, LOW);
    }

    // average
    avg[0] /= 10;
    avg[1] /= 10;
    avg[2] /= 10;
}

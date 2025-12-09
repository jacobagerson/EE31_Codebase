#include "color.h"

float   a_lane[4] = {28.5, 25, 43, 20};   // creates/stores average values for each LED in each condition. COLOR SENSOR 1 black, red, blue, yellow
float   a_mag[4];             // creates the vector magnitudes between measured values and each average condition. COLOR SENSOR 1
float   b_lane[4] = {36.2, 34.0, 40, 31};   // creates/stores average values for each LED in each condition. COLOR SENSOR 2
float   b_mag[4];
int     a_bestLane;             // returned value for most likely lane
float   a_bestValue;            // stores lowest magnitude for 'for' loop
int     b_bestLane;             // returned value for most likely lane
float   b_bestValue;            // stores lowest magnitude for 'for' loop


void setUpColorPins() {
    pinMode(7, OUTPUT);     // red LED
    pinMode(12, OUTPUT);    // blue LED
    pinMode(13, OUTPUT);    // photocell power (if that's really how it's wired)

}

void getColor(int color[2]) {
    int a_amb, b_amb, a_red, b_red, a_blue, b_blue;

    // reads values below
    digitalWrite(13, HIGH); 
    delay(25);
    a_amb = analogRead(A0);
    b_amb = analogRead(A1);

    digitalWrite(7, HIGH); 
    delay(25);
    a_red = analogRead(A0) - a_amb;
    b_red = analogRead(A1) - b_amb;
    digitalWrite(7, LOW);

    digitalWrite(12, HIGH); 
    delay(25);
    a_blue = analogRead(A0) - a_amb;
    b_blue = analogRead(A1) - b_amb;
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);        

    // calculates the angles of the vector created by 
    // the sensor reads
    float a_angle = atan2f((float)a_blue, (float)a_red)*(180/PI);
    float b_angle = atan2f((float)b_blue, (float)b_red)*(180/PI);


    // takes the difference between teh measured angle
    // and the on on the calibration
    for (int i = 0; i < 4; i++) {
        a_mag[i] = fabs(a_angle - a_lane[i]);
        b_mag[i] = fabs(b_angle - b_lane[i]); 
    }

    // finds the minimal difference of angles
    a_bestLane = 0; a_bestValue = a_mag[0];
    b_bestLane = 0; b_bestValue = b_mag[0];
    for (int i = 1; i < 4; ++i) {
        if (a_mag[i] < a_bestValue) { a_bestValue = a_mag[i]; a_bestLane = i; }
        if (b_mag[i] < b_bestValue) { b_bestValue = b_mag[i]; b_bestLane = i; }
    }

    color[0] = a_bestLane; // 0=Black,1=Red,2=Blue,3=Yellow
    color[1] = b_bestLane;
}

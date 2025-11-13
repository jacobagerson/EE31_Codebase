#include "color.h"

float   a_lane[4] = {0};   // creates/stores average values for each LED in each condition. COLOR SENSOR 1
float   a_mag[4];             // creates the vector magnitudes between measured values and each average condition. COLOR SENSOR 1
float   b_lane[4] = {0};   // creates/stores average values for each LED in each condition. COLOR SENSOR 2
float   b_mag[4];
int     a_bestLane;             // returned value for most likely lane
float   a_bestValue;            // stores lowest magnitude for 'for' loop
int     b_bestLane;             // returned value for most likely lane
float   b_bestValue;            // stores lowest magnitude for 'for' loop


void setUpColorPins() {
    pinMode(7, OUTPUT);     // red LED
    pinMode(12, OUTPUT);    // blue LED
    pinMode(13, OUTPUT);    // photocell power (if that's really how it's wired)

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
}



void getColor(int color[2]) {
    int a_amb, b_amb, a_red, b_red, a_blue, b_blue;

    // reads values below

    digitalWrite(13, HIGH); delay(50);
    a_amb = analogRead(A0);
    b_amb = analogRead(A1);

    digitalWrite(7, HIGH); delay(50);
    a_red = analogRead(A0) - a_amb;
    b_red = analogRead(A1) - b_amb;
    digitalWrite(7, LOW);

    digitalWrite(12, HIGH); delay(50);
    a_blue = analogRead(A0) - a_amb;
    b_blue = analogRead(A1) - b_amb;
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);

    // debugging print 
    Serial.print("Sensor A:"); Serial.print(a_amb); Serial.print(", "); Serial.print(a_red); Serial.print(", "); Serial.println(a_blue); 
    Serial.print("Sensor B:"); Serial.print(b_amb); Serial.print(", "); Serial.print(b_red); Serial.print(", "); Serial.println(b_blue); 
        

    // calculates the angles of the vector created by 
    // the sensor reads
    float a_angle = atan2f((float)a_blue, (float)a_red);
    float b_angle = atan2f((float)b_blue, (float)b_red);


    //debugging print output values in degrees
    Serial.print("Sensor A: "); Serial.println(a_angle*(180/PI));
    Serial.print("Sensor B: "); Serial.println(b_angle*(180/PI));


    // takes the difference between teh measured angle
    // and the on on the calibration
    for (int i = 0; i < 4; ++i) {
        a_mag[i] = fabsf(a_angle - a_lane[i]);
        b_mag[i] = fabsf(b_angle - b_lane[i]);
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


// calibration module
void avg(float &a_out, float &b_out) {
    int a_amb, b_amb, a_red, b_red, a_blue, b_blue;
    float a_sum = 0.0f, b_sum = 0.0f;

    for (int i = 5; i > 0; --i) { Serial.print(i); Serial.print("..."); delay(500); }
    Serial.println();

    for (int i = 0; i < 10; ++i) {
        // reads values
        a_amb = analogRead(A0);
        b_amb = analogRead(A1);

        digitalWrite(7, HIGH); delay(50);
        a_red  = analogRead(A0) - a_amb;
        b_red  = analogRead(A1) - b_amb;
        digitalWrite(7, LOW);

        digitalWrite(12, HIGH); delay(50);
        a_blue = analogRead(A0) - a_amb;
        b_blue = analogRead(A1) - b_amb;
        digitalWrite(12, LOW);

        // debugging print 
        Serial.print("Sensor A:"); Serial.print(a_amb); Serial.print(", "); Serial.print(a_red); Serial.print(", "); Serial.println(a_blue); 
        Serial.print("Sensor B:"); Serial.print(b_amb); Serial.print(", "); Serial.print(b_red); Serial.print(", "); Serial.println(b_blue); 
        
        // creates a running sum for each of the angles
        a_sum += atan2f((float)a_blue, (float)a_red);
        b_sum += atan2f((float)b_blue, (float)b_red);
    }

    // average and otuput
    a_out = a_sum / 10.0f;
    b_out = b_sum / 10.0f;
    //debugging print output values in degrees
    Serial.print("Sensor A: "); Serial.println(a_out*(180/PI));
    Serial.print("Sensor B: "); Serial.println(b_out*(180/PI));
}



// void setUpColorPins() {
//     //setup Color Pins
//     pinMode(7, OUTPUT); // red LED
//     pinMode(12, OUTPUT); // blue LED
//     pinMode(13, OUTPUT); // photocell, gives power for voltage divider

//     digitalWrite(13, HIGH);

//     Serial.print("black lane Average Calculation in: ");
//     avg(a_lane[0], b_lane[0]);

//     Serial.print("red lane Average Calculation in: ");
//     avg(a_lane[1], b_lane[1]);

//     Serial.print("blue lane Average Calculation in: ");
//     avg(a_lane[2], b_lane[2]);

//     Serial.print("yellow lane Average Calculation in: ");
//     avg(a_lane[3], b_lane[3]);

//     digitalWrite(13, LOW);
//     Serial.print("Sensor 1 values: ");
//     for(int i = 0; i < 4; i++) {
//         Serial.print("Lane ");
//         Serial.print(i);
//         Serial.print(": ");
//         Serial.print(a_lane[i][0]);
//         Serial.print(", ");
//         Serial.print(a_lane[i][1]);
//         Serial.print(", ");
//         Serial.println(a_lane[i][2]);
//     }
//     Serial.print("Sensor 2 values: ");
//     for(int i = 0; i < 4; i++) {
//         Serial.print("Lane ");;
//         Serial.print(i);
//         Serial.print(": ");
//         Serial.print(b_lane[i][0]);
//         Serial.print(", ");
//         Serial.print(b_lane[i][1]);
//         Serial.print(", ");
//         Serial.println(b_lane[i][2]);
//     }
// }

// void getColor(int color[2]) {
//     int a_ambient;
//     int a_red;
//     int a_blue; // measured values COLOR SENSOR 1
//     int b_ambient;
//     int b_red;
//     int b_blue; // measured values COLOR SENSOR 2

//     digitalWrite(13, HIGH);
//     delay(50);

//     a_ambient = analogRead(A0);
//     b_ambient = analogRead(A1);

//     digitalWrite(7, HIGH);
//     delay(50);
//     a_red = analogRead(A0);
//     b_red = analogRead(A1);
//     digitalWrite(7, LOW);

//     digitalWrite(12, HIGH);
//     delay(50);
//     a_blue = analogRead(A0);
//     b_blue = analogRead(A1);
//     digitalWrite(12, LOW);
//     digitalWrite(13, LOW);

//     // calculate distance metric for each lane
//     for(int i = 0; i < 4; i++) {
//         a_mag[i] = sqrt(
//         pow((a_ambient - a_lane[i][0]), 2) +
//         pow((a_red     - a_lane[i][1]), 2) +
//         pow((a_blue    - a_lane[i][2]), 2)
//         );

//         b_mag[i] = sqrt(
//         pow((b_ambient - b_lane[i][0]), 2) +
//         pow((b_red     - b_lane[i][1]), 2) +
//         pow((b_blue    - b_lane[i][2]), 2)
//         );
        
//     }


//     // find smallest
//     a_bestLane = 0; 
//     a_bestValue = a_mag[0];
//     b_bestLane = 0; 
//     b_bestValue = b_mag[0];
//     for (int i = 1; i < 4; i++) {
//         if (a_mag[i] < a_bestValue) {
//         a_bestValue = a_mag[i];
//         a_bestLane = i;
//         }
//         if (b_mag[i] < b_bestValue) {
//         b_bestValue = b_mag[i];
//         b_bestLane = i;
//         }
//     }
    


//     color[0] = a_bestLane; // 0 = Black, 1 = Red, 2 = Blue, 3 = Yellow
//     color[1] = b_bestLane;
    
// }


// void avg(int a_lane[3], int b_lane[3]) {
//     a_lane[0] = a_lane[1] = a_lane[2] = 0; // clear before summing
//     b_lane[0] = b_lane[1] = b_lane[2] = 0; // clear before summing

//     // countdown
//     for(int i = 5; i > 0; i--){
//         Serial.print(i);
//         Serial.print("...");
//         delay(500);
//     }
//     Serial.println(" ");

//     // take 10 samples
//     for(int i = 0; i < 10; i++) {
//         a_lane[0] += analogRead(A0);   // ambient
//         b_lane[0] += analogRead(A1);

//         digitalWrite(7, HIGH);     // red LED on
//         delay(50);
//         a_lane[1] += analogRead(A0);   // red
//         b_lane[1] += analogRead(A1);
//         digitalWrite(7, LOW);

//         digitalWrite(12, HIGH);     // blue LED on
//         delay(50);
//         a_lane[2] += analogRead(A0);   // blue
//         b_lane[2] += analogRead(A1);
//         digitalWrite(12, LOW);
//     }


//     // average
//     a_lane[0] /= 10;
//     a_lane[1] /= 10;
//     a_lane[2] /= 10;
//     b_lane[0] /= 10;
//     b_lane[1] /= 10;
//     b_lane[2] /= 10;
// }


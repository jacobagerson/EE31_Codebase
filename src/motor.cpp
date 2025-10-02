#include <Arduino.h>
#include "motor.h"

void setupMotorPins() {

    //Left Motor
    pinMode(4, OUTPUT); // Enable pin (orange)
    pinMode(5, OUTPUT); //PWM pin (green)
    pinMode(6, OUTPUT); //Reference pin (green)

    //Right Motor
    pinMode(8, OUTPUT); // Enable pin (orange)
    pinMode(9, OUTPUT); //PWM pin (green)
    pinMode(10, OUTPUT); //Reference pin (green)
    
}

void leftMotorForward(int speed) { //Speed 0-255
    digitalWrite(4, HIGH); //Set enable high
    digitalWrite(6, LOW); //Set reference low
    analogWrite(5, speed);

}

void rightMotorForward(int speed) { //Speed 0-255
    digitalWrite(8, HIGH); //Set enable high
    digitalWrite(10, LOW); //Set reference low
    analogWrite(9, speed); //Set speed
}

void leftMotorBackward(int speed) { //Speed 0-255
    digitalWrite(4, HIGH); //Set enable high
    digitalWrite(6, HIGH); //Set reference high
    analogWrite(5, speed); //Set speed
}

void rightMotorBackward(int speed) { //Speed 0-255
    digitalWrite(8, HIGH); //Set enable high
    digitalWrite(10, HIGH); //Set reference high
    analogWrite(9, speed); //Set speed
}

void leftMotorStop() {
    digitalWrite(4, LOW); //Set enable low
    analogWrite(5, 0); //Set speed to 0
}

void rightMotorStop() {
    digitalWrite(8, LOW); //Set enable low
    analogWrite(9, 0); //Set speed to 0
}

void motorsStop() {
    leftMotorStop();
    rightMotorStop();
}


 
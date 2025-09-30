#include <Arduino.h>
#include "motor.h"

uint8_t l_speed; 
uint8_t r_speed; 

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

void leftMotorForward() { //Speed 0-255
    digitalWrite(4, HIGH); //Set enable high
    digitalWrite(6, LOW); //Set reference low
    analogWrite(5, l_speed);
}

void rightMotorForward() { //Speed 0-255
    digitalWrite(8, HIGH); //Set enable high
    digitalWrite(10, LOW); //Set reference low
    analogWrite(9, r_speed); //Set speed
}

void leftMotorBackward() { //Speed 0-255
    digitalWrite(4, HIGH); //Set enable high
    digitalWrite(6, HIGH); //Set reference high
    analogWrite(5, l_speed); //Set speed
}

void rightMotorBackward() { //Speed 0-255
    digitalWrite(8, HIGH); //Set enable high
    digitalWrite(10, HIGH); //Set reference high
    analogWrite(9, r_speed); //Set speed
}

void leftMotorStop() {
    setLSpeed(0);
    digitalWrite(4, LOW); //Set enable low
    analogWrite(5, l_speed); //Set speed to 0
}

void rightMotorStop() {
    setRSpeed(0);
    digitalWrite(8, LOW); //Set enable low
    analogWrite(9, r_speed); //Set speed to 0
}

void motorsStop() {
    leftMotorStop();
    rightMotorStop();
}

void setLSpeed(uint8_t speed){
    l_speed = speed; 
}

void setRSpeed(uint8_t speed){
    r_speed = speed; 
}

//line following
 
//speed = (Vl + Vr) / 2
//doing discrete sampling instead of continuous since we can only sample at a limited rate
//color sensors on both sides of the chassey, width = width of channel

void correctLine(int lColor, int rColor){


}


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
    analogWrite(5, 150);
}

void leftMotorBackward() { //Speed 0-255
    digitalWrite(4, HIGH); //Set enable high
    digitalWrite(6, HIGH); //Set reference high
    analogWrite(5, 255 - 150); //Set speed
}

void rightMotorForward() { //Speed 0-255
    digitalWrite(8, HIGH); //Set enable high
    digitalWrite(10, LOW); //Set reference low
    analogWrite(9, 150); //Set speed
}

void rightMotorBackward() { //Speed 0-255
    digitalWrite(8, HIGH); //Set enable high
    digitalWrite(10, HIGH); //Set reference high
    analogWrite(9, 255 - 150); //Set speed
}

void leftMotorStop() {
    setLSpeed(0);
    digitalWrite(4, LOW); //Set enable low
    analogWrite(5, 0); //Set speed to 0
}

void rightMotorStop() {
    setRSpeed(0);
    digitalWrite(8, LOW); //Set enable low
    analogWrite(9, 0); //Set speed to 0
}

void motorsStop() {
    leftMotorStop();
    rightMotorStop();
}

void moveForward(){
    //left forward
    digitalWrite(4, HIGH); //Set enable high
    digitalWrite(6, LOW); //Set reference low
    analogWrite(5, 150);

    //right forward
    digitalWrite(8, HIGH); //Set enable high
    digitalWrite(10, LOW); //Set reference low
    analogWrite(9, 150); //Set speed
}

void moveBackward(){
    //left backward
    digitalWrite(4, HIGH); //Set enable high
    digitalWrite(6, HIGH); //Set reference high
    analogWrite(5, 255 - 150); //Set speed

    //right backward
    digitalWrite(8, HIGH); //Set enable high
    digitalWrite(10, HIGH); //Set reference high
    analogWrite(9, 255 - 150); //Set speed
}

void setLSpeed(uint8_t speed){
    l_speed = speed; 
}

void setRSpeed(uint8_t speed){
    r_speed = speed; 
}

void setSpeed(uint8_t speed){
    r_speed = speed; 
    l_speed = speed;
}

//color sensors on both sides of the chassey, width = little less than width of channel

void correctLine(int lColor, int rColor){
    //color values = ???
    //if L is on black, turn bot right until not on black
    // Turn L speed up, turn R speed down
    //if R is on black, turn bot left until not on black
    // Turn L speed down, turn R speed up


    //make these changes and then call color sensing function again
    //run this until neither on black
}

void turnL90(){
    motorsStop();
    setRSpeed(150);
    setLSpeed(100);
    rightMotorForward();
    leftMotorBackward();
    delay(550);
    motorsStop();
}

void turnR90(){
    motorsStop();
    setRSpeed(100);
    setLSpeed(150);
    rightMotorBackward();
    leftMotorForward();
    delay(550);
    motorsStop();
}

void turn180(){
    motorsStop();
    setRSpeed(150);
    setLSpeed(150);
    rightMotorBackward();
    leftMotorForward();
    delay(1100);
    motorsStop();
}
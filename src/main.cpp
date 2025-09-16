#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  digitalWrite(4, HIGH); //Set enable high
  digitalWrite(6, LOW);
  analogWrite(5, 260);
}

void loop() {
  // put your main code here, to run repeatedly:
}

#include <Arduino.h>

typedef enum { 
  START, 
  firstWALL,
  findCOLOR_X,
  laneFOLLOW_X,
  findCOLOR_Y,
  laneFOLLOW_Y,
  findSTART 
} State;

State currentState = START;



void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  digitalWrite(4, HIGH); //Set enable high
  digitalWrite(6, LOW);
  analogWrite(5, 250);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (currentState){
  case START:
    
    break;
  
  case firstWALL:

    break;

  case findCOLOR_X:

    break;

  case laneFOLLOW_X:

    break;

  case findCOLOR_Y:

    break;
  
  case laneFOLLOW_Y:

    break;

  case findSTART:

    break;

  default:
    currentState = START;
    break;
  }

}

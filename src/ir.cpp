#include "ir.h"

volatile bool irTriggered = false;

float ir_read() {
   return analogRead(A0);
}

// ISR
void irISR() {
   irTriggered = true;
}

void setupIRInterrupt(int pin) {
   pinMode(pin, INPUT);
   attachInterrupt(digitalPinToInterrupt(pin), irISR, RISING);
}

bool checkIrTriggered() {
   if (irTriggered) {
      irTriggered = false; // reset
      return true;
   }
   return false;
}

// int ir_proximity(float ir_value) {
//    if (ir_value > 700) {
//      return 1; // Object is close
//    } else {
//      return 0; // No object detected
//    }
// }


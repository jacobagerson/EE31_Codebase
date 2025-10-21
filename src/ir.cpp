#include "ir.h"

volatile bool irTriggered = false;

float ir_read() {
   return analogRead(A0); 
}

// ISR
void irISR() {
   irTriggered = true;
}

bool wall_close() {
    // Serial.print("read value = ");
    // Serial.println(ir_read);
    float check_distance = analogRead(A0);
    if (check_distance > 750) { //750 or closer, something is close to our bot
        delay(10);
        return true;
    } else {
        return false;
    }
}

// void setupIRInterrupt(int pin) {
//    pinMode(pin, INPUT);
//    attachInterrupt(digitalPinToInterrupt(pin), irISR, CHANGE);
// }

// bool checkIrTriggered() {
//    if (irTriggered) {
//       irTriggered = false; // reset
//       return true;
//    }
//    return false;
// }

// int ir_proximity(float ir_value) {
//    if (ir_value > 700) {
//      return 1; // Object is close
//    } else {
//      return 0; // No object detected
//    }
// }


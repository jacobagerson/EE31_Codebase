#include "ir.h"

volatile bool irTriggered = false;

float ir_read() {
   return analogRead(A3);
}

// ISR
void irISR() {
   irTriggered = true;
}

bool wall_close() {
    float check_distance = analogRead(A3);
    if (check_distance < 19) { //19 or less, something is close to our bot
        delay(10);
        return true;
    } else {
        return false;
    }
}
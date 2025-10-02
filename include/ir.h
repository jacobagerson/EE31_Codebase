#include <Arduino.h>

float ir_read();
void irISR();
bool wall_close(float ir_read);
// void setupIRInterrupt(int pin);
// bool checkIrTriggered();
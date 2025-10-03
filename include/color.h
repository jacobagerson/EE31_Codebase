#include <Arduino.h>

int   lane[4][3] = {0};   // creates/stores average values for each LED in each condition
int   mag[4];             // creates the vector magnitudes between measured values and each average condition
int   ambient, red, blue; // measured values
int   bestLane;       // returned value for most likely lane
int   bestValue;          // stores lowest magnitude for 'for' loop
void  setUpColorPins();   // set up pins + executes calibration
int   getColor();         // does the calculation
void  avg(int avg[3]);    // calculates averages

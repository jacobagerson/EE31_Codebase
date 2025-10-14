#include <Arduino.h>

 void  setUpColorPins();   // set up pins + executes calibration
 int   getColor();         // does the calculation
 void  avg(int avg[3]);    // calculates averages

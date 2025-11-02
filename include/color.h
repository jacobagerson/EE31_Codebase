#include <Arduino.h>

 void  setUpColorPins();   // set up pins + executes calibration
 int   getColor(int sensor);         // does the calculation
 void  avg(int avg[3], int sensor);    // calculates averages

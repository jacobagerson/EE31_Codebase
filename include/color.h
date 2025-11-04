#include <Arduino.h>

 void  setUpColorPins();   // set up pins + executes calibration
 void  getColor(int color[2]);         // does the calculation
 void  avg(int a_lane[3], int b_lane[3]);    // calculates averages

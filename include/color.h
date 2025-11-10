#include <Arduino.h>

 void  setUpColorPins();   // set up pins + executes calibration
 void  getColor(int color[2]);         // does the calculation
 void  avg(float &a_out, float &b_out);    // calculates averages

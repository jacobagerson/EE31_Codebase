#include "ir.h"

float ir_read() {
   float value = analogRead(A0);
   return value;
}

// int ir_proximity(float ir_value) {
//    if (ir_value > 700) {
//      return 1; // Object is close
//    } else {
//      return 0; // No object detected
//    }
// }


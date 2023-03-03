//main.cpp
// @rt.z

#include <Arduino.h>

enum States = {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL};
volatile States state;

//placeholder #includes for until the actual files come out
/*
#include "on_off.cpp"
#include "drive.cpp"
#include "charge.cpp"
*/

void setup() {
   state = OFF;
}

void loop() {
   switch (state) {
      case OFF:
         state = OFF();
      case ON:
         state = ON();
      case ON_READY:
         state = ON_READY();
      case DRIVE:
         state = DRIVE();
      case CHARGE_PRECHARGE:
         state = CHARGE_PRECHARGE();
      case CHARGE_CHARGING():
         state = CHARGE_CHARGING();
      case CHARGE_FULL():
         state = CHARGE_FULL();
   }
}

//main.cpp
//@rt.z, 0303

#include <Arduino.h>

enum States = {ERROR, OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL};
volatile States state;

//includes commended out until the actual files are ready
#include "on.cpp"
#include "off.cpp"
#include "on_ready.cpp"
//#include "FULL.cpp"
//#include "PRECHARGE.cpp"
//#include "CHARGING.cpp"

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
      case CHARGE_CHARGING:
         state = CHARGE_CHARGING();
      case CHARGE_FULL:
         state = CHARGE_FULL();
   }
}

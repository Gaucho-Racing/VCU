//main.cpp
//@rt.z, 0303

#include "main.h"

volatile States state;

#include "stubs.h"
I_no_can_speak_flex car(true);


void setup() {
   state = OFF;
}

void loop() {
   switch (state) {
      case OFF:
         state = off(car);
         break;
      case ON:
         state = on(car);
         break;
      case ON_READY:
         state = on_ready(car);
         break;
      case DRIVE:
         state = drive(car);
         break;
      case CHARGE_PRECHARGE:
         state = charge_precharge(car);
         break;
      case CHARGE_CHARGING:
         state = charge_charging(car);
         break;
      case CHARGE_FULL:
         state = charge_full(car);
         break;
   }
}

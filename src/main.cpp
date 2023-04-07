//main.cpp
// @rt.z

#include <Arduino.h>
#include <imxrt.h>
#include "string"
#include "main.h"

volatile States state;

#include "stubs.h"

// #include "stubs.cpp"

void setup() {
   state = OFF;
}

I_no_can_speak_flex car(true);

void loop() {
   switch (state) {
      case OFF:
         state = off());
         break;
      case ON:
         state = on();
         break;
      case ON_READY:
         state = on_ready();
         break;
      case DRIVE:
         state = drive(car*);
         break;
      case CHARGE_PRECHARGE:
         state = charge_precharge();
         break;
      case CHARGE_CHARGING:
         state = charge_charging();
         break;
      case CHARGE_FULL:
         state = charge_full();
         break;
      case ERROR:
         state = off(); // TEMPORARY
         break;
   }
}

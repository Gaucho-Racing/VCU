//stubs.cpp
// @rt.z
// a file full of stubs to test whether or not the main function will build.
// thanks, @Th3will

#include "stubs.h"

/*
States off(I_no_can_speak_flex &car) {
   Serial.println("0");
   return ON;
}

States on(I_no_can_speak_flex &car) {
   Serial.println("1");
   return ON_READY;
}

States on_ready(I_no_can_speak_flex &car) {
   Serial.println("2");
   return DRIVE;
}
*/

States drive(I_no_can_speak_flex &car) {
   Serial.println("3");
   return CHARGE_PRECHARGE;
}

States charge_precharge(I_no_can_speak_flex &car) {
   Serial.println("4");
   return CHARGE_CHARGING;
}

States charge_charging(I_no_can_speak_flex &car) {
   Serial.println("5");
   return CHARGE_FULL;
}

States charge_full(I_no_can_speak_flex &car) {
   Serial.println("6");
   return OFF;
}

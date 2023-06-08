//on.cpp
// @nikunjparsar, @rt.z

#include "main.h"
#include "stubs.h"
#include "onOffUtility.h"

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on(I_no_can_speak_flex &car, Switchboard& s) {
   car.DTI.setDriveEnable(0);
   car.DTI.setRCurrent(0);
   int brightness_fact = 20;
   led.clear();
   led.setPixelColor(0, led.Color(0, 255/brightness_fact, 179/brightness_fact));
   led.setPixelColor(1, led.Color(0, 255/brightness_fact, 179/brightness_fact));
   led.setPixelColor(2, led.Color(0, 255/brightness_fact, 179/brightness_fact));
   led.show();

   if(!s.drive_enable) return OFF;

   bool rejectStartup = false;
   if (isRejectingStartup(car, s, false)) rejectStartup = true;
   if (s.drive_engage && !rejectStartup) {
     for(int i=0; i<4; i++) {
         led.setPixelColor(i, led.Color(255/brightness_fact, 255/brightness_fact, 255/brightness_fact));
         led.show();
         delay(250);
      }
      led.clear();
      led.show();
      if (criticalCheck(car)) return ERROR;
      warningCheck(car, true);  
      for(int i = 0; i< 4; i++) {
         digitalWrite(3, HIGH);
         led.clear();
         led.setPixelColor(0, led.Color(0, 255/brightness_fact, 13/brightness_fact));
         led.setPixelColor(1, led.Color(0, 255/brightness_fact, 13/brightness_fact));
         led.setPixelColor(2, led.Color(0, 255/brightness_fact, 13/brightness_fact));
         led.show();
         delay(150);
         led.clear();
         led.show();
         delay(150);
         if(!s.drive_enable) return OFF;
      }
      led.clear();
      led.show();
      digitalWrite(3, LOW);
      return ON_READY;
   } else if (s.drive_engage && rejectStartup) {
      isRejectingStartup(car, s);
   }
   if (!s.drive_engage && !isRejectingStartup(car, s, false)) rejectStartup = false;
   return ON;
   
   /*
   if(!systemsCheck(car)) { //if it returns zero, we move to ON_READY
      return ON_READY;
   } else { //else throw the interrupt
      //interrupt code goes here
      return OFF; //a stub
   }
   */
}

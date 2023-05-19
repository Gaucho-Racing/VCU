//on.cpp
// @rt.z

#include "main.h"
#include "stubs.h"
#include "onOffUtility.h"

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on(FakeCar &car, Switchboard& s) {
   car.DTI.setRCurrent(0);
   
   led.setPixelColor(0, led.Color(0, 255, 179));
   led.setPixelColor(1, led.Color(0, 255, 179));
   led.setPixelColor(2, led.Color(0, 255, 179));
   led.setPixelColor(3, led.Color(0, 255, 179));
   led.show();

   bool rejectStartup = false;
   if (isRejectingStartup(car, false)) rejectStartup = true;
   if (s.drive_engage && !rejectStartup) {
     for(int i=0; i<4; i++) {
         led.setPixelColor(i, led.Color(0, 0, 255));
         led.show();
         delay(100);
      }
      led.clear();
      led.show();
      if (criticalCheck(car)) return ERROR;
      warningCheck(car);  
      for(int i = 0; i< 4; i++) {
         digitalWrite(3, HIGH);
         led.clear();
         led.setPixelColor(0, led.Color(0, 255, 13));
         led.setPixelColor(1, led.Color(0, 255, 13));
         led.setPixelColor(2, led.Color(0, 255, 13));
         led.setPixelColor(3, led.Color(0, 255, 13));
         led.show();
         delay(150);
         led.setPixelColor(0, led.Color(0, 0, 0));
         led.setPixelColor(1, led.Color(0, 0, 0));
         led.setPixelColor(2, led.Color(0, 0, 0));
         led.setPixelColor(3, led.Color(0, 0, 0));
         led.show();
         delay(150);
         if(!s.drive_enable) return OFF;
      }
      led.clear();
      led.show();
      digitalWrite(3, LOW);
      return ON_READY;
   } else if (s.drive_engage && rejectStartup) {
      isRejectingStartup(car);
   }
   if (!s.drive_engage && !isRejectingStartup(car, false)) rejectStartup = false;
   if(!s.drive_enable) return OFF;
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

//on.cpp
// @rt.z

#include "main.h"
#include "onOffUtility.h"

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on(FakeCar &car, Switchboard& s) {
   // Serial.println("ON STATE");

   if(!s.drive_enable) return OFF;
   // car.DTI.setRCurrent(0);
   led.setPixelColor(0, led.Color(0, 255, 179));
   led.setPixelColor(1, led.Color(0, 255, 179));
   led.setPixelColor(2, led.Color(0, 255, 179));
   led.setPixelColor(3, led.Color(0, 255, 179));
   led.show();

  

   //beeper: 5V, 0.5 amps to some pin for 1 second.
   if(s.drive_engage){
      // if (isRejectingStartup(car)) return OFF;
      // if (criticalCheck(car)) return ERROR;
      // warningCheck(car);
      for(int i=0; i<4; i++) {
         led.setPixelColor(i, led.Color(0, 0, 255));
         led.show();
         delay(500);
      }
      led.clear();
      led.show();
      led.clear();
      for(int i = 0; i< 4; i++){
         led.setPixelColor(0, led.Color(0, 255, 13));
         led.setPixelColor(1, led.Color(0, 255, 13));
         led.setPixelColor(2, led.Color(0, 255, 13));
         led.setPixelColor(3, led.Color(0, 255, 13));
         led.show();
         delay(100);
         led.setPixelColor(0, led.Color(0, 0, 0));
         led.setPixelColor(1, led.Color(0, 0, 0));
         led.setPixelColor(2, led.Color(0, 0, 0));
         led.setPixelColor(3, led.Color(0, 0, 0));
         led.show();
         delay(100);
      }
      led.clear();
      led.show();
      return ON_READY;
   }else{
      return ON;
   }
   

   /*
   if(!systemsCheck(car)) { //if it returns zero, we move to ON_READY
      return ON_READY;
   } else { //else throw the interrupt
      //interrupt code goes here
      return OFF; //a stub
   }
   */
}

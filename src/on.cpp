//on.cpp
// @rt.z

#include "main.h"
#include "stubs.h"
#include "onOffUtility.h"

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on(I_no_can_speak_flex &car) {
   car.DTI.setRCurrent(0);
   bool rejectStartup = false;
   if (isRejectingStartup(car, false)) rejectStartup = true;
   if (driveEngaged(car) && !rejectStartup) {   
      if (criticalCheck(car)) return ERROR;
      warningCheck(car);  
      unsigned long time70 = 0;
      while (millis() - time70 > 1500) {
         digitalWrite(3, HIGH);
         on_ready(car);
      }
      digitalWrite(3, LOW);
      return ON_READY;
   } else if (driveEngaged(car) && rejectStartup) {
      isRejectingStartup(car);
   }
   if (!driveEngaged(car) && !isRejectingStartup(car, false)) rejectStartup = false;
   if (!onPressed(car)) return OFF;
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

//on.cpp
// @rt.z

#include "main.h"
#include "onOffUtility.h"

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on(I_no_can_speak_flex &car) {
   car.DTI.setRCurrent(0);
   if (criticalCheck(car)) return ERROR;
   warningCheck(car);

   //beeper: 5V, 0.5 amps to some pin for 1 second.
   return ON_READY;

   /*
   if(!systemsCheck(car)) { //if it returns zero, we move to ON_READY
      return ON_READY;
   } else { //else throw the interrupt
      //interrupt code goes here
      return OFF; //a stub
   }
   */
}

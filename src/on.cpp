//on.cpp

#include "main.h"
#include "onOffUtility.h"

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on(I_no_can_speak_flex &car) {
   car.DTI.setRCurrent(0);
   std::vector<int> systems_check = systemsCheck(car);
   bool error_detected = 0;
   for (int code : systems_check) {
      if (code >= 100) error_detected = 1;
      //that can command to send it over…
   }
   if (error_detected) return ERROR;
   else return ON_READY;

   /*
   if(!systemsCheck(car)) { //if it returns zero, we move to ON_READY
      return ON_READY;
   } else { //else throw the interrupt
      //interrupt code goes here
      return OFF; //a stub
   }
   */
}

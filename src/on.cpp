//on.cpp

#include "main.h"
#include "error.h"
#include "onOffUtility.h"

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on(I_no_can_speak_flex &car) {
   car.DTI.setRCurrent(0);
   std::vector<int> systems_check = startupCheck(car);
   std::vector<int> error_codes;
   for (int code : systems_check) {
      if (code >= 100) error_codes.push_back(code);
   }
   if (!error_codes.empty()) {
      for (int code : error_codes) {
         sendDashError(code);
         return sendToError(ON, &hasStartupCrits);
      }
   }

   //beeper: 5V, 0.5 amps to some pin for 1 second.
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

//on.cpp

#include "main.h"
#include "onOffUtility.h"

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on(I_no_can_speak_flex &car) {
   car.DTI.setRCurrent(0);
   bool* systems_check = systemsCheck(car);
   for (int i = 0; i < 100; i++) {
      if (systems_check[i]) {
         //throw interrupt
         return OFF; //stub
      }
   }
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

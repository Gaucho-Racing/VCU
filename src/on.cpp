//on.cpp
#include <iostream>
//relevant files
#include "onOffUtility.cpp"

using namespace std;

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States ON() {
   setRCurrent(0);
   if(!systemsCheck()) { //if it returns zero, we move to ON_READY
      return ON_READY;
   } else { //else throw the interrupt
      //interrupt code goes here
   }
}

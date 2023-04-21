//off.cpp
#include "onOffUtility.h"
//#include file with the enums
#include "main.h"

// Starts at this state when the car is unlocked
States off(I_no_can_speak_flex &car) {
    while(1) {
        // Start power to necessary things 
        // Get whether on or off (some function) (see below if statement) 
        if(onPressed(car)){
            return ON;
        }
        if(car.charger.getCurrent() > 0){
            return CHARGE_PRECHARGE;
        } 
        
        //currentState = OFF; //not needed?
        // No default return value ?
    }
}

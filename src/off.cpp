//off.cpp
// @yarwinliu, @rt.z

//#include file with the enums
#include "main.h"
#include "onOffUtility.h"

// Starts at this state when the car is unlocked
States off(I_no_can_speak_flex &car) {
    car.DTI.setRCurrent(0);
    if (onPressed(car)) {
        return ON;
    }
    return OFF;

    /*
    if(car.BMS.getCurrent() > 0) {
        return CHARGE_PRECHARGE;
    } 
    */
}

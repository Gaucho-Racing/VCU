//error.cpp
// @Th3Will

#include "main.h"
#include "error.h"
#include "constants.h"
//#include <iostream>

States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void), Switchboard& s) {
    car.DTI.setDriveEnable(0);
    car.DTI.setRCurrent(0);
    led.clear();
    led.setPixelColor(0, led.Color(0, 0, 255));
    led.show();
    if(!s.drive_enable){
        car.DTI.setDriveEnable(0);
        return OFF;
    }
    //CHECK old: erCheck(), new: *(erCheck)() 
    if((*erCheck)()){
        return ERROR;
    } else {
        return prevStates;
    }
}

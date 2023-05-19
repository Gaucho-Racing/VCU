//error.cpp
// @Th3Will

#include "main.h"
#include "error.h"
#include "constants.h"
//#include <iostream>

States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void)) {
    car.DTI.setDriveEnable(0);
    car.DTI.setRCurrent(0);
    
    if(erCheck()){
        return ERROR;
    } else {
        car.DTI.setDriveEnable(1);
        return prevStates;
    }
}

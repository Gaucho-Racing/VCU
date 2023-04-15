#include "error.h"
States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void)){
    car.DTI.setDriveEnable(0);
    car.DTI.setCurrent(0);
    
    if(erCheck()){
        return ERROR;
    } else {
        return prevStates;
    }
}

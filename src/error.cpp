#include "error.h"
States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void)){
    car.DTI.setCurrent(0);
    car.DTI.setDriveEnable({0});
    //need to figure out what the previous state is
    //
    if(erCheck()){
        return ERROR;
    } else {
        return prevStates;
    }
}

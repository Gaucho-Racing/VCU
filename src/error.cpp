//error.cpp
// @Th3Will

#include "main.h"
#include "error.h"
#include "constants.h"
//#include <iostream>

States error(FakeCar &car, States prevStates, volatile bool (*erCheck)(void)) {
    car.DTI.setDriveEnable(0);
    car.DTI.setCurrent(0);
    
    //CHECK old: erCheck(), new: *(erCheck)() 
    if((*erCheck)()){
        return ERROR;
    } else {
        return prevStates;
    }
}

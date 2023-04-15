#include "error.h"
States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void)){
    
    if(erCheck()){
        return ERROR;
    } else {
        return prevStates;
    }
}

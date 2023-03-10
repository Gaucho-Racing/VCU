#include "Nodes.h"

//returns true if there is current running to the motor
bool onPressed(){ 
    if(getDCCurrent() > 0) return true;
    else return false;
}

bool systemsCheck(){
    //TODO - insert acutal code
    //make sure the data works
    //outputs error message depending on what the error is
    return false;
}

bool drive(){
    //TODO
    return false;
}


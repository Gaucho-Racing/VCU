//#include "Nodes.h"

//returns true if there is current running to the motor
bool onPressed(){ 
    if(getDCCurrent() > 0) return true;
    else return false;
}

bool systemsCheck(){
    //TODO - insert acutal code
    return false;
}


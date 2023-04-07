//this has a bunch of stuff that is basically used by everything hence the extern stuff

#ifndef STATES
#define STATES
#include "string"

enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL, FATAL_ERROR};
//need extern to modify across files apparently
struct carFailure {

    //dash
    volatile bool sendToDash;
    //message to send to dash
    volatile std::string errMess;
};
//sub-system declarations 
#endif
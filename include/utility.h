//this has a bunch of stuff that is basically used by everything hence the extern stuff

#ifndef STATES
#define STATES
#include "string"

//need extern to modify across files apparently
struct carFailure {

    //dash
    volatile bool sendToDash;
    //message to send to dash
    volatile std::string errMess;
};
//sub-system declarations 
#endif
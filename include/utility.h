//this has a bunch of stuff that is basically used by everything hence the extern stuff

#ifndef STATES
#define STATES
#include "Nodes.h"

enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL, FATAL_ERROR};
//need extern to modify across files apparently
extern volatile States currentState;

//sub-system declarations 
#endif
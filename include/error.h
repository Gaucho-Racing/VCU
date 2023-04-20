#ifndef ERROR_H
#define ERROR_H
#include "stubs.h"
//use this for interrupts to store currentState;
//handles the specified error
States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void));

#endif
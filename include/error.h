#ifndef ERROR_H
#define ERROR_H
#include "stubs.h"

//use this for interrupts to store currentState;
//handles the specified error

States sendToError(volatile States currentState, volatile bool (*erFunc)(void));

States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void));

//so it compiles!
void sendDashError(int code);

void TS_WARN_Check(I_no_can_speak_flex &car);

#endif
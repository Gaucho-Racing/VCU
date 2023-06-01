//error.h
// @Th3Will
#include "main.h"

#ifndef ERROR_H
#define ERROR_H

States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void), Switchboard& s);

#endif

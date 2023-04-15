// main.h
// @rt.z
// @yarwinliu, in the end i admit, you had the better idea

#ifndef MAIN
#define MAIN

#include <Arduino.h>
// #include "Nodes.h" (because its already included in I_no_can_speak_flex.h)
#include "I_no_can_speak_flex.h"

enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL, ERROR};

#endif

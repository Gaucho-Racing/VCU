#ifndef STATES
#define STATES

enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL, FATAL_ERROR};
//need extern to modify across files apparently
extern volatile States state;

#endif
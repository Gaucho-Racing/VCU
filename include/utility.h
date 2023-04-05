//this has a bunch of stuff that is basically used by everything hence the extern stuff

#ifndef STATES
#define STATES
#include "string"

enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL, FATAL_ERROR};
//need extern to modify across files apparently
struct carFailure {
    volatile bool battery_temp_high = false;
    volatile bool battery_temp_low = false;
    volatile bool no_current = false;
    volatile bool accelerator_and_brakes = false;
    volatile bool hard_brake = false;
    volatile bool unresponsive_throttle = false;
    volatile bool motor_temp_low = false;
    volatile bool no_can_signal = false;
    volatile bool current_too_high = false;
    volatile bool system_error = false;
    volatile bool insulation_fault = false;
    volatile bool car_crash = false;
    //dash
    volatile bool sendToDash;
    //message to send to dash
    volatile std::string errMess;
};
//sub-system declarations 
#endif
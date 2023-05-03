// main.h
// @rt.z
// @yarwinliu, in the end i admit, you had the better idea

#ifndef MAIN
#define MAIN

#include <Arduino.h>
#include <imxrt.h>
#include "I_no_can_speak_flex.h"
// #include "TESTBENCH/FakeCar.h"

enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL, ERROR};

States sendToError(volatile States currentState, volatile bool (*erFunc)(void));

volatile bool hasStartupCrits();
volatile bool batteryTempHigh();
volatile bool noCurrent();
volatile bool APPSBSPDViolation();
volatile bool hardBrake();
volatile bool accelUnresponsive();
volatile bool motorTempHigh();
volatile bool CANFailure();
volatile bool currentExceeds();
volatile bool systemError();
volatile bool IMDFault();
volatile bool GForceCrash();



#endif

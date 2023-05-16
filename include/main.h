// main.h
// @nikunjparasar
// @rt.z
// @yarwinliu

#ifndef MAIN
#define MAIN

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <imxrt.h>
#include "FakeCar.h"
#include <vector>

enum States {OFF, ON, ON_READY, DRIVE, ERROR, TESTING};
static vector<std::string> statesString = {"OFF", "ON", "ON_READY", "DRIVE", "ERROR", "TESTING"};

static Adafruit_NeoPixel led(4, 14, NEO_GBR);

static std::string getTextForEnum( int enumVal )
{
  return statesString[enumVal];
}

States sendToError(volatile States currentState, volatile bool (*erFunc)(void));

volatile bool hasStartupCrits();
volatile bool APPSBSPDViolation();
volatile bool hardBrake();
volatile bool accelUnresponsive();
volatile bool motorTempHigh();
volatile bool CANFailure();
volatile bool currentExceeds();
volatile bool GForceCrash();

struct Switchboard {
  int drive_enable;
  int drive_engage;
  int full_pwr;
  int traction_control;
};

#endif

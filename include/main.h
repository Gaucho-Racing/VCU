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
#include "I_no_can_speak_flex.h"
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

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
  int SWITCH_TEST_BRAKES;
  double ROTARY_TEST_ACCEL;

  unordered_map<double, std::pair<int, std::pair<int, int>>> COLOR_MAPPING = {};

  Switchboard(){
    for(int i = 0; i <= 1000; i++){
      double j = 0.001*i;
      COLOR_MAPPING[j] = {static_cast<int>(j*255), {0, static_cast<int>(255-j*255)}}; //{R,{G,B}}
    }
  }
};  




#endif

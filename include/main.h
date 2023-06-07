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

// DTI HV500 operating temps: -20C to 85C
// EMRAX 228HV WORKING TEMPS: The electric motor can operate in ambient
// temperatures between -40 to +60⁰C. The maximum
// motor temperature allowed as recorded by internal
// temperature sensor is 120⁰C
unordered_map<int, double> LIQUID_COOLING_FAN_CURVE = {
  {0, 0.0},
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 0},
    {6, 1.2},
    {7, 1.4},
    {8, 1.6},
    {9, 1.8},
    {10, 2.0},
    {11, 2.2},
    {12, 2.4},
    {13, 2.6},
    {14, 2.8},
    {15, 3.0},
    {16, 3.2},
    {17, 3.4},
    {18, 3.6},
    {19, 3.8},
    {20, 4.0},
    {21, 4.2},
    {22, 4.4},
    {23, 4.6},
    {24, 4.8},
    {25, 5.0},
    {26, 5.2},
    {27, 5.4},
    {28, 5.6},
    {29, 5.8},
    {30, 6.0},
    {31, 6.2},
    {32, 6.4},
    {33, 6.6},
    {34, 6.8},
    {35, 7.0},
    {36, 7.2},
    {37, 7.4},
    {38, 7.6},
    {39, 7.8},
    {40, 8.0},
    {41, 8.2},
    {42, 8.4},
    {43, 8.6},
    {44, 8.8},
    {45, 9.0},
    {46, 9.2},
    {47, 9.4},
    {48, 9.6},
    {49, 9.8},
    {50, 10.0},
    {51, 10.2},
    {52, 10.4},
    {53, 10.6},
    {54, 10.8},
    {55, 11.0},
    {56, 11.2},
    {57, 11.4},
    {58, 11.6},
    {59, 11.8},
    {60, 12.0}
};


#endif

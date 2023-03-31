#include <Arduino.h>
enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL};

//gonna overload interrupts from 
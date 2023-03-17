#include <Arduino.h>
#include "states.h"
//gonna overload interrupts from 


void interruptSetup();

//IRQ_GPI01_INT0 is used for HV line open
void IRQ_GPI01_INT0_Handler();
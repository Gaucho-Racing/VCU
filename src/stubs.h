// stubs.h
// @rt.z
// becuase platformio links all the files in src together at the end
// yes, rt.z is still learning
// will he someday stop? probably
// that was just a euphemism for that he will give up someday...

#ifndef STUBS
#define STUBS

#include "main.h"

States off();

States on();

States on_ready();

States drive();

States charge_precharge();

States charge_charging();

States charge_full();

#endif
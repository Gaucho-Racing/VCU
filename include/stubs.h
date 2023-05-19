// stubs.h
// @rt.z
// becuase platformio links all the files in src together at the end
// yes, rt.z is still learning
// will he someday stop? probably
// that was just a euphemism for that he will give up someday...

#ifndef STUBS
#define STUBS

#include "main.h"

States off(FakeCar &car, Switchboard& s);

States on(FakeCar &car,  Switchboard& s);

States on_ready(FakeCar &car,  Switchboard& s);

States drive(FakeCar &car,  Switchboard& s);


#endif

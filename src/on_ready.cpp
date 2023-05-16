// on_ready.cpp
// @yarwinliu, @rt.z

#include "main.h"
#include "onOffUtility.h"

States on_ready(FakeCar &car, Switchboard& s) {
    //motorOutput = 0;
    // car.DTI.setRCurrent(0);
    // if drive mode engaged
    if(s.drive_engage && s.drive_enable && car.pedals.getAPPS1() > 0) {
        led.clear();
        led.show();
        return DRIVE;
    }
    
    return ON_READY;
}

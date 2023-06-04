// on_ready.cpp
// @yarwinliu, @rt.z

#include "main.h"
#include "onOffUtility.h"

States on_ready(I_no_can_speak_flex &car, Switchboard& s) {
    //motorOutput = 0;
    car.DTI.setDriveEnable(1);
    car.DTI.setRCurrent(0);

    if(!s.drive_enable) return OFF;
    if(s.drive_enable && !s.drive_engage) return ON;

    // if drive mode engaged
    if((car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > 0.05) {
        led.clear();
        led.show();
        return DRIVE;
    }
    return ON_READY;
}

// on_ready.cpp
// @nikunjparasar, @yarwinliu, @rt.z

#include "main.h"
#include "onOffUtility.h"

States on_ready(I_no_can_speak_flex &car, Switchboard& s) {
    //motorOutput = 0;
    car.DTI.setDriveEnable(1);
    car.DTI.setRCurrent(0);
    int brightness_fact = 20;
    led.clear();
    led.setPixelColor(0, led.Color(255/brightness_fact, 0, 0));
    led.setPixelColor(1, led.Color(255/brightness_fact, 0, 0));
    led.setPixelColor(2, led.Color(255/brightness_fact, 0, 0));
    led.show();

    if(!s.drive_enable) return OFF;
    if(s.drive_enable && !s.drive_engage) return ON;

    // if drive mode engaged
    // if((car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > 0.05) {
    if(s.ACCEL_1 > 0.05 || s.ACCEL_2 > 0.05) {
        led.clear();
        led.show();
        return DRIVE;
    }
    return ON_READY;
}

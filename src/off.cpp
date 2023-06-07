//off.cpp
// @rt.z, @nikunjparasar

//#include file with the enums
#include "main.h"
#include "onOffUtility.h"

// Starts at this state when the car is unlocked
States off(I_no_can_speak_flex &car, Switchboard& s) {
    car.DTI.setDriveEnable(0);
    car.DTI.setRCurrent(0);
    
    led.clear();
    led.show();
    
    bool reject_on = false;
    if (s.drive_engage) reject_on = true;
    
    int brightness_fact = 50;

    if(s.drive_enable && !s.drive_engage && !reject_on) {
        for(int i = 0; i < 4; i++) {
            led.setPixelColor(i, led.Color(148/brightness_fact, 0, 247/brightness_fact));
            led.show();
            delay(250);
        }
        led.clear();
        led.setPixelColor(0, led.Color(66/brightness_fact, 247/brightness_fact, 0));
        led.setPixelColor(1, led.Color(66/brightness_fact, 247/brightness_fact, 0));
        led.setPixelColor(2, led.Color(66/brightness_fact, 247/brightness_fact, 0));
        led.setPixelColor(3, led.Color(66/brightness_fact, 247/brightness_fact, 0));
        led.show();
        delay(500);
        led.clear();
        led.show();
        return ON;
    }

    if (!s.drive_enable && !s.drive_engage) reject_on = false;

    return OFF;
}

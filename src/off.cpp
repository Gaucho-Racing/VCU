//#include file with the enums
#include "main.h"
#include "onOffUtility.h"



States off(FakeCar &car, Switchboard& s) {
    // Serial.println("OFF");
    
    
    if(s.drive_enable) {
        for(int i = 0; i < 4; i++){
            led.setPixelColor(i, led.Color(148, 0, 247));
            led.show();
            delay(500);
        }
        led.clear();
        led.setPixelColor(0, led.Color(66, 247, 0));
        led.setPixelColor(1, led.Color(66, 247, 0));
        led.setPixelColor(2, led.Color(66, 247, 0));
        led.setPixelColor(3, led.Color(66, 247, 0));
        led.show();
        delay(500);
        led.clear();
        led.show();
        return ON;
    }

    
    return OFF;
}

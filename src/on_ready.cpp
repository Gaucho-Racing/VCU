// on_ready.cpp
// @yarwinliu, @rt.z

#include "main.h"
#include "stubs.h"
#include "onOffUtility.h"

States on_ready(I_no_can_speak_flex &car) {
    //motorOutput = 0;
    // if drive mode engaged
    bool reject_drive = 0;
    if ((car.pedals.getBrakePressure1() < 50 || car.pedals.getBrakePressure2() < 50)) {
        reject_drive = 1;
    } 
    if (driveEngaged(car) && !reject_drive) {
        unsigned long time70 = 0;
        while (millis() - time70 > 1500) {
            digitalWrite(3, HIGH);
            drive(car);
            //time70 = millis();
        }
        digitalWrite(3, LOW);
        return DRIVE;     
    }
    if (!driveEngaged(car) && car.pedals.getBrakePressure1() > 50 && car.pedals.getBrakePressure2() < 50) {
        reject_drive = 0;
    }
    return ON_READY;
}

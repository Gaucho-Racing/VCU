// on_ready.cpp
// @yarwinliu, @rt.z

#include "main.h"
#include "onOffUtility.h"

States on_ready(I_no_can_speak_flex &car) {
    //motorOutput = 0;
    // if drive mode engaged
    car.DTI.setRCurrent(0);
    if((car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > 0.05) 
      return DRIVE;
    if (!driveEngaged(car)) return ON;
    if (!onPressed(car)) return OFF;
    return ON_READY;
}

// on_ready.cpp

#include "main.h"
#include "onOffUtility.h"

States on_ready(I_no_can_speak_flex &car) {
    while(1) {
         //motorOutput = 0;
         car.DTI.setRCurrent(0);
         // if drive mode engaged
         if(driveEngaged(car)) {
            return DRIVE;
         }
    }
}

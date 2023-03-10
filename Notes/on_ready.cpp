// on_ready.cpp
#include "Nodes.h"

States on_ready() {
    while(1) {
        // global variable motorOutput
        setCurrent(0); //to set motor output to 0
        // Get necessary data
        // if drive mode engaged
        if(drive()){
            return MOTOR_OFF;
        }
    }
}

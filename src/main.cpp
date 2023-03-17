#include <Arduino.h>
#include "Interrupts.h"
#include "states.h"
#include "Nodes.h"

Inverter inv(1);

void setup(){
    interruptSetup();
}
//whatever the inverter 
int min_expected = 0;
void loop(){
    //I don't actually know how to get if the high voltage line is tripped
    //so I'm gonna compare the Vin against the smallest value
    if(inv.getVoltIn() < min_expected){
        NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);
    }
}
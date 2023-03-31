#include "Interrupts.h"
#include "Nodes.h"
#include "states.h"

volatile States state;
void interruptSetup(){
    NVIC_ENABLE_IRQ(IRQ_GPIO1_INT0);
    attachInterruptVector(IRQ_GPIO1_INT0, &IRQ_GPI01_INT0_Handler);
}

//HV line open
void IRQ_GPI01_INT0_Handler(){
    state = FATAL_ERROR;
    //turn off, idk how
    //setCurrent(0);, currently unable to link to Node

}
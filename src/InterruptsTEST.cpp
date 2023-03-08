#include <stdint.h>
#include "imxrt.h"

// Define the interrupt priority level
#define MY_INTERRUPT_PRIORITY 0x80 // set to medium priority

// Define the interrupt number
#define MY_INTERRUPT_NUMBER 14 // set to a free interrupt number on the Teensy 4.1

int main()
{
    // Enable the interrupt
    NVIC_EnableIRQ((IRQn_Type)MY_INTERRUPT_NUMBER);

    // Set the interrupt priority level
    NVIC_SetPriority((IRQn_Type)MY_INTERRUPT_NUMBER, MY_INTERRUPT_PRIORITY);

    while (1)
    {
        // Trigger the software interrupt
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    }

    return 0;
}

// Interrupt service routine for the software interrupt
void __attribute__((interrupt("IRQ"))) my_interrupt_handler(void)
{
    // Handle the interrupt here
}

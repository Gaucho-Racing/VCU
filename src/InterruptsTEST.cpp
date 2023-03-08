// Proper syntax usage for arm cortex m7 microcontrollers
// Nikunj Parasar 03/08/2023

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


/*
Here's a breakdown of the code:

#include <stdint.h> and "stm32f7xx.h" include the necessary header files.
            USE imxrt.h INSTEAD OF stm32f7xx.h ABOVE

#define MY_INTERRUPT_PRIORITY 0x01 defines the interrupt priority level. In this example, we set it to the lowest priority (0x01).

#define MY_INTERRUPT_NUMBER 0x01 defines the interrupt number. In this example, we set it to 1.

NVIC_EnableIRQ((IRQn_Type)MY_INTERRUPT_NUMBER) enables the interrupt.

NVIC_SetPriority((IRQn_Type)MY_INTERRUPT_NUMBER, MY_INTERRUPT_PRIORITY) sets the interrupt priority level.

while (1) {...} triggers the software interrupt repeatedly in an infinite loop.

SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk triggers the software interrupt by setting the PendSV flag in the Interrupt Control and State Register (ICSR).

void __attribute__((interrupt("IRQ"))) my_interrupt_handler(void) is the interrupt service routine for the software interrupt. It handles the interrupt when it occurs.


*/
// code to test software interrupt handling on a teensy 4.1 microcontroller
// Nikunj Parasar

/*
Download the latest version of the CMSIS library from the ARM website: https://developer.arm.com/tools-and-software/embedded/cmsis/cmsis-download

Extract the contents of the downloaded ZIP file to a location on your computer.

In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library.

Select the ZIP file that you downloaded and extracted in step 1.

Restart the Arduino IDE.
*/

#include <Arduino.h>
#include <stdint.h>
#include "cmsis_os.h"
#include "core_cm7.h"

// Define the interrupt priority level
#define MY_INTERRUPT_PRIORITY 0x80 // set to medium priority

// Define the interrupt number
#define MY_INTERRUPT_NUMBER 14 // set to a free interrupt number on the Teensy 4.1

// Flag to indicate whether the interrupt has occurred
volatile bool interruptFlag = false;

// Interrupt service routine for the software interrupt
void __attribute__((interrupt("IRQ"))) my_interrupt_handler(void)
{
    // Set the interrupt flag
    interruptFlag = true;
}

void setup()
{
    // Enable the interrupt
    NVIC_EnableIRQ((IRQn_Type)MY_INTERRUPT_NUMBER);

    // Set the interrupt priority level
    NVIC_SetPriority((IRQn_Type)MY_INTERRUPT_NUMBER, MY_INTERRUPT_PRIORITY);
}

void loop()
{
    // Trigger the software interrupt
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

    // Wait for the interrupt to occur
    while (!interruptFlag);

    // Reset the interrupt flag
    interruptFlag = false;

    // Do something in response to the interrupt
    Serial.println("Interrupt occurred!");
    delay(1000);
}

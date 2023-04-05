#include <Arduino.h>
#include <imxrt.h>
#include "utility.h"
#include "I_no_can_speak_flex.h"
#include "string"


// Variables to hold input states

I_no_can_speak_flex car(true);
volatile carFailure errObserver;

// Interrupt handler for battery temperature high
void IRQ_GPI01_INT0_Handler() {
  
}

// Interrupt handler for battery temperature low
void IRQ_GPI01_INT1_Handler() {
  
}

// Interrupt handler for no current
void IRQ_GPI02_INT0_Handler() {
  
}

// Interrupt handler for accelerator and brakes
void IRQ_GPI02_INT1_Handler() {
  
}

// Interrupt handler for hard brake
void IRQ_GPI03_INT0_Handler() {
  
}

// Interrupt handler for unresponsive throttle
void IRQ_GPI03_INT1_Handler() {
  if (errObserver.unresponsive_throttle) {
    // Do something
  }
}

// Interrupt handler for motor temperature low
void IRQ_GPI04_INT0_Handler() {
  if (errObserver.motor_temp_low) {
    // Do something
  }
}

// Interrupt handler for no CAN signal
void IRQ_GPI04_INT1_Handler() {
  if (errObserver.no_can_signal) {
    // Do something
  }
}

// Interrupt handler for current too high
void IRQ_GPI05_INT0_Handler() {
  if (errObserver.current_too_high) {
    // Do something
  }
}

// Interrupt handler for system error
void IRQ_GPI05_INT1_Handler() {
  if (errObserver.system_error) {
    // Do something
  }
}

// Interrupt handler for insulation fault
void IRQ_GPI06_INT0_Handler() {
  if (errObserver.insulation_fault) {
    // Do something
  }
}

// Interrupt handler for car crash
void IRQ_GPI06_INT1_Handler() {
  if (errObserver.car_crash) {
    // Do something
  }
}

void setup() {
  // Enable interrupts for battery temperature high and low
  attachInterruptVector(IRQ_GPIO1_INT0, &IRQ_GPI01_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT0);
  
  attachInterruptVector(IRQ_GPIO1_INT1, &IRQ_GPI01_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT1);

  // Enable interrupts for no current and accelerator and brakes
  attachInterruptVector(IRQ_GPIO1_INT2, &IRQ_GPI02_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT2);
  
  attachInterruptVector(IRQ_GPIO1_INT3, &IRQ_GPI02_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT3);
  
  // Enable interrupts for hard brake and unresponsive throttle
  attachInterruptVector(IRQ_GPIO1_INT4, &IRQ_GPI03_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT4);
  
  attachInterruptVector(IRQ_GPIO1_INT5, &IRQ_GPI03_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT5);
  
  // Enable interrupts for motor temperature low and no CAN signal
  attachInterruptVector(IRQ_GPIO1_INT6, &IRQ_GPI04_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT6);
  
  attachInterruptVector(IRQ_GPIO1_INT7, &IRQ_GPI04_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT7);
  
  // Enable interrupts for current too high and system error
  attachInterruptVector(IRQ_GPIO1_0_15, &IRQ_GPI05_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_0_15);
  
  attachInterruptVector(IRQ_GPIO1_16_31, &IRQ_GPI05_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_16_31);
  
  // Enable interrupts for insulation fault and car crash
  attachInterruptVector(IRQ_GPIO2_0_15, &IRQ_GPI06_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO2_0_15);
  
  attachInterruptVector(IRQ_GPIO2_16_31, &IRQ_GPI06_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO2_16_31);
}

  
void loop() {
  // Check for battery temperature high and low
  if(errObserver.battery_temp_high){
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);
  }
  
  if (errObserver.battery_temp_low) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT1);
  }

  // Check for no current and accelerator and brakes
  if (errObserver.no_current) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT2);
  }
  if (errObserver.accelerator_and_brakes) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT3);
  }

  // Check for hard brake and unresponsive throttle
  if (errObserver.hard_brake) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT4);
  }
  if (errObserver.unresponsive_throttle) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT5);
  }

  // Check for motor temperature low and no CAN signal
  if (errObserver.motor_temp_low) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT6);
  }
  if (errObserver.no_can_signal) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT7);
  }

  // Check for current too high and system error
  if (errObserver.current_too_high) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_0_15);
  }
  if (errObserver.system_error) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_16_31);
  }

  // Check for insulation fault and car crash
  if (errObserver.insulation_fault) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO2_0_15);
  }
  if (errObserver.car_crash) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO2_16_31);
  }

  // Delay for a short period of time to prevent the loop from running too frequently
  //delay(100); 
}



  





// #include <Arduino.h>
// #include <imxrt.h>

// volatile int foo = 0;

// void IRQ_GPI01_INT0_Handler() {
  
//   foo = 1;
  
// }

// void setup() {
  
//   NVIC_ENABLE_IRQ(IRQ_GPIO1_INT0);
//   attachInterruptVector(IRQ_GPIO1_INT0, &IRQ_GPI01_INT0_Handler);

// }

// void loop() {
//   // generate a random integer between 0 and 5
//   foo = random(6);

//   // check if foo is greater than 1
//   Serial.print("foo is ");
//   Serial.print(foo);
//   if (foo > 1) {
//     // set the interrupt flag for PORTB in the NVIC
//     NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);
//   }
//   Serial.print("foo is ");
//   Serial.print(foo);

//   delay(1000); // wait for 1 second
// }

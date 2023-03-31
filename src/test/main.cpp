#include <Arduino.h>
#include <imxrt.h>



// Variables to hold input states
volatile bool battery_temp_high = false;
volatile bool battery_temp_low = false;
volatile bool no_current = false;
volatile bool accelerator_and_brakes = false;
volatile bool hard_brake = false;
volatile bool unresponsive_throttle = false;
volatile bool motor_temp_low = false;
volatile bool no_can_signal = false;
volatile bool current_too_high = false;
volatile bool system_error = false;
volatile bool insulation_fault = false;
volatile bool car_crash = false;

// Interrupt handler for battery temperature high
void IRQ_GPI01_INT0_Handler() {
  if (battery_temp_high) {
    // Do something
  }
}

// Interrupt handler for battery temperature low
void IRQ_GPI01_INT1_Handler() {
  if (battery_temp_low) {
    // Do something
  }
}

// Interrupt handler for no current
void IRQ_GPI02_INT0_Handler() {
  if (no_current) {
    // Do something
  }
}

// Interrupt handler for accelerator and brakes
void IRQ_GPI02_INT1_Handler() {
  if (accelerator_and_brakes) {
    // Do something
  }
}

// Interrupt handler for hard brake
void IRQ_GPI03_INT0_Handler() {
  if (hard_brake) {
    // Do something
  }
}

// Interrupt handler for unresponsive throttle
void IRQ_GPI03_INT1_Handler() {
  if (unresponsive_throttle) {
    // Do something
  }
}

// Interrupt handler for motor temperature low
void IRQ_GPI04_INT0_Handler() {
  if (motor_temp_low) {
    // Do something
  }
}

// Interrupt handler for no CAN signal
void IRQ_GPI04_INT1_Handler() {
  if (no_can_signal) {
    // Do something
  }
}

// Interrupt handler for current too high
void IRQ_GPI05_INT0_Handler() {
  if (current_too_high) {
    // Do something
  }
}

// Interrupt handler for system error
void IRQ_GPI05_INT1_Handler() {
  if (system_error) {
    // Do something
  }
}

// Interrupt handler for insulation fault
void IRQ_GPI06_INT0_Handler() {
  if (insulation_fault) {
    // Do something
  }
}

// Interrupt handler for car crash
void IRQ_GPI06_INT1_Handler() {
  if (car_crash) {
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
  attachInterruptVector(IRQ_GPIO2_INT0, &IRQ_GPI02_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO2_INT0);
  
  attachInterruptVector(IRQ_GPIO2_INT1, &IRQ_GPI02_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO2_INT1);
  
  // Enable interrupts for hard brake and unresponsive throttle
  attachInterruptVector(IRQ_GPIO3_INT0, &IRQ_GPI03_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO3_INT0);
  
  attachInterruptVector(IRQ_GPIO3_INT1, &IRQ_GPI03_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO3_INT1);
  
  // Enable interrupts for motor temperature low and no CAN signal
  attachInterruptVector(IRQ_GPIO4_INT0, &IRQ_GPI04_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO4_INT0);
  
  attachInterruptVector(IRQ_GPIO4_INT1, &IRQ_GPI04_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO4_INT1);
  
  // Enable interrupts for current too high and system error
  attachInterruptVector(IRQ_GPIO5_INT0, &IRQ_GPI05_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO5_INT0);
  
  attachInterruptVector(IRQ_GPIO5_INT1, &IRQ_GPI05_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO5_INT1);
  
  // Enable interrupts for insulation fault and car crash
  attachInterruptVector(IRQ_GPIO6_INT0, &IRQ_GPI06_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO6_INT0);
  
  attachInterruptVector(IRQ_GPIO6_INT1, &IRQ_GPI06_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO6_INT1);
}

  
void loop() {
  // Check for battery temperature high and low
  if (isBatteryTempHigh()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);
  }
  if (isBatteryTempLow()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT1);
  }

  // Check for no current and accelerator and brakes
  if (isNoCurrent()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO2_INT0);
  }
  if (isAccelAndBrakes()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO2_INT1);
  }

  // Check for hard brake and unresponsive throttle
  if (isHardBrake()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO3_INT0);
  }
  if (isUnresponsiveThrottle()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO3_INT1);
  }

  // Check for motor temperature low and no CAN signal
  if (isMotorTempLow()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO4_INT0);
  }
  if (isNoCAN()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO4_INT1);
  }

  // Check for current too high and system error
  if (isCurrentTooHigh()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO5_INT0);
  }
  if (isSystemError()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO5_INT1);
  }

  // Check for insulation fault and car crash
  if (isInsulationFault()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO6_INT0);
  }
  if (isCarCrash()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO6_INT1);
  }

  // Delay for a short period of time to prevent the loop from running too frequently
  delay(100);
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

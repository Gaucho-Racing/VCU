#include <Arduino.h>
#include <imxrt.h>
#include "utility.h"
#include "I_no_can_speak_flex.h"
#include "main.h"
#include "constants.h"
#include "stubs.h"
#include <string>


volatile States state;
//dash
volatile bool sendToDash;
//message to send to dash
volatile std::string errMess;

I_no_can_speak_flex car(true);
volatile carFailure errObserver;



void setup() {
   state = OFF;
}

void loop() {


   // Check for battery temperature high and low
  if(car.BMS.getTemp() > BAT_TEMP_MAX){
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);
  }
  
  if (car.BMS.getTemp() < BAT_TEMP_MIN) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT1);
  }

  // Check for no current and accelerator and brakes
  if (car.BMS.getCurrent() < NO_CURRENT) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT2);
  }
  if (car.pedals.getAPPS() > 0.25 && (car.pedals.getBrakePressure1() > MIN_BRAKE_PRESSURE || car.pedals.getBrakePressure2() > MIN_BRAKE_PRESSURE)){
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT3);
  }

  // Check for hard brake and unresponsive throttle
  if (car.pedals.getBrakePressure1() > HARD_BRAKE_LIMIT || car.pedals.getBrakePressure2() > HARD_BRAKE_LIMIT) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT4);
  }
  //FIX THIS SHIT IT IS PROB WRONG
  if (car.pedals.getAPPS() > APPS_UNRESPONSIVE_MAX && car.DTI.getACCurrent() < MIN_CURRENT_MOTOR) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT5);
  }

  // Check for motor temperature low 
  if (car.DTI.getMotorTemp() < MIN_MOTOR_TEMP) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT6);
  }
  //no CAN Signal
  //FIX LATER IDK
  if (!car.canSend) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT7);
  }

  // Check for current too high and system err
  if (car.BMS.getCurrent()>THRESHOLD_PLACEHOLDER_CURR) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_0_15);
  }

  //????
  if (errObserver.system_error) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_16_31);
  }

  // Check for insulation fault and car crash
  if (car.IMD.getHardware_Error()) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO2_0_15);
  }
  //
  if (car.sensors.getLinAccelX() > THRESHOLD_G_FORCE) {
    NVIC_TRIGGER_IRQ(IRQ_GPIO2_16_31);
  }

  // Delay for a short period of time to prevent the loop from running too frequently
  //delay(100); 

     switch (state) {
      case OFF:
         state = off();
         break;
      case ON:
         state = on();
         break;
      case ON_READY:
         state = on_ready();
         break;
      case DRIVE:
         state = drive();
         break;
      case CHARGE_PRECHARGE:
         state = charge_precharge();
         break;
      case CHARGE_CHARGING:
         state = charge_charging();
         break;
      case CHARGE_FULL:
         state = charge_full();
         break;
   }
}

// Variables to hold input states


// Interrupt handler for battery temperature high
void BatteryTempHighInterrupt() {

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

}

// Interrupt handler for motor temperature low
void IRQ_GPI04_INT0_Handler() {

}

// Interrupt handler for no CAN signal
void IRQ_GPI04_INT1_Handler() {

}

// Interrupt handler for current too high
void IRQ_GPI05_INT0_Handler() {

}
// Interrupt handler for system error
void IRQ_GPI05_INT1_Handler() {

}

// Interrupt handler for insulation fault
void IRQ_GPI06_INT0_Handler() {

}

// Interrupt handler for car crash
void IRQ_GPI06_INT1_Handler() {

}

void setup() {
  // Enable interrupts for battery temperature high and low
  attachInterruptVector(IRQ_GPIO1_INT0, &BatteryTempHighInterrupt);
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

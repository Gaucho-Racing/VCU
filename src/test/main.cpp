#include <Arduino.h>
#include <imxrt.h>

// Variables to hold input states
volatile bool brakes_engaged = false;
volatile bool accelerator_over_25 = false;
volatile bool charger_connected = false;
volatile bool charging_not_active = false;
volatile bool battery_temp_low = false;
volatile bool battery_temp_high = false;

// Interrupt handler for brakes engaged and accelerator input > 25%
void IRQ_GPI02_INT0_Handler() {
  if (brakes_engaged() && accelerator_over_25()) {
    // Do something
  }
}

// Interrupt handler for charger connected, but not charging
void IRQ_GPI04_INT0_Handler() {
  if (charger_connected() && !charging_not_active()) {
    // Do something
  }
}

// Interrupt handler for battery temp low
void IRQ_GPI06_INT0_Handler() {
  if (battery_temp_low()) {
    // Do something
  }
}

// Interrupt handler for battery temp high
void IRQ_GPI06_INT1_Handler() {
  if (battery_temp_high()) {
    // Do something
  }
}

void setup() {
  // Enable interrupts for brake and accelerator inputs
  attachInterruptVector(IRQ_GPIO2_INT0, &IRQ_GPI02_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO2_INT0);
  
  attachInterruptVector(IRQ_GPIO3_INT0, &IRQ_GPI02_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO3_INT0);
  
  // Enable interrupt for charger connected and not charging
  attachInterruptVector(IRQ_GPIO4_INT0, &IRQ_GPI04_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO4_INT0);
  
  attachInterruptVector(IRQ_GPIO5_INT0, &IRQ_GPI04_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO5_INT0);
  
  // Enable interrupts for battery temp
  attachInterruptVector(IRQ_GPIO6_INT0, &IRQ_GPI06_INT0_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO6_INT0);
  
  attachInterruptVector(IRQ_GPIO6_INT1, &IRQ_GPI06_INT1_Handler);
  NVIC_ENABLE_IRQ(IRQ_GPIO6_INT1);
}

void loop() {
  // Read input states
  brakes_engaged = get_brakes_engaged();
  accelerator_over_25 = get_accelerator_over_25();
  charger_connected = get_charger_connected();
  charging_not_active = get_charging_not_active();
  battery_temp_low = get_battery_temp_low();
  battery_temp_high = get_battery_temp_high();

  // Wait for some time
  delay(100);
}

// Function to get brakes engaged state
bool get_brakes_engaged() {
  // Return the current state of the brakes
}

// Function to get accelerator input state
bool get_accelerator_over_25() {
  // Return true if the accelerator input is over 25%
}

// Function to get charger connected state
bool get_charger_connected() {
  // Return the current state of the charger connection
}

// Function to get charging not active state
bool get_charging_not_active() {
  // Return the current state of the charging activity
}

// Function to get battery temp low state
bool get_battery_temp_low() {
  // Return true if the battery temperature is low
}

// Function to get battery temp high state
bool get_battery_temp_high() {
  // Return true if the battery temperature is high
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

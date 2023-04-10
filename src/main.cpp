#include <Arduino.h>
#include <imxrt.h>
#include "utility.h"
// #include "I_no_can_speak_flex.h"
#include "main.h"
#include "constants.h"
#include "stubs.h"
#include <string>
// using namespace std;

// enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL, FATAL_ERROR};

volatile States state;
//dash
volatile bool sendToDash = false;
//message to send to dash
volatile std::string errMess = "";

I_no_can_speak_flex car(true);
volatile carFailure errObserver;




void loop() {
  bool batteryTempHigh = car.BMS.getTemp() > BAT_TEMP_MAX; 
  bool batteryTempLow = car.BMS.getTemp() < BAT_TEMP_MIN;
  bool noCurrent = car.DTI.getDCCurrent() < MIN_CURRENT_THRESHOLD; // ?? TODO: FIX
  bool APPSBSPDViolation = car.pedals.getAPPS() > 0.25 && (car.pedals.getBrakePressure1() > MIN_BRAKE_PRESSURE || car.pedals.getBrakePressure2() > MIN_BRAKE_PRESSURE);
  bool hardBrake = car.pedals.getBrakePressure1() > HARD_BRAKE_LIMIT || car.pedals.getBrakePressure2() > HARD_BRAKE_LIMIT;
  bool accelUnresponsive = car.pedals.getAPPS() > APPS_UNRESPONSIVE_MAX && car.DTI.getDCCurrent() < MIN_RESPONSIVE_CURRENT_MOTOR;  //TODO LATER FIX THIS SHIT IT IS PROB WRONG
  bool motorTempHigh = car.DTI.getMotorTemp() > MOT_TEMP_MAX;
  bool CANFailure = !car.canSend; // IDK if this is right but seems right
  bool currentExceeds = car.DTI.getDCCurrent()> DTI_CURRENT_THRESHOLD;
  bool systemError = true; //TODO: FIX THIS ACTUAL VALUE
  bool IMDFault = car.IMD.getHardware_Error();
  bool GForceCrash = sqrt(car.sensors.getLinAccelX()*car.sensors.getLinAccelX() +
                            car.sensors.getLinAccelY()*car.sensors.getLinAccelY() +
                              car.sensors.getLinAccelZ()*car.sensors.getLinAccelZ()) > G_FORCE_LIMIT;


  if(batteryTempHigh){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);}
  if(batteryTempLow){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT1);}
  if(noCurrent){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT2);}
  if(APPSBSPDViolation){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT3);}
  if(hardBrake){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT4);}
  if(accelUnresponsive){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT5);}
  if(motorTempHigh){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT6);}
  if(CANFailure){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT7);}
  if(currentExceeds){NVIC_TRIGGER_IRQ(IRQ_GPIO1_0_15);}
  if(systemError){NVIC_TRIGGER_IRQ(IRQ_GPIO1_16_31);}
  if(IMDFault){NVIC_TRIGGER_IRQ(IRQ_GPIO2_0_15);}
  if(GForceCrash){NVIC_TRIGGER_IRQ(IRQ_GPIO2_16_31);}

  // Delay for a short period of time to prevent the loop from running too frequently
  //delay(100); 

     switch (state) {
      case OFF:
         state = off(car);
         break;
      case ON:
         state = on(car);
         break;
      case ON_READY:
         state = on_ready(car);
         break;
      case DRIVE:
         state = drive(car);
         break;
      case CHARGE_PRECHARGE:
         state = charge_precharge(car);
         break;
      case CHARGE_CHARGING:
         state = charge_charging(car);
         break;
      case CHARGE_FULL:
         state = charge_full(car);
         break;
   }
}
//NOTE: 
// might want to think about how we are going to restore certain settings once there isnt an error anymore. 

// Interrupt handler for battery temperature high
void BatteryTempHigh_ISR() {
   // Dissalow Charging
   // Send Message to Dash
   const_cast<std::string&>(errMess).append("WARNING: CELL TEMPERATURE HIGH, LIMITING POWER DRAW.\n");
   // Limit Motor Current Draw
   car.DTI.setMaxCurrent(OVERHEAT_CURRENT_LIMIT);
   // Shut down car if Very high
   if(car.BMS.getTemp() > CRITICAL_BATTERY_TEMP_HIGH){
      const_cast<std::string&>(errMess).append("CRITICAL: CELL TEMP VERY HIGH, SHUTTING DOWN.");
      // state = OFF;
   }
}

// Interrupt handler for battery temperature low
void BatteryTempLow_ISR() {
   // Dissalow Charging 
   
   // Send Message to Dash
   const_cast<std::string&>(errMess).append("WARNING: CELL TEMPERATURE LOW.\n");
   // SHut Down car if Very Low

}

// Interrupt handler for no current
void NoCurrent_ISR() {
   // Dashboard Warning Send
   const_cast<std::string&>(errMess).append("WARNING: NO CURRENT TO DTI MC.\n");
   // state OFF?
}

// Interrupt handler for accelerator and brakes
void APPSBSPDCheck_ISR() {
   // Disengage motor
   car.DTI.setCurrent(0);
   // Send message to Dash
   const_cast<std::string&>(errMess).append("WARNING: POWER LIMITED: APPS/BSPD ENGAGED BRAKE & THROTTLE\n");
}

// Interrupt handler for hard brake
void HardBrake_ISR() {
   // Disengage motor
   car.DTI.setRCurrent(0);
}

// Interrupt handler for unresponsive throttle
void UnresponsiveThrottle_ISR() {
   // Send Dash Warning
   const_cast<std::string&>(errMess).append("CRITICAL: THROTTLE SIGNAL UNRESPONSIVE. FIX\n");
   // state = OFF
}

// Interrupt handler for motor temperature high
void MotorTempHigh_ISR() {
   // Give dash warning
   const_cast<std::string&>(errMess).append("WARNING: MOTOR TEMP HIGH, LIMITING POWER DRAW\n");
   // Limit Motor Current draw
   car.DTI.setMaxCurrent(MAX_CURRENT_DRAW_HIGH_MOTOR);
   // IF very high, stop car
   if(car.DTI.getMotorTemp() > CRITICAL_MOTOR_TEMP){
      const_cast<std::string&>(errMess).append("CRITICAL: MOTOR TEMP VERY HIGH, SHUTTING DOWN\n");
      car.DTI.setCurrent(0);
      //state off
   }
}

// Interrupt handler for no CAN signal
void NoCAN_ISR() {
   // IDK Shut down?
}

// Interrupt handler for current too high
void CurrentExceeds_ISR() {

}

// Interrupt handler for system error
void SystemError_ISR() {
   //Disengage motor
   //Stop charging (if charging)
}

// Interrupt handler for insulation fault
void IMDFault_ISR() {
   // Give dash a critical warning
   const_cast<std::string&>(errMess).append("CRITICAL: IMD FAULT CHASSIS POSSIBLY ENERGIZED. EXIT VEHICLE.\n");
   // Shut Down car
   car.DTI.setCurrent(0);

}

// Interrupt handler for car crash
void CarCrashed_ISR() {
   // Dash Warning
   // Disengage motor
   car.DTI.setCurrent(0);
   // Shut down car
   

}


void setup() {

  //-------SET STATE------------

   state = OFF;

  //------- ENABLE NVIC INTERRUPTS------

  // Enable interrupts for battery temperature high 
  attachInterruptVector(IRQ_GPIO1_INT0, &BatteryTempHigh_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT0);
  
  //battery temp low
  attachInterruptVector(IRQ_GPIO1_INT1, &BatteryTempLow_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT1);

  // Enable interrupts for no current 
  attachInterruptVector(IRQ_GPIO1_INT2, &NoCurrent_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT2);

  // APPS/BSPD accelerator and brakes
  attachInterruptVector(IRQ_GPIO1_INT3, &APPSBSPDCheck_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT3);
  
  // Enable interrupts for hard brake 
  attachInterruptVector(IRQ_GPIO1_INT4, &HardBrake_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT4);
  
  // unresponsive throttle
  attachInterruptVector(IRQ_GPIO1_INT5, &UnresponsiveThrottle_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT5);
  
  // Enable interrupts for motor temperature high 
  attachInterruptVector(IRQ_GPIO1_INT6, &MotorTempHigh_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT6);
  
  // no CAN signal
  attachInterruptVector(IRQ_GPIO1_INT7, &NoCAN_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT7);
  
  // Enable interrupts for current too high 
  attachInterruptVector(IRQ_GPIO1_0_15, &CurrentExceeds_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_0_15);
  
  // system error
  attachInterruptVector(IRQ_GPIO1_16_31, &SystemError_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_16_31);
  
  // Enable interrupts for insulation fault
  attachInterruptVector(IRQ_GPIO2_0_15, &IMDFault_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO2_0_15);
  
  // car crash
  attachInterruptVector(IRQ_GPIO2_16_31, &CarCrashed_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO2_16_31);
}
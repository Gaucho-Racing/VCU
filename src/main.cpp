//main.cpp
// @nikunjparasar, @rt.z, @Th3Will


//#include <Arduino.h>, already done in main.h
//#include <imxrt.h>, moved to main.h
#include "main.h"
#include "mainUtility.h"
#include "error.h"
#include "constants.h"
#include "stubs.h"
#include "onOffUtility.h"
//#include <string>
//#include <map>
//#include <vector>
//#include <algorithm>
//#include <queue>
//#include <iostream>
//using namespace std;

volatile States state;
volatile States prevState; 
volatile bool (*errorCheck)(void); 

I_no_can_speak_flex car(true);
int apps_implausibility_time = 0, bse_implausibility_time = 0;

// IMPORTANT CHECKS
volatile bool batteryTempHigh() { return car.BMS.getTemp() > CELL_TEMP_WARN; }

volatile bool noCurrent() {return car.DTI.getDCCurrent() < VALUE_MIN_CURRENT_THRESHOLD; }

//NOTE: Waiting on SCS team for proper way to do this
volatile bool APPSBSPDViolation() {
   return (car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > VALUE_APPS_BSPD_THROTTLE && 
      (car.pedals.getBrakePressure1() > VALUE_MIN_BRAKE_PRESSURE || car.pedals.getBrakePressure2() > VALUE_MIN_BRAKE_PRESSURE);
}

volatile bool CanReturnFromAPPSBSPD() {
   return (car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 < VALUE_APPS_BSPD_RETURN;
}

volatile bool hardBrake() {
   return car.pedals.getBrakePressure1() > VALUE_HARD_BRAKE_LIMIT || 
      car.pedals.getBrakePressure2() > VALUE_HARD_BRAKE_LIMIT;
}


volatile bool accelUnresponsive() {
   return (car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > VALUE_APPS_UNRESPONSIVE_MAX && 
      car.DTI.getDCCurrent() < VALUE_MIN_RESPONSIVE_CURRENT_MOTOR;
} //TODO LATER FIX THIS SHIT IT IS PROB WRONG

volatile bool motorTempHigh() { return car.DTI.getMotorTemp() > VALUE_MOT_TEMP_MAX; }

volatile bool CANFailure() { 
   return (car.DTI.getAge() > MAX_CAN_DURATION || 
      car.IMD.getAge() > MAX_CAN_DURATION || 
      car.sensors.getAge() > MAX_CAN_DURATION || 
      car.pedals.getAge() > MAX_CAN_DURATION || 
      car.charger.getAge() > MAX_CAN_DURATION || 
      car.BMS.getAge() > MAX_CAN_DURATION);
}

volatile bool currentExceeds() { return car.DTI.getDCCurrent()> VALUE_DTI_CURRENT_THRESHOLD; }

volatile bool systemError() { return false; }//STUUUB!! D:<

volatile bool IMDFault() { return car.IMD.getHardware_Error(); }

volatile bool GForceCrash() {
   return sqrt(car.sensors.getLinAccelX()*car.sensors.getLinAccelX() +
                           car.sensors.getLinAccelY()*car.sensors.getLinAccelY() +
                           car.sensors.getLinAccelZ()*car.sensors.getLinAccelZ()) > VALUE_G_FORCE_LIMIT;
}

// AND ONE MORE JUST TO CHECK WHETHER OR NOT THERE'S STILL CRITS. AT STARTUP -rt.z
volatile bool hasStartupCrits() {
   return criticalCheck(car, false);
}

/* use this for interrupts to store currentState; handles the specified error */
States sendToError(volatile States currentState, volatile bool (*erFunc)(void)) {
   errorCheck = erFunc; 
   prevState = currentState; 
   return ERROR;
}

void criticalBeeps() {
   car.DTI.setCurrent(0);
   digitalWrite(3, HIGH);
   delay(1000);
   digitalWrite(3, LOW);

}

/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                          MAIN LOOP
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
void loop() {
  car.readData();
   if(batteryTempHigh()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);}
   if(noCurrent()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT2);}
   if(APPSBSPDViolation()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT3);}
   if(hardBrake()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT4);}
   if(accelUnresponsive()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT5);}
   if(motorTempHigh()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT6);}
   if(CANFailure()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT7);}
   if(currentExceeds()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_0_15);}
   if(systemError()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_16_31);}
   if(IMDFault()){NVIC_TRIGGER_IRQ(IRQ_GPIO2_0_15);}
   if(GForceCrash()){NVIC_TRIGGER_IRQ(IRQ_GPIO2_16_31);}
   if (abs(car.pedals.getAPPS1() - car.pedals.getAPPS2()) >= 10) {
      apps_implausibility_time += car.pedals.getAge();
      if (apps_implausibility_time >= 100) {
         car.DTI.setRCurrent(0);
         return;
      } else {
         apps_implausibility_time = 0;
      }
   }
   if (car.pedals.getBrakeLimit()) {
      bse_implausibility_time += car.pedals.getAge();
      if (bse_implausibility_time >= 100) {
         car.DTI.setRCurrent(0);
         return;
      } else {
         bse_implausibility_time = 0;
      }
   }

  TS_WARN_Check(car);

   switch (state) {
      case OFF:
         state = off(car);
         break;
      case ON:
         if ((state = on(car)) == ERROR) sendToError(ON, &hasStartupCrits);
         break;
      case ON_READY:
         state = on_ready(car);
         break;
      case DRIVE:
         state = drive(car);
         break;
      /*
      case CHARGE_PRECHARGE:
         state = charge_precharge(car);
         break;
      case CHARGE_CHARGING:
         state = charge_charging(car);
         break;
      case CHARGE_FULL:
         state = charge_full(car);
         break;
      */
      case ERROR:
         state = error(car, prevState, errorCheck);
         break;
   }

}

/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                      HIGH PRIORITY INTERRUPT SERVICE ROUTINES 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/


//TEMPERATURE MANAGEMENT IS CONTROLLED BY ORION BMS, THESE ISRs MAY BE REDUNDANT
// Interrupt handler for battery temperature high
void BatteryTempHigh_ISR() {
   // // CRITICAL
   // if(car.BMS.getTemp() > CRITICAL_CELL_TEMP){
   //    car.DTI.setCurrent(0);
   //    car.DTI.setDriveEnable({0});
   //    car.sendDashError(102);
   //    state = sendToError(state, &batteryTempHigh);
   // }
   // else {
   //    // WARNING ONLY
   //    car.sendDashError(2);
   //    /*
   //       TODO: FIX
   //    */
   //    // Limit Motor Current Draw
   //    car.DTI.setMaxCurrent(CELL_OVERHEAT_CURRENT_LIMIT);
   //    // TODO: WAY TO RESTORE MAX CURRENT ONCE NOT OVERHEATING
   // }
}

// Interrupt handler for no current
void NoCurrent_ISR() {
   car.sendDashError(103);
   state = sendToError(state, &noCurrent);
}

// Interrupt handler for accelerator and brakes
void APPSBSPDCheck_ISR() {
   car.sendDashError(99);
   while(!CanReturnFromAPPSBSPD() && driveEngaged(car)){
      car.DTI.setCurrent(0);
      // Send message to Dash
   }
}

// Interrupt handler for hard brake
void HardBrake_ISR() {
   // Can someone confirm the rule for this. 
   // There's no rule for this. It's just a safety feature we decided on in case the car's out of control.
   car.DTI.setCurrent(0);
   state = sendToError(state, &hardBrake);
}

// Interrupt handler for unresponsive throttle
void UnresponsiveThrottle_ISR() {
   // Send Dash Warning
   car.sendDashError(104);
   state = sendToError(state, &accelUnresponsive);
}

//TEMPERATURE MANAGEMENT IS CONTROLLED BY ORION BMS, THESE ISRs MAY BE REDUNDANT
// NOT SURE FOR MOTOR THOUGH
// Interrupt handler for motor temperature high
void MotorTempHigh_ISR() {
   // if(car.DTI.getMotorTemp() > VALUE_CRITICAL_MOTOR_TEMP){
   //    car.sendDashError(105);
   //    state = sendToError(state, &motorTempHigh);
   // }
   // else {
   //    /*
   //    TODO FIX
   //    */
   //    // Give dash warning
   //    car.sendDashError(3);
   //    // Limit Motor Current draw
   //    car.DTI.setMaxCurrent(VALUE_MAX_CURRENT_DRAW_HIGH_MOTOR);
   // }
}

// Interrupt handler for no CAN signal
void NoCAN_ISR() {
   // IDK Shut down? 
}

// Interrupt handler for current too high
void CurrentExceeds_ISR() {
   car.sendDashError(106);
   state = sendToError(state, &currentExceeds);
}

// Interrupt handler for system error
void SystemError_ISR() {
   car.sendDashError(100);
   state = sendToError(state, &systemError);
}

// Interrupt handler for insulation fault
void IMDFault_ISR() {
   // Give dash a critical warning
   car.sendDashError(107);
   state = sendToError(state, &IMDFault);
}

// Interrupt handler for car crash
void CarCrashed_ISR() {
   // Dash Warning
   car.sendDashError(108);
   state = sendToError(state, &GForceCrash);
}


/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                           SETUP
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

void setup() {
   Serial.begin(9600);
   car.begin();

   //set beeper pin to output mode
   pinMode(3, OUTPUT);

  //-------SET STATE------------

   state = OFF;

  //------- ENABLE NVIC INTERRUPTS------

  // Enable interrupts for battery temperature high 
  attachInterruptVector(IRQ_GPIO1_INT0, &BatteryTempHigh_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT0);
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

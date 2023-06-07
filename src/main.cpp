//main.cpp
// @nikunjparasar, @rt.z, @Th3Will

#include "main.h"
#include "mainUtility.h"
#include "error.h"
#include "constants.h"
#include "stubs.h"
#include "onOffUtility.h"
#include "testing.h"


volatile States state;
volatile States prevState; 
volatile bool (*errorCheck)(void); 

//I_no_can_speak_flex car(true);
int apps_implausibility_time = 0, bse_implausibility_time = 0;

Switchboard s;
I_no_can_speak_flex car(true); 
const int on_off_pin = 12;
const int engage_pin = 11;
const int full_pwr_pin = 10;
const int brake_pin = 9;
const int pedal_pin = 24;

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                  INTERRUPTS TRIGGER FUNCTIONS
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

volatile bool APPSBSPDViolation() {
   return s.drive_engage && (car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > VALUE_APPS_BSPD_THROTTLE && 
      (car.pedals.getBrakePressure1() > VALUE_MIN_BRAKE_PRESSURE || car.pedals.getBrakePressure2() > VALUE_MIN_BRAKE_PRESSURE);
}

volatile bool CanReturnFromAPPSBSPD() {
   return !s.drive_engage || (car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 < VALUE_APPS_BSPD_RETURN;
}

volatile bool hardBrake() {
   return s.drive_engage && car.pedals.getBrakePressure1() > VALUE_HARD_BRAKE_LIMIT || 
      car.pedals.getBrakePressure2() > VALUE_HARD_BRAKE_LIMIT;
}
volatile bool accelUnresponsive() {
   return s.drive_engage && (car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > VALUE_APPS_UNRESPONSIVE_MAX && 
      car.DTI.getDCCurrent() <= VALUE_MIN_RESPONSIVE_CURRENT_MOTOR;
} 
volatile bool motorTempHigh() { return car.DTI.getMotorTemp() > VALUE_MOT_TEMP_MAX; }
volatile bool CANFailure() { 
   return (car.DTI.getAge() > MAX_CAN_DURATION || 
      // car.IMD.getAge() > MAX_CAN_DURATION || 
      car.sensors.getAge() > MAX_CAN_DURATION || 
      car.pedals.getAge() > MAX_CAN_DURATION || 
      car.charger.getAge() > MAX_CAN_DURATION || 
      car.BMS.getAge() > MAX_CAN_DURATION);
}
volatile bool currentExceeds() { return car.DTI.getDCCurrent() > VALUE_DTI_CURRENT_THRESHOLD; }
volatile bool GForceCrash() {
   return sqrt(car.sensors.getLinAccelX()*car.sensors.getLinAccelX() +
                           car.sensors.getLinAccelY()*car.sensors.getLinAccelY() +
                           car.sensors.getLinAccelZ()*car.sensors.getLinAccelZ()) > VALUE_G_FORCE_LIMIT;
}

volatile bool APPSImplausibility() {
   if (abs(car.pedals.getAPPS1() - car.pedals.getAPPS2()) >= 10) {
      apps_implausibility_time += car.pedals.getAge();
      return s.drive_engage && (apps_implausibility_time >= 100);
   } else {
      apps_implausibility_time = 0;
      return false;
   }
}

volatile bool BSEImplausibility() {
   if (car.pedals.getBrakeLimit()) {
      bse_implausibility_time += car.pedals.getAge();
      return s.drive_engage && (bse_implausibility_time >= 100);
   } else {
      bse_implausibility_time = 0;
      return false;
   }
}

// AND ONE MORE JUST TO CHECK WHETHER OR NOT THERE'S STILL CRITS. AT STARTUP -rt.z
volatile bool hasStartupCrits() {
   return criticalCheck(car, false); 
   //return false; //STUB TODO FIX
}

/* use this for interrupts to store currentState; handles the specified error */

States sendToError(volatile States currentState, volatile bool (*erFunc)(void)) {
   errorCheck = erFunc; 
   prevState = currentState; 
   return ERROR;
}

/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                          MAIN LOOP
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

void loop() {
//   car.readData();
   if (state != OFF) {
      // if(hardBrake()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT4);}
      // if(accelUnresponsive()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT5);}
      // if(motorTempHigh()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT6);}
      // if(CANFailure()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT7);}
      // if(currentExceeds()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_0_15);}
      // if(GForceCrash()){NVIC_TRIGGER_IRQ(IRQ_GPIO2_16_31);}
      if(APPSImplausibility()) {
         car.sendDashError(97);
         car.DTI.setRCurrent(0);

      }
      if(BSEImplausibility()) {
         car.sendDashError(98);
         car.DTI.setRCurrent(0);
      }
      if(APPSBSPDViolation()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT3);}
   }
     
   // TS_WARN_Check(car);
   if(digitalRead(on_off_pin) == HIGH){
      s.drive_enable = 1;
   }else{
      s.drive_enable = 0;
   }

   if(digitalRead(engage_pin) == HIGH){
      s.drive_engage = 1;
   }else{
      s.drive_engage = 0;
   }

   if(digitalRead(full_pwr_pin)== HIGH){
      s.full_pwr = 1;

   }else{
      s.full_pwr = 0;
   }
   if(digitalRead(brake_pin) == HIGH){
      s.SWITCH_TEST_BRAKES = 1;
   }
   else{
      s.SWITCH_TEST_BRAKES = 0;
   }
   s.ROTARY_TEST_ACCEL = analogRead(pedal_pin)/1023.0;



   switch (state) {
      case OFF:
         state = off(car, s);
         break;
      case ON:
         if ((state = on(car, s)) == ERROR) sendToError(ON, &hasStartupCrits);
         break;
      case ON_READY:
         state = on_ready(car, s);
         break;
      case DRIVE:
         state = drive(car, s);
         break; 
      // CHARGING STUFF NOT NEEDED
      case ERROR:
         state = error(car, prevState, errorCheck, s);
         break;
      // case TESTING:
      //    state = testing(car, state);
      //    break;
   }
   testing(car, s, state);
}


// void loop(){
//    led.begin();
//    led.clear();
//    led.show();
//    car.readData();
//    //car.setDriveEnable(true);
//    double MAX_PEDAL_CURRENT = 50;
//    Serial.println(car.DTI.getERPM()/10.0);
//    if(digitalRead(on_off_pin) == HIGH){
//       car.DTI.setDriveEnable(true);
//       int level = analogRead(pedal_pin);
//       if(level < 25) car.DTI.setRCurrent(0);
//       else{
//          car.DTI.setRCurrent(MAX_PEDAL_CURRENT*level/1023.0);
//       }
//    }else{
//       car.DTI.setDriveEnable(false);
//       car.DTI.setRCurrent(0);
//    }
// }

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                      HIGH PRIORITY INTERRUPT SERVICE ROUTINES 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/


// Interrupt handler for accelerator and brakes
void APPSBSPDCheck_ISR() {
   car.sendDashError(99);
   if (!CanReturnFromAPPSBSPD() && s.drive_engage){
      car.DTI.setRCurrent(0);
      // Send message to Dash
   }
}
// Interrupt handler for hard brake
void HardBrake_ISR() {
   // Can someone confirm the rule for this. 
   // There's no rule for this. It's just a safety feature we decided on in case the car's out of control.
   car.DTI.setRCurrent(0);
   state = sendToError(state, &hardBrake);
}
// Interrupt handler for unresponsive throttle
void UnresponsiveThrottle_ISR() {
   // Send Dash Warning
   car.sendDashError(104);
   state = sendToError(state, &accelUnresponsive);
}
// Interrupt handler for motor temperature high
void MotorTempHigh_ISR() {
      car.sendDashError(105);
      state = sendToError(state, &motorTempHigh);
   
}
// Interrupt handler for no CAN signal
void NoCAN_ISR() {
   //TODO FIX
}
// Interrupt handler for current too high
void CurrentExceeds_ISR() {
   car.sendDashError(106);
   state = sendToError(state, &currentExceeds);
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
   led.begin();

   pinMode(on_off_pin, INPUT_PULLUP);
   pinMode(engage_pin, INPUT_PULLUP);
   pinMode(full_pwr_pin, INPUT_PULLUP);
   pinMode(brake_pin, INPUT_PULLUP);
   pinMode(pedal_pin, INPUT);

   //set beeper pin to output mode
   pinMode(3, OUTPUT);

  //-------SET STATE------------

   state = OFF;

  //------- ENABLE NVIC INTERRUPTS------

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
  // car crash
  attachInterruptVector(IRQ_GPIO2_16_31, &CarCrashed_ISR);
  NVIC_ENABLE_IRQ(IRQ_GPIO2_16_31);
}

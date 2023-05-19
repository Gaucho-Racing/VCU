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
FakeCar car(true); 
const int on_off_pin = 12;
const int engage_pin = 11;
const int full_pwr_pin = 10;
const int tc_pin = 9;

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        
                  INTERRUPTS TRIGGER FUNCTIONS
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

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
      car.DTI.getDCCurrent() <= VALUE_MIN_RESPONSIVE_CURRENT_MOTOR;
} 
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
volatile bool GForceCrash() {
   return sqrt(car.sensors.getLinAccelX()*car.sensors.getLinAccelX() +
                           car.sensors.getLinAccelY()*car.sensors.getLinAccelY() +
                           car.sensors.getLinAccelZ()*car.sensors.getLinAccelZ()) > VALUE_G_FORCE_LIMIT;
}

volatile bool APPSImplausibility() {
   if (abs(car.pedals.getAPPS1() - car.pedals.getAPPS2()) >= 10) {
      apps_implausibility_time += car.pedals.getAge();
      return (apps_implausibility_time >= 100);
   } else {
      apps_implausibility_time = 0;
      return false;
   }
}

volatile bool BSEImplausibility() {
   if (car.pedals.getBrakeLimit()) {
      bse_implausibility_time += car.pedals.getAge();
      return (bse_implausibility_time >= 100);
   } else {
      bse_implausibility_time = 0;
      return false;
   }
}

// AND ONE MORE JUST TO CHECK WHETHER OR NOT THERE'S STILL CRITS. AT STARTUP -rt.z
volatile bool hasStartupCrits() {
   // return criticalCheck(car, false); 
   return false; //STUB TODO FIX
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
//   car.readData();
   // if(APPSBSPDViolation()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT3);}
   // if(hardBrake()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT4);}
   // if(accelUnresponsive()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT5);}
   // if(motorTempHigh()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT6);}
   // if(CANFailure()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT7);}
   // if(currentExceeds()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_0_15);}
   // if(GForceCrash()){NVIC_TRIGGER_IRQ(IRQ_GPIO2_16_31);}
   // if(APPSImplausibility()) {
   //    car.sendDashError(97);
   //    car.DTI.setRCurrent(0);

   // }
   // if(BSEImplausibility()) {
   //    car.sendDashError(98);
   //    car.DTI.setRCurrent(0);
   // }

   // TS_WARN_Check(car);
   // Serial.println("WHAT THE FUCK");
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
      if(state == DRIVE){
         led.setPixelColor(1, led.Color(0, 255, 0));
         led.setPixelColor(2, led.Color(0, 255, 0));
         led.show();
      }
      
   }else{
      s.full_pwr = 0;
      if(state == DRIVE){
         led.setPixelColor(1, led.Color(0, 255, 255));
         led.setPixelColor(2, led.Color(0, 255, 255));
         led.show();
      }
      
   }
   if(digitalRead(tc_pin)== HIGH){
      s.traction_control = 1;
      if(state == DRIVE){
         led.setPixelColor(3, led.Color(255, 120, 0));
         led.show();
      }
      
   }else{
      s.traction_control = 0;
      if(state == DRIVE){
         led.setPixelColor(3, led.Color(0, 0, 255));
         led.show();
      }
      
   }

   //NOTE:

   // TOGGLES ARE PINS 12, 11, 10, 9, 8
   /*
   12: ON OFF
   11: START 
   10: POWER MODe
   9 : ?
   8 : ?
   */

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
         state = error(car, prevState, errorCheck);
         break;
      case TESTING:
         state = testing(car, state);
         break;
   }
   testing(car, state);
}

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
   // car.begin();
   led.begin();

   pinMode(on_off_pin, INPUT_PULLUP);
   pinMode(engage_pin, INPUT_PULLUP);
   pinMode(full_pwr_pin, INPUT_PULLUP);
   pinMode(tc_pin, INPUT_PULLUP);

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

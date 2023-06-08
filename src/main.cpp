//main.cpp
// @nikunjparasar, @Th3Will, @rtz

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
const int on_off_pin = 11;
const int engage_pin = 10;
const int full_pwr_pin = 9;
const int brake_pin = 12;
const int pedal_pin = 24;

// DTI HV500 operating temps: -20C to 85C
// EMRAX 228HV WORKING TEMPS: The electric motor can operate in ambient
// temperatures between -40 to +60⁰C. The maximum
// motor temperature allowed as recorded by internal
// temperature sensor is 120⁰C
unordered_map<int, double> LIQUID_COOLING_FAN_CURVE = { 
   {0, 0.0},{1, 0},{2, 0},{3, 0},{4, 0}, {5, 0},{6, 1.2},{7, 1.4},{8, 1.6},{9, 1.8},
   {10, 2.0},{11, 2.2}, {12, 2.4},{13, 2.6}, {14, 2.8},{15, 3.0},{16, 3.2},{17, 3.4},
   {18, 3.6},{19, 3.8},{20, 4.0},{21, 4.2},{22, 4.4},{23, 4.6},{24, 4.8},{25, 5.0},
   {26, 5.2},{27, 5.4},{28, 5.6},{29, 5.8},{30, 6.0},{31, 6.2},{32, 6.4},{33, 6.6},
   {34, 6.8},{35, 7.0},{36, 7.2},{37, 7.4},{38, 7.6},{39, 7.8},{40, 8.0},{41, 8.2},
   {42, 8.4},{43, 8.6},{44, 8.8},{45, 9.0},{46, 9.2},{47, 9.4},{48, 9.6},{49, 9.8},
   {50, 10.0},{51, 10.2},{52, 10.4},{53, 10.6},{54, 10.8},{55, 11.0},{56, 11.2},
   {57, 11.4},{58, 11.6},{59, 11.8},{60, 12.0}
};
/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                  INTERRUPTS TRIGGER FUNCTIONS
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

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
volatile bool APPSBSPDViolation() {
   return s.drive_engage && (car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > VALUE_APPS_BSPD_THROTTLE && 
      (car.pedals.getBrakePressure1() > VALUE_MIN_BRAKE_PRESSURE || car.pedals.getBrakePressure2() > VALUE_MIN_BRAKE_PRESSURE);
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

   if(state != OFF){
      if(s.full_pwr){
         if(millis()%1000 < 500){
         led.setPixelColor(3, led.Color(0, 0, 0));
         led.show();
         }else{
         led.setPixelColor(3, led.Color(0, 0, 255/10));
         led.show();
         }
      }
      else{
         if(millis()%1000 < 500){
         led.setPixelColor(3, led.Color(0, 0, 0));
         led.show();
         }else{
         led.setPixelColor(3, led.Color(0, 255/10, 255/10));
         led.show();
         }
      }
   }
   s.ROTARY_TEST_ACCEL = analogRead(pedal_pin)/1023.0;

   //fan controller module
   
   double check_critical_temp = max(car.DTI.getInvTemp(), car.DTI.getMotorTemp());
   if(check_critical_temp > 60){
      car.fans.setFan1Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
      car.fans.setFan2Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
      car.fans.setFan3Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
      car.fans.setFan4Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);      
   }
   else{
      car.fans.setFan1Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
      car.fans.setFan2Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
      car.fans.setFan3Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
      car.fans.setFan4Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
   }
   


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

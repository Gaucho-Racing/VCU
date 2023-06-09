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

Switchboard s;
I_no_can_speak_flex car(true); 
const int on_off_pin = 11;
const int engage_pin = 10;
const int full_pwr_pin = 9;
const int brake_pin = 12;
const int pedal_pin_1 = 24;
const int pedal_pin_2 = 25;
const int brake_front = 18;
const int brake_rear = 19;

// DTI HV500 operating temps: -20C to 85C
// EMRAX 228HV WORKING TEMPS: The electric motor can operate in ambient
// temperatures between -40 to +60⁰C. The maximum
// motor temperature allowed as recorded by internal
// temperature sensor is 120⁰C
/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                  INTERRUPTS TRIGGER FUNCTIONS
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/


// volatile bool hardBrake() {
//    return s.drive_engage && car.pedals.getBrakePressure1() > VALUE_HARD_BRAKE_LIMIT || 
//       car.pedals.getBrakePressure2() > VALUE_HARD_BRAKE_LIMIT;
// }
// volatile bool accelUnresponsive() {
//    return s.drive_engage && (car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > VALUE_APPS_UNRESPONSIVE_MAX && 
//       car.DTI.getDCCurrent() <= VALUE_MIN_RESPONSIVE_CURRENT_MOTOR;
// } 
// volatile bool motorTempHigh() { return car.DTI.getMotorTemp() > VALUE_MOT_TEMP_MAX; }
// volatile bool CANFailure() { 
//    return (car.DTI.getAge() > MAX_CAN_DURATION || 
//       // car.IMD.getAge() > MAX_CAN_DURATION || 
//       car.sensors.getAge() > MAX_CAN_DURATION || 
//       car.pedals.getAge() > MAX_CAN_DURATION || 
//       car.charger.getAge() > MAX_CAN_DURATION || 
//       car.BMS.getAge() > MAX_CAN_DURATION);
// }
// volatile bool currentExceeds() { return car.DTI.getDCCurrent() > VALUE_DTI_CURRENT_THRESHOLD; }
// volatile bool GForceCrash() {
//    return sqrt(car.sensors.getLinAccelX()*car.sensors.getLinAccelX() +
//                            car.sensors.getLinAccelY()*car.sensors.getLinAccelY() +
//                            car.sensors.getLinAccelZ()*car.sensors.getLinAccelZ()) > VALUE_G_FORCE_LIMIT;
// }

volatile bool APPSImplausibility() {
   return abs(s.ACCEL_1 - 2*s.ACCEL_2) > 0.1;
}

volatile bool BSEImplausibility() {
   
}

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

bool flag = true;
float movingAverage(int arr[], int size, int newVal) {
   for(int i = 0; i < size-1; i++) {
      arr[i] = arr[i+1];
   }
   arr[size-1] = newVal;
   int sum = 0;
   for(int i = 0; i < size; i++) {
      sum += arr[i];
   }
   return float(sum);

}
int brake1[100] = {0};
int brake2[100] = {0};

/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                          MAIN LOOP
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

void loop() {
//   car.readData();
// analogReadResolution(12);
   if (state != OFF) {
      // if(hardBrake()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT4);}
      // if(accelUnresponsive()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT5);}
      // if(motorTempHigh()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT6);}
      // if(CANFailure()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT7);}
      // if(currentExceeds()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_0_15);}
      // if(GForceCrash()){NVIC_TRIGGER_IRQ(IRQ_GPIO2_16_31);}
      if(APPSImplausibility()) {
         car.sendDashError(97);
         sendToError(state, APPSImplausibility);
      }
      // if(BSEImplausibility()) {
      //    car.sendDashError(98);
      //    car.DTI.setRCurrent(0);
      // }
      // if(APPSBSPDViolation()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT3);}
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
   s.ACCEL_1 = analogRead(pedal_pin_1)/1023.0;
   s.ACCEL_2 = analogRead(pedal_pin_2)/1023.0;
   
   
   if(millis()%1000 < 500){
      // Serial.print("before: ");
      // Serial.println(analogRead(brake_front));
      if(flag){
         s.BRAKE_FRONT = movingAverage(brake1, 1000, analogRead(brake_front));
      } else {
         s.BRAKE_REAR = movingAverage(brake2, 1000, analogRead(brake_rear));
      }
      // Serial.print("after: ");
      // Serial.println(millis());
      flag = !flag;
   }
   if(state==OFF){
      car.fans.setFan1Voltage(0);
      car.fans.setFan2Voltage(0);
      car.fans.setFan3Voltage(0);
      car.fans.setFan4Voltage(0);
   }
   else{
      double check_critical_temp = max(car.DTI.getInvTemp(), car.DTI.getMotorTemp());
      if(check_critical_temp >=60 || s.full_pwr == 1){
         car.fans.setFan1Voltage(12);
         car.fans.setFan2Voltage(12);
         car.fans.setFan3Voltage(12);
         car.fans.setFan4Voltage(12);
      }
      else if(check_critical_temp < 60 ){
         car.fans.setFan1Voltage(9);
         car.fans.setFan2Voltage(9);
         car.fans.setFan3Voltage(9);
         car.fans.setFan4Voltage(9);
      }
      else if(check_critical_temp < 30){
         car.fans.setFan1Voltage(7);
         car.fans.setFan2Voltage(7);
         car.fans.setFan3Voltage(7);
         car.fans.setFan4Voltage(7);
      }
   }

   
   
   // if(check_critical_temp > 60){
   //    car.fans.setFan1Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
   //    car.fans.setFan2Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
   //    car.fans.setFan3Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
   //    car.fans.setFan4Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);      
   // }
   // else{
   //    car.fans.setFan1Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
   //    car.fans.setFan2Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
   //    car.fans.setFan3Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
   //    car.fans.setFan4Voltage(LIQUID_COOLING_FAN_CURVE[static_cast<int>(check_critical_temp)]);
   // }
   

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


/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                      HIGH PRIORITY INTERRUPT SERVICE ROUTINES 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/



// Interrupt handler for hard brake
// void HardBrake_ISR() {
//    // Can someone confirm the rule for this. 
//    // There's no rule for this. It's just a safety feature we decided on in case the car's out of control.
//    car.DTI.setRCurrent(0);
//    state = sendToError(state, &hardBrake);
// }
// Interrupt handler for unresponsive throttle
// void UnresponsiveThrottle_ISR() {
//    // Send Dash Warning
//    car.sendDashError(104);
//    state = sendToError(state, &accelUnresponsive);
// }
// Interrupt handler for motor temperature high
// void MotorTempHigh_ISR() {
//       car.sendDashError(105);
//       state = sendToError(state, &motorTempHigh);
   
// }
// Interrupt handler for no CAN signal
// void NoCAN_ISR() {
//    //TODO FIX
// }
// Interrupt handler for current too high
// void CurrentExceeds_ISR() {
//    car.sendDashError(106);
//    state = sendToError(state, &currentExceeds);
// }
// Interrupt handler for car crash
// void CarCrashed_ISR() {
//    // Dash Warning
//    car.sendDashError(108);
//    state = sendToError(state, &GForceCrash);
// }


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
   pinMode(pedal_pin_1, INPUT);
   pinMode(pedal_pin_2, INPUT);
   pinMode(brake_front, INPUT_PULLDOWN);
   pinMode(brake_rear, INPUT_PULLDOWN);

   //set beeper pin to output mode
   pinMode(3, OUTPUT);

  //-------SET STATE------------

   state = OFF;

  //------- ENABLE NVIC INTERRUPTS------

  // APPS/BSPD accelerator and brakes
//   attachInterruptVector(IRQ_GPIO1_INT3, &APPSBSPDCheck_ISR);
//   NVIC_ENABLE_IRQ(IRQ_GPIO1_INT3);
//   // Enable interrupts for hard brake 
//   attachInterruptVector(IRQ_GPIO1_INT4, &HardBrake_ISR);
//   NVIC_ENABLE_IRQ(IRQ_GPIO1_INT4);
//   // unresponsive throttle
//   attachInterruptVector(IRQ_GPIO1_INT5, &UnresponsiveThrottle_ISR);
//   NVIC_ENABLE_IRQ(IRQ_GPIO1_INT5);
//   // Enable interrupts for motor temperature high 
//   attachInterruptVector(IRQ_GPIO1_INT6, &MotorTempHigh_ISR);
//   NVIC_ENABLE_IRQ(IRQ_GPIO1_INT6);
//   // no CAN signal
//   attachInterruptVector(IRQ_GPIO1_INT7, &NoCAN_ISR);
//   NVIC_ENABLE_IRQ(IRQ_GPIO1_INT7);
//   // Enable interrupts for current too high 
//   attachInterruptVector(IRQ_GPIO1_0_15, &CurrentExceeds_ISR);
//   NVIC_ENABLE_IRQ(IRQ_GPIO1_0_15);
//   // car crash
//   attachInterruptVector(IRQ_GPIO2_16_31, &CarCrashed_ISR);
//   NVIC_ENABLE_IRQ(IRQ_GPIO2_16_31);
}

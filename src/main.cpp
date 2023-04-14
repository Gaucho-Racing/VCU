#include <Arduino.h>
#include <imxrt.h>
#include "utility.h"
#include "main.h"
#include "error.h"
#include "constants.h"
#include "stubs.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

// enum States {OFF, ON, ON_READY, DRIVE, CHARGE_PRECHARGE, CHARGE_CHARGING, CHARGE_FULL, FATAL_ERROR};

struct CircularBuffer {
    CircularBuffer(int size) : m_size(size), m_buffer(size), m_head(0) {}
    void addMessage(std::string message) {
        m_buffer[m_head] = message;
        m_head = (m_head + 1) % m_size;
    }
    void printMessages() {
        int i = m_head;
        for (int j = 0; j < m_size; j++) {
            if (!m_buffer[i].empty()) {
                std::cout << m_buffer[i] << std::endl;
            }
            i = (i + 1) % m_size;
        }
    }
    int m_size;
    std::vector<std::string> m_buffer;
    int m_head;
};

volatile States state;
//stores
volatile States prevState; 
volatile bool sendToDash = false;
volatile bool (*errorCheck)(void); 
//message to send to dash

CircularBuffer errorBuffer(10);
I_no_can_speak_flex car(true);

volatile bool batteryTempHigh(){ return car.BMS.getTemp() > VALUE_BAT_TEMP_MAX; }
  volatile bool batteryTempLow(){return car.BMS.getTemp() < VALUE_BAT_TEMP_MIN;}
  volatile bool noCurrent(){return car.DTI.getDCCurrent() < VALUE_MIN_CURRENT_THRESHOLD; }
  volatile bool APPSBSPDViolation(){return car.pedals.getAPPS() > VALUE_APPS_BSPD_THROTTLE && (car.pedals.getBrakePressure1() > VALUE_MIN_BRAKE_PRESSURE || car.pedals.getBrakePressure2() > VALUE_MIN_BRAKE_PRESSURE);}
  volatile bool hardBrake(){return car.pedals.getBrakePressure1() > VALUE_HARD_BRAKE_LIMIT || car.pedals.getBrakePressure2() > VALUE_HARD_BRAKE_LIMIT;}
  volatile bool accelUnresponsive(){return car.pedals.getAPPS() > VALUE_APPS_UNRESPONSIVE_MAX && car.DTI.getDCCurrent() < VALUE_MIN_RESPONSIVE_CURRENT_MOTOR;} //TODO LATER FIX THIS SHIT IT IS PROB WRONG
  volatile bool motorTempHigh(){return car.DTI.getMotorTemp() > VALUE_MOT_TEMP_MAX;}
  volatile bool CANFailure(){return !car.canSend;  }// IDK if this is right but seems right
  volatile bool currentExceeds(){ return car.DTI.getDCCurrent()> VALUE_DTI_CURRENT_THRESHOLD; }
  volatile bool systemError(){ return true; } //TODO: FIX THIS ACTUAL VALUE
  volatile bool IMDFault(){ return car.IMD.getHardware_Error();}
  volatile bool GForceCrash(){
      return sqrt(car.sensors.getLinAccelX()*car.sensors.getLinAccelX() +
                            car.sensors.getLinAccelY()*car.sensors.getLinAccelY() +
                              car.sensors.getLinAccelZ()*car.sensors.getLinAccelZ()) > VALUE_G_FORCE_LIMIT;
   }

States sendToError(volatile States currentState, volatile bool (*erFunc)(void)){
   errorCheck = erFunc; 
   prevState = currentState; 
   return ERROR;
}

void loop() {



  if(batteryTempHigh()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);}
  if(batteryTempLow()){NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT1);}
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
      case ERROR:
         state = error(car, prevState, errorCheck);
         break;
   }

   // print out the errors from the buffer
   errorBuffer.printMessages();
}


//NOTE: 
// might want to think about how we are going to restore certain settings once there isnt an error anymore. 




// Interrupt handler for battery temperature high
void BatteryTempHigh_ISR() {
   // Disallow Charging
   // Send Message to Dash
   errorBuffer.addMessage(ERROR_HIGH_CELL_TEMP);
   // Limit Motor Current Draw
   car.DTI.setMaxCurrent(VALUE_OVERHEAT_CURRENT_LIMIT);
   // Shut down car if Very high
   if(car.BMS.getTemp() > VALUE_CRITICAL_BATTERY_TEMP_HIGH){
      errorBuffer.addMessage(ERROR_CRITICAL_CELL_TEMP);
      state = sendToError(state, &batteryTempHigh);
   }
}

// Interrupt handler for battery temperature low
void BatteryTempLow_ISR() {
   // Send Message to Dash
   errorBuffer.addMessage(ERROR_LOW_CELL_TEMP);
   state = sendToError(state, &batteryTempLow);

}

// Interrupt handler for no current
void NoCurrent_ISR() {
   // Dashboard Warning Send
   errorBuffer.addMessage(ERROR_NO_CURRENT_DTI);
   state = sendToError(state, &noCurrent);
}

// Interrupt handler for accelerator and brakes
void APPSBSPDCheck_ISR() {
   // Disengage motor
   car.DTI.setCurrent(0);
   // Send message to Dash
   errorBuffer.addMessage(ERROR_APPS_BSPD);
   
}

// Interrupt handler for hard brake
void HardBrake_ISR() {
   // Disengage motor
   car.DTI.setRCurrent(0);
   state = sendToError(state, &hardBrake);
}

// Interrupt handler for unresponsive throttle
void UnresponsiveThrottle_ISR() {
   // Send Dash Warning
   errorBuffer.addMessage(ERROR_THROTTLE_SIGNAL);
   state = sendToError(state, &accelUnresponsive);
}

// Interrupt handler for motor temperature high
void MotorTempHigh_ISR() {
   // Give dash warning
   errorBuffer.addMessage(ERROR_MOTOR_TEMP);
   // Limit Motor Current draw
   car.DTI.setMaxCurrent(VALUE_MAX_CURRENT_DRAW_HIGH_MOTOR);
   // IF very high, stop car
   if(car.DTI.getMotorTemp() > VALUE_CRITICAL_MOTOR_TEMP){
      errorBuffer.addMessage(ERROR_CRITICAL_MOTOR_TEMP);
      car.DTI.setCurrent(0);
      state = sendToError(state, &motorTempHigh);
   }
}

// Interrupt handler for no CAN signal
void NoCAN_ISR() {
   // IDK Shut down?
}

// Interrupt handler for current too high
void CurrentExceeds_ISR() {
   errorBuffer.addMessage("CRITICAL: CURRENT LIMIT EXCEEDED");
   state = sendToError(state, &currentExceeds);
}

// Interrupt handler for system error
void SystemError_ISR() {
   cout << "TEST";
   state = sendToError(state, &systemError);
}

// Interrupt handler for insulation fault
void IMDFault_ISR() {
   // Give dash a critical warning
   errorBuffer.addMessage(ERROR_IMD_FAULT);
   // Shut Down carß
   car.DTI.setCurrent(0);
   state = sendToError(state, &IMDFault);

}

// Interrupt handler for car crash
void CarCrashed_ISR() {
   // Dash Warning
   errorBuffer.addMessage("Rip.");

   // Disengage motor
   car.DTI.setCurrent(0);
   // Shut down car
   state = sendToError(state, &GForceCrash);

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
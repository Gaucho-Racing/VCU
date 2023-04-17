#include "main.h"
#include "error.h"
#include "constants.h"
#include <iostream>

States sendToError(volatile States currentState, volatile bool (*erFunc)(void)) {
   errorCheck = erFunc; 
   prevState = currentState; 
   return ERROR;
}

States error(I_no_can_speak_flex &car, States prevStates, volatile bool (*erCheck)(void)) {
    car.DTI.setDriveEnable(0);
    car.DTI.setCurrent(0);
    
    if(erCheck()){
        return ERROR;
    } else {
        return prevStates;
    }
}

void sendDashError(int code) {
    using namespace std;
    /*
        car.sendDashError(int code);
    */
    cout << code << " ";
}

void TS_WARN_Check(I_no_can_speak_flex &car) {
   // TIRE PRESSURES AND TEMPERATURES

   //51: Front-right tire tempaerture too high
   if (car.sensors.getFRtemp1() > MAX_TIRE_TEMP_C) sendDashError(51);
   //52: Front-right tire temperature too low
   if (car.sensors.getFRtemp1() < MIN_TIRE_TEMP_C) sendDashError(52);
   //53: Front-right brake temperature too high
   if (car.sensors.getFRtemp2() > MAX_BRAKE_TEMP_C) sendDashError(53);
   //54: Front-right brake temperature too low
   if (car.sensors.getFRtemp2() <= MIN_BRAKE_TEMP_C) sendDashError(54);
   //55: Overengaged suspension
   if (car.sensors.getFRtravel() > SUSPENSION_MAX) sendDashError(55);
   //56: Underengaged suspension
   if (car.sensors.getFRtravel() < SUSPENSION_MIN) sendDashError(56);
   //58: High Front-right tire pressure
   if (car.sensors.getFRpsi() > MAX_TIRE_PSI) sendDashError(58);
   //59: Low Front-right tire pressure
   if (car.sensors.getFRpsi() < MIN_TIRE_PSI) sendDashError(59);

   //61: Front-left tire tempaerture too high
   if (car.sensors.getFLtemp1() > MAX_TIRE_TEMP_C) sendDashError(61);
   //62: Front-left tire temperature too low
   if (car.sensors.getFLtemp1() < MIN_TIRE_TEMP_C) sendDashError(62);
   //63: Front-left brake temperature too high
   if (car.sensors.getFLtemp2() > MAX_BRAKE_TEMP_C) sendDashError(63);
   //64: Front-left brake temperature too low
   if (car.sensors.getFLtemp2() <= MIN_BRAKE_TEMP_C) sendDashError(64);
   // 65: Overengaged suspension
   if (car.sensors.getFLtravel() > SUSPENSION_MAX)sendDashError(65);
   // 66: Underengaged suspension
   if (car.sensors.getFLtravel() < SUSPENSION_MIN) sendDashError(66);
   //68: High Front-left tire pressure
   if (car.sensors.getFLpsi() > MAX_TIRE_PSI) sendDashError(68);
   //69: Low Front-left tire pressure
   if (car.sensors.getFLpsi() < MIN_TIRE_PSI) sendDashError(69);

   //71: Rear-right tire tempaerture too high
   if (car.sensors.getRRtemp1() > MAX_TIRE_TEMP_C) sendDashError(71);
   //72: Rear-right tire temperature too low
   if (car.sensors.getRRtemp1() < MIN_TIRE_TEMP_C) sendDashError(72);
   //73: Rear-right brake temperature too high
   if (car.sensors.getRRtemp2() > MAX_BRAKE_TEMP_C) sendDashError(73);
   //74: Rear-right brake temperature too low
   if (car.sensors.getRRtemp2() <= MIN_BRAKE_TEMP_C) sendDashError(74);
   // 75: Overengaged suspension
   if (car.sensors.getRRtravel() > SUSPENSION_MAX) sendDashError(75);
   // 76: Underengaged suspension
   if (car.sensors.getRRtravel() < SUSPENSION_MIN) sendDashError(76);
   //78: High Rear-right tire pressure
   if (car.sensors.getRRpsi() > MAX_TIRE_PSI) sendDashError(78);
   //79: Low Rear-right tire presure
   if (car.sensors.getRRpsi() < MIN_TIRE_PSI) sendDashError(79);
   
   //81: Rear-left tire tempaerture too high
   if (car.sensors.getRLtemp1() > MAX_TIRE_TEMP_C) sendDashError(81);
   //82: Rear-left tire temperature too low
   if (car.sensors.getRLtemp1() < MIN_TIRE_TEMP_C) sendDashError(82);
   //83: Rear-left brake temperature too high
   if (car.sensors.getRLtemp2() > MAX_BRAKE_TEMP_C) sendDashError(83);
   //84: Rear-left brake temperature too low
   if (car.sensors.getRLtemp2() <= MIN_BRAKE_TEMP_C) sendDashError(84);
   //85: Overengaged suspension
   if (car.sensors.getRLtravel() > SUSPENSION_MAX) sendDashError(85);
   //86: Underengaged suspension
   if (car.sensors.getRLtravel() < SUSPENSION_MIN) sendDashError(86);
   //88: High Rear-left tire pressure
   if (car.sensors.getRLpsi() > MAX_TIRE_PSI) sendDashError(88);
   //89: Low Rear-left tire presure
   if (car.sensors.getRLpsi() < MIN_TIRE_PSI) sendDashError(89);
}

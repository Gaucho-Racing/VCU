#include "main.h"
#include "error.h"

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

void TS_WARN_Check(I_no_can_speak_flex &car) {
   // TIRE PRESSURES AND TEMPERATURES

   //51: Front-right tire tempaerture too high
   if (car.sensors.getFRtemp1() > 90) car.sendDashError(51);
   //52: Front-right tire temperature too low
   if (car.sensors.getFRtemp1() < 10) car.sendDashError(52);
   //53: Front-right brake temperature too high
   if (car.sensors.getFRtemp2() > 450) car.sendDashError(53);
   //54: Front-right brake temperature too low
   if (car.sensors.getFRtemp2() <= 0) car.sendDashError(54);
   //55: Overengaged suspension
   if (car.sensors.getFRtravel() > 1) car.sendDashError(55);
   //56: Underengaged suspension
   if (car.sensors.getFRtravel() < -1) car.sendDashError(56);
   //58: High Front-right tire pressure
   if (car.sensors.getFRpsi() > 50) car.sendDashError(58);
   //59: Low Front-right tire pressure
   if (car.sensors.getFRpsi() < 24) car.sendDashError(59);

   //61: Front-left tire tempaerture too high
   if (car.sensors.getFLtemp1() > 90) car.sendDashError(61);
   //62: Front-left tire temperature too low
   if (car.sensors.getFLtemp1() < 10) car.sendDashError(62);
   //63: Front-left brake temperature too high
   if (car.sensors.getFLtemp2() > 450) car.sendDashError(63);
   //64: Front-left brake temperature too low
   if (car.sensors.getFLtemp2() <= 0) car.sendDashError(64);
   // 65: Overengaged suspension
   if (car.sensors.getFLtravel() > 1)car.sendDashError(65);
   // 66: Underengaged suspension
   if (car.sensors.getFLtravel() < -1) car.sendDashError(66);
   //68: High Front-left tire pressure
   if (car.sensors.getFLpsi() > 50) car.sendDashError(68);
   //69: Low Front-left tire pressure
   if (car.sensors.getFLpsi() < 24) car.sendDashError(69);

   //71: Rear-right tire tempaerture too high
   if (car.sensors.getRRtemp1() > 90) car.sendDashError(71);
   //72: Rear-right tire temperature too low
   if (car.sensors.getRRtemp1() < 10) car.sendDashError(72);
   //73: Rear-right brake temperature too high
   if (car.sensors.getRRtemp2() > 450) car.sendDashError(73);
   //74: Rear-right brake temperature too low
   if (car.sensors.getRRtemp2() <= 0) car.sendDashError(74);
   // 75: Overengaged suspension
   if (car.sensors.getRRtravel() > 1) car.sendDashError(75);
   // 76: Underengaged suspension
   if (car.sensors.getRRtravel() < -1) car.sendDashError(76);
   //78: High Rear-right tire pressure
   if (car.sensors.getRRpsi() > 50) car.sendDashError(78);
   //79: Low Rear-right tire presure
   if (car.sensors.getRRpsi() < 24) car.sendDashError(79);
   
   //81: Rear-left tire tempaerture too high
   if (car.sensors.getRLtemp1() > 90) car.sendDashError(81);
   //82: Rear-left tire temperature too low
   if (car.sensors.getRLtemp1() < 10) car.sendDashError(82);
   //83: Rear-left brake temperature too high
   if (car.sensors.getRLtemp2() > 450) car.sendDashError(83);
   //84: Rear-left brake temperature too low
   if (car.sensors.getRLtemp2() <= 0) car.sendDashError(84);
   //85: Overengaged suspension
   if (car.sensors.getRLtravel() > 1) car.sendDashError(85);
   //86: Underengaged suspension
   if (car.sensors.getRLtravel() < -1) car.sendDashError(86);
   //88: High Rear-left tire pressure
   if (car.sensors.getRLpsi() > 50) car.sendDashError(88);
   //89: Low Rear-left tire presure
   if (car.sensors.getRLpsi() < 24) car.sendDashError(89);

}

//onOffUtility.cpp
// @yarwinliu, @rt.z, 03122023

#include "main.h"
#include "onOffUtility.h"

//returns true if there is current running to the motor
bool onPressed(I_no_can_speak_flex &car) {  
    if(car.DTI.getDCCurrent() > 0) return true;
    else return false;
}

int systemsCheck(I_no_can_speak_flex &car) {
    //TODO - insert acutal code
    //make sure the data works
    //outputs error message depending on what the error is

    //1: Unable to revieve CAN packets
   if ((car.DTI.getAge()) > 1000) return 1;
   if ((car.IMD.getAge()) > 1000) return 1;
   if ((car.sensors.getAge()) > 1000) return 1;
   if ((car.pedals.getAge()) > 1000) return 1;
   if ((car.charger.getAge()) > 1000) return 1;
   if ((car.BMS.getAge()) > 1000) return 1;

   //2 - 11: Motor faults, refer to CAN documentation
   int i = 0;
   if ((i = car.DTI.getFaults()) != 0) return i + 1;

   //12: Motor is running when not supposed to
   if (car.DTI.getERPM() != 0 || car.DTI.getDuty() != 0 || car.DTI.getACCurrent() != 0) return 12;

   //-1: Wait... the thing isn't actually on
   if (car.DTI.getDCCurrent() <= 0) return -1;

   //13: Drive disabled
   if (car.DTI.getDriveEnable() != 1) return 13;

   //14: Capacitor Temperature Limit Disabled
   if (!car.DTI.getCapTempLim() != 1) return 14;

   //16: IGBT Accel. Limit Disabled
   if (!car.DTI.getIgbtAccelTempLim() != 1) return 16;

   //17: IGBT Temp. Limit Disabled 
   if (!car.DTI.getIgbtTempLim() != 1) return 17;

   //18: Motor accel temp. limit disabled
   if (!car.DTI.getVoltInLim() != 1) return 18;

   //etc. (im too lazy to type them all out)
   if (!car.DTI.getMotorAccelTempLim() != 1) return 19;
   if (!car.DTI.getMotorTempLim() != 1) return 20;
   if (!car.DTI.getRPMMinLimit() != 1) return 21;
   if (!car.DTI.getRPMMaxLimit() != 1) return 22;
   if (!car.DTI.getPowerLimit() != 1) return 23;

   //other systems check, if needed
   //30: Overexcessive current from battery
   if (car.BMS.getCurrent() < -500) return 30;

   //31: Charging while driving
   if (car.BMS.getCurrent() >= 0) return 31;

   //32: Low Voltage
   if (car.BMS.getVoltage() < 5) return 32;

   //33: Overexcessive Voltage
   if (car.BMS.getVoltage() > 240) return 33;

   //34: Low car.BMS
   if (car.BMS.getChargeState() < 20) return 34;

   //35: car.BMS Overcharge
   if (car.BMS.getChargeState() > 100) return 35;

   //36: car.BMS Health Low
   if (car.BMS.getHealth() < 80) return 36;

   //37: Faulty car.BMS Health Data
   if (car.BMS.getHealth() > 100) return 37;

   //38: High car.BMS Temperature
   if (car.BMS.getTemp() > 60) return 38;

   //39: Low car.BMS Temperature
   if (car.BMS.getTemp() < 0) return 39;

   //40: Isolation failure/warning (not sure what this is)
   if (car.IMD.getIsolation() != 1) return 40;
   
   //41-42: Isolation warning/fault. See can documentation.
   if ((i = car.IMD.getIsolationStates()) == 10 || i == 11) return i + 31;

   //43: Isolation Hardware error
   if (car.IMD.getHardware_Error() != 0) return 43;

   //44: Electrostatic potential energy exceeds 0.2J
   if (car.IMD.getTouch_energy_fault() != 0) return 44;

   //45: Exitation pulse not opertional
   if (car.IMD.getExc_off() != 0) return 45;

   //46: High car.BMS Voltage / No max_battery_working_voltage set
   if (car.IMD.getHigh_Battery_Voltage() != 0) return 46;

   //47: Low car.BMS Voltage / car.BMS Disconnect
   if (car.IMD.getLow_Battery_Voltage() != 0) return 47;

   //50: car's moving!!
   if (car.sensors.getLinAccelX() != 0 || car.sensors.getLinAccelY() != 0 || car.sensors.getLinAccelZ() != 0) return 50;
   if (car.sensors.getAngVeloX() != 0 || car.sensors.getAngVeloY() != 0 || car.sensors.getAngVeloZ() != 0) return 50;

   //temperatures are assumed to be in centrigrade (@(somebody that's not rt.z) do the conversions if they turn out to be in the whatever random other temperature unit everyone else uses)
   //51: Front-right tire tempaerture too high
   if (car.sensors.getFRtemp1() > 90) return 51;

   //52: Front-right tire temperature too low
   if (car.sensors.getFRtemp1() < 10) return 52;
   
   //53: Front-right brake temperature too high
   if (car.sensors.getFRtemp2() > 450) return 53;

   //54: Front-right brake temperature too low
   if (car.sensors.getFRtemp2() <= 0) return 54;

   //55: Overengaged suspension
   //if (car.sensors.getFRtravel() > 1) return 55;
   //56: Underengaged suspension
   //if (Sesnors.getFRtravel() < -1) return 56;

   //57: Front-right wheel is moving
   if (car.sensors.getFRspeed() > 0) return 57;

   //58: High Front-right tire pressure
   if (car.sensors.getFRpsi() > 50) return 58;

   //59: Low Front-right tire pressure
   if (car.sensors.getFRpsi() < 24) return 59;


   //61: Front-left tire tempaerture too high
   if (car.sensors.getFLtemp1() > 90) return 61;

   //62: Front-left tire temperature too low
   if (car.sensors.getFLtemp1() < 10) return 62;
   
   //63: Front-left brake temperature too high
   if (car.sensors.getFLtemp2() > 450) return 63;

   //64: Front-left brake temperature too low
   if (car.sensors.getFLtemp2() <= 0) return 64;

   //65: Overengaged suspension
   //if (car.sensors.getFLtravel() > 1) return 65;
   //66: Underengaged suspension
   //if (Sesnors.getFLtravel() < -1) return 66;

   //67: Front-left wheel is moving
   if (car.sensors.getFLspeed() > 0) return 67;

   //68: High Front-left tire pressure
   if (car.sensors.getFLpsi() > 50) return 68;

   //69: Low Front-left tire pressure
   if (car.sensors.getFLpsi() < 24) return 69;


   //71: Rear-right tire tempaerture too high
   if (car.sensors.getRRtemp1() > 90) return 71;

   //72: Rear-right tire temperature too low
   if (car.sensors.getRRtemp1() < 10) return 72;
   
   //73: Rear-right brake temperature too high
   if (car.sensors.getRRtemp2() > 450) return 73;

   //74: Rear-right brake temperature too low
   if (car.sensors.getRRtemp2() <= 0) return 74;

   //75: Overengaged suspension
   //if (car.sensors.getRRtravel() > 1) return 75;
   //76: Underengaged suspension
   //if (Sesnors.getRRtravel() < -1) return 76;

   //77: Rear-right wheel is moving
   if (car.sensors.getRRspeed() > 0) return 77;

   //78: High Rear-right tire pressure
   if (car.sensors.getRRpsi() > 50) return 78;

   //79: Low Rear-right tire presure
   if (car.sensors.getRRpsi() < 24) return 79;


   //81: Rear-left tire tempaerture too high
   if (car.sensors.getRLtemp1() > 90) return 81;

   //82: Rear-left tire temperature too low
   if (car.sensors.getRLtemp1() < 10) return 82;
   
   //83: Rear-left brake temperature too high
   if (car.sensors.getRLtemp2() > 450) return 83;

   //84: Rear-left brake temperature too low
   if (car.sensors.getRLtemp2() <= 0) return 84;

   //85: Overengaged suspension
   //if (car.sensors.getRLtravel() > 1) return 85;
   //86: Underengaged suspension
   //if (Sesnors.getRLtravel() < -1) return 86;

   //87: Rear-left wheel is moving
   if (car.sensors.getRLspeed() > 0) return 87;

   //88: High Rear-left tire pressure
   if (car.sensors.getRLpsi() > 50) return 88;

   //89: Low Rear-left tire presure
   if (car.sensors.getRLpsi() < 24) return 89;

   //91: Accelerator engaged
   if (car.pedals.getAPPS() > 0) return 91;
   
   //92: Brakes not engaged upon startup
   if (car.pedals.getBrakePressure1() != 0 || car.pedals.getBrakePressure2() != 0) return 92;

   return 0;
}

bool driveEngaged(I_no_can_speak_flex &car) {
    //TODO: find how to get dash signals from the CAN
    return false;
}

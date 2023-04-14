//onOffUtility.cpp
// @yarwinliu, @rt.z, 03122023

#include "main.h"
#include "onOffUtility.h"

//returns true if there is current running to the motor
bool onPressed(I_no_can_speak_flex &car) {  
    if(car.DTI.getDCCurrent() > 0) return true;
    else return false;
}

bool* systemsCheck(I_no_can_speak_flex &car) {
    static bool errors[100];
    for (int i = 0; i < 100; i++) errors[i] = 0;

    //TODO - insert acutal code
    //make sure the data works
    //outputs error message depending on what the error is

    //1: Unable to revieve CAN packets
   if ((car.DTI.getAge()) > 1000) errors[1] = true;
   if ((car.IMD.getAge()) > 1000) errors[1] = true;
   if ((car.sensors.getAge()) > 1000) errors[1] = true;
   if ((car.pedals.getAge()) > 1000) errors[1] = true;
   if ((car.charger.getAge()) > 1000) errors[1] = true;
   if ((car.BMS.getAge()) > 1000) errors[1] = true;

   //2 - 11: Motor faults, refer to CAN documentation
   int i = 0;
   if ((i = car.DTI.getFaults()) != 0) errors[i + 1] = true;

   //12: Motor is running when not supposed to
   if (car.DTI.getERPM() != 0 || car.DTI.getDuty() != 0 || car.DTI.getACCurrent() != 0) errors[12] = true;

   //-1: Wait... the thing isn't actually on
   if (car.DTI.getDCCurrent() <= 0) errors[0] = true;

   //13: Drive disabled
   if (car.DTI.getDriveEnable() != 1) errors[13] = true;

   //14: Capacitor Temperature Limit Disabled
   if (!car.DTI.getCapTempLim() != 1) errors[14] = true;

   //16: IGBT Accel. Limit Disabled
   if (!car.DTI.getIgbtAccelTempLim() != 1) errors[16] = true;

   //17: IGBT Temp. Limit Disabled 
   if (!car.DTI.getIgbtTempLim() != 1) errors[17] = true;

   //18: Motor accel temp. limit disabled
   if (!car.DTI.getVoltInLim() != 1) errors[18] = true;

   //etc. (im too lazy to type them all out)
   if (!car.DTI.getMotorAccelTempLim() != 1) errors[19] = true;
   if (!car.DTI.getMotorTempLim() != 1) errors[20] = true;
   if (!car.DTI.getRPMMinLimit() != 1) errors[21] = true;
   if (!car.DTI.getRPMMaxLimit() != 1) errors[22] = true;
   if (!car.DTI.getPowerLimit() != 1) errors[23] = true;

   //other systems check, if needed
   //30: Overexcessive current from battery
   if (car.BMS.getCurrent() < -500) errors[30] = true;

   //31: Charging while driving
   if (car.BMS.getCurrent() >= 0) errors[31] = true;

   //32: Low Voltage
   if (car.BMS.getVoltage() < 5) errors[32] = true;

   //33: Overexcessive Voltage
   if (car.BMS.getVoltage() > 240) errors[33] = true;

   //34: Low car.BMS
   if (car.BMS.getChargeState() < 20) errors[34] = true;

   //35: car.BMS Overcharge
   if (car.BMS.getChargeState() > 100) errors[35] = true;

   //36: car.BMS Health Low
   if (car.BMS.getHealth() < 80) errors[36] = true;

   //37: Faulty car.BMS Health Data
   if (car.BMS.getHealth() > 100) errors[37] = true;

   //38: High car.BMS Temperature
   if (car.BMS.getTemp() > 60) errors[38] = true;

   //39: Low car.BMS Temperature
   if (car.BMS.getTemp() < 0) errors[39] = true;

   //40: Isolation failure/warning (not sure what this is)
   if (car.IMD.getIsolation() != 1) errors[40] = true;
   
   //41-42: Isolation warning/fault. See can documentation.
   if ((i = car.IMD.getIsolationStates()) == 10 || i == 11) errors[i + 31] = true;

   //43: Isolation Hardware error
   if (car.IMD.getHardware_Error() != 0) errors[43] = true;

   //44: Electrostatic potential energy exceeds 0.2J
   if (car.IMD.getTouch_energy_fault() != 0) errors[44] = true;

   //45: Exitation pulse not opertional
   if (car.IMD.getExc_off() != 0) errors[45] = true;

   //46: High car.BMS Voltage / No max_battery_working_voltage set
   if (car.IMD.getHigh_Battery_Voltage() != 0) errors[46] = true;

   //47: Low car.BMS Voltage / car.BMS Disconnect
   if (car.IMD.getLow_Battery_Voltage() != 0) errors[47] = true;

   //50: car's moving!!
   if (car.sensors.getLinAccelX() != 0 || car.sensors.getLinAccelY() != 0 || car.sensors.getLinAccelZ() != 0) errors[50] = true;
   if (car.sensors.getAngVeloX() != 0 || car.sensors.getAngVeloY() != 0 || car.sensors.getAngVeloZ() != 0) errors[50] = true;

   //temperatures are assumed to be in centrigrade (@(somebody that's not rt.z) do the conversions if they turn out to be in the whatever random other temperature unit everyone else uses)
   //51: Front-right tire tempaerture too high
   if (car.sensors.getFRtemp1() > 90) errors[51] = true;

   //52: Front-right tire temperature too low
   if (car.sensors.getFRtemp1() < 10) errors[52] = true;
   
   //53: Front-right brake temperature too high
   if (car.sensors.getFRtemp2() > 450) errors[53] = true;

   //54: Front-right brake temperature too low
   if (car.sensors.getFRtemp2() <= 0) errors[54] = true;

   //55: Overengaged suspension
   //if (car.sensors.getFRtravel() > 1) errors[55] = true;
   //56: Underengaged suspension
   //if (Sesnors.getFRtravel() < -1) errors[56] = true;

   //57: Front-right wheel is moving
   if (car.sensors.getFRspeed() > 0) errors[57] = true;

   //58: High Front-right tire pressure
   if (car.sensors.getFRpsi() > 50) errors[58] = true;

   //59: Low Front-right tire pressure
   if (car.sensors.getFRpsi() < 24) errors[59] = true;


   //61: Front-left tire tempaerture too high
   if (car.sensors.getFLtemp1() > 90) errors[61] = true;

   //62: Front-left tire temperature too low
   if (car.sensors.getFLtemp1() < 10) errors[62] = true;
   
   //63: Front-left brake temperature too high
   if (car.sensors.getFLtemp2() > 450) errors[63] = true;

   //64: Front-left brake temperature too low
   if (car.sensors.getFLtemp2() <= 0) errors[64] = true;

   //65: Overengaged suspension
   //if (car.sensors.getFLtravel() > 1) errors[65] = true;
   //66: Underengaged suspension
   //if (Sesnors.getFLtravel() < -1) errors[66] = true;

   //67: Front-left wheel is moving
   if (car.sensors.getFLspeed() > 0) errors[67] = true;

   //68: High Front-left tire pressure
   if (car.sensors.getFLpsi() > 50) errors[68] = true;

   //69: Low Front-left tire pressure
   if (car.sensors.getFLpsi() < 24) errors[69] = true;


   //71: Rear-right tire tempaerture too high
   if (car.sensors.getRRtemp1() > 90) errors[71] = true;

   //72: Rear-right tire temperature too low
   if (car.sensors.getRRtemp1() < 10) errors[72] = true;
   
   //73: Rear-right brake temperature too high
   if (car.sensors.getRRtemp2() > 450) errors[73] = true;

   //74: Rear-right brake temperature too low
   if (car.sensors.getRRtemp2() <= 0) errors[74] = true;

   //75: Overengaged suspension
   //if (car.sensors.getRRtravel() > 1) errors[75] = true;
   //76: Underengaged suspension
   //if (Sesnors.getRRtravel() < -1) errors[76] = true;

   //77: Rear-right wheel is moving
   if (car.sensors.getRRspeed() > 0) errors[77] = true;

   //78: High Rear-right tire pressure
   if (car.sensors.getRRpsi() > 50) errors[78] = true;

   //79: Low Rear-right tire presure
   if (car.sensors.getRRpsi() < 24) errors[79] = true;


   //81: Rear-left tire tempaerture too high
   if (car.sensors.getRLtemp1() > 90) errors[81] = true;

   //82: Rear-left tire temperature too low
   if (car.sensors.getRLtemp1() < 10) errors[82] = true;
   
   //83: Rear-left brake temperature too high
   if (car.sensors.getRLtemp2() > 450) errors[83] = true;

   //84: Rear-left brake temperature too low
   if (car.sensors.getRLtemp2() <= 0) errors[84] = true;

   //85: Overengaged suspension
   //if (car.sensors.getRLtravel() > 1) errors[85] = true;
   //86: Underengaged suspension
   //if (Sesnors.getRLtravel() < -1) errors[86] = true;

   //87: Rear-left wheel is moving
   if (car.sensors.getRLspeed() > 0) errors[87] = true;

   //88: High Rear-left tire pressure
   if (car.sensors.getRLpsi() > 50) errors[88] = true;

   //89: Low Rear-left tire presure
   if (car.sensors.getRLpsi() < 24) errors[89] = true;

   //91: Accelerator engaged
   if (car.pedals.getAPPS() > 0) errors[91] = true;
   
   //92: Brakes not engaged upon startup
   if (car.pedals.getBrakePressure1() != 0 || car.pedals.getBrakePressure2() != 0) errors[92] = true;

   return errors;
}

bool driveEngaged(I_no_can_speak_flex &car) {
    //TODO: find how to get dash signals from the CAN
    return false;
}

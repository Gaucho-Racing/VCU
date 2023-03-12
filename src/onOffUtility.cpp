//onOffUtility.cpp
// @yarwinliu, @rt.z, 03122023

#include "Nodes.h"

//returns true if there is current running to the motor
bool onPressed(){ 
    if(Inverter.getDCCurrent() > 0) return true;
    else return false;
}

int systemsCheck(){
    //TODO - insert acutal code
    //make sure the data works
    //outputs error message depending on what the error is

    //1: Unable to revieve CAN packets
   if ((Inverter.getAge()) > 1000) return 1;
   if ((Isolation_Monitor.getAge()) > 1000) return 1;
   if ((Sensors.getAge()) > 1000) return 1;
   if ((Sensors_Pedals.getAge()) > 1000) return 1;
   if ((Charger.getAge()) > 1000) return 1;
   if ((Battery.getAge()) > 1000) return 1;

   //2 - 11: Motor faults, refer to CAN documentation
   int i = 0;
   if ((i = Inverter.getFaults()) != 0) return i + 1;

   //12: Motor is running when not supposed to
   if (Inverter.ERPM() != 0 || Inverter.dutyCycle() != 0 || Inverter.getACCurrent() != 0) return 12;

   //-1: Wait... the thing isn't actually on
   if (Inverter.getDCCurrent() <= 0) return -1;

   //13: Drive disabled
   if (Inverter.getDriveEnable() != 1) return 13;

   //14: Capacitor Temperature Limit Disabled
   if (!Inverter.CapTempLim() != 1) return 14;

   //16: IGBT Accel. Limit Disabled
   if (!Inverter.getIgbtAccelTempLim() != 1) return 16;

   //17: IGBT Temp. Limit Disabled 
   if (!Inverter.getIgbtTempLim() != 1) return 17;

   //18: Motor accel temp. limit disabled
   if (!Inverter.getVoltInLim() != 1) return 18;

   //etc. (im too lazy to type them all out)
   if (!Inverter.getMotorAccelTempLim() != 1) return 19;
   if (!Inverter.getMotorTempLim() != 1) return 20;
   if (!Inverter.getRPMMinLimit() != 1) return 21;
   if (!Inverter.getRPMMaxLimit() != 1) return 22;
   if (!Inverter.getPowerLimit() != 1) return 23;

   //other systems check, if needed
   //30: Overexcessive current from battery
   if (Battery.getCurrent() < -500) return 30;

   //31: Charging while driving
   if (Battery.getCurrent() >= 0) return 31;

   //32: Low Voltage
   if (Battery.getVoltage() < 5) return 32;

   //33: Overexcessive Voltage
   if (Battery.getVoltage() > 240) return 33;

   //34: Low Battery
   if (Battery.getChargeState() < 20) return 34;

   //35: Battery Overcharge
   if (Battery.getChargeState() > 100) return 35;

   //36: Battery Health Low
   if (Battery.getHealth() < 80) return 36;

   //37: Faulty Battery Health Data
   if (Battery.getHealth() > 100) return 37;

   //38: High Battery Temperature
   if (Battery.getTemp() > 60) return 38;

   //39: Low Battery Temperature
   if (Battery.getTemp() < 0) return 39;

   //40: Isolation failure/warning (not sure what this is)
   if (Isolation_Monitor.getIsolation() != 1) return 40;
   
   //41-42: Isolation warning/fault. See can documentation.
   if ((i = Isolation_Monitor.getIsolationStates()) == 10 || i == 11) return i + 31;

   //43: Isolation Hardware error
   if (Isolation_Monitor.getHardware_Error() != 0) return 43;

   //44: Electrostatic potential energy exceeds 0.2J
   if (Isolation_Monitor.getTouch_energy_fault() != 0) return 44;

   //45: Exitation pulse not opertional
   if (Isolation_Monitor.getExc_off() != 0) return 45;

   //46: High Battery Voltage / No max_battery_working_voltage set
   if (Isolation_Monitor.getHigh_Battery_Voltage() != 0) return 46;

   //47: Low Battery Voltage / Battery Disconnect
   if (Isolation_Monitor.getLow_Battery_Voltage() != 0) return 47;

   //50: car's moving!!
   if (Sensors.getLinAccelX() != 0 || Sensors.getLinAccelY() != 0 || Sensors.getLinAccelZ() != 0) return 50;
   if (Sensors.getAngVeloX() != 0 || Sensors.getAngVeloY() != 0 || Sensors.getAngVeloZ() != 0) return 50;

   //temperatures are assumed to be in centrigrade (@(somebody that's not rt.z) do the conversions if they turn out to be in the whatever random other temperature unit everyone else uses)
   //51: Front-right tire tempaerture too high
   if (Sensors.getFRtemp1() > 90) return 51;

   //52: Front-right tire temperature too low
   if (Sensors.getFRtemp1() < 10) return 52;
   
   //53: Front-right brake temperature too high
   if (Sensors.getFRtemp2() > 450) return 53;

   //54: Front-right brake temperature too low
   if (Sensors.getFRtemp2() <= 0) return 54;

   //55: Overengaged suspension
   //if (Sensors.getFRtravel() > 1) return 55;
   //56: Underengaged suspension
   //if (Sesnors.getFRtravel() < -1) return 56;

   //57: Front-right wheel is moving
   if (Sensors.getFRspeed() > 0) return 57;

   //58: High Front-right tire pressure
   if (Sensors.getFRpsi() > 50) return 58;

   //59: Low Front-right tire pressure
   if (Sensors.getFRpsi() < 24) return 59;


   //61: Front-left tire tempaerture too high
   if (Sensors.getFLtemp1() > 90) return 61;

   //62: Front-left tire temperature too low
   if (Sensors.getFLtemp1() < 10) return 62;
   
   //63: Front-left brake temperature too high
   if (Sensors.getFLtemp2() > 450) return 63;

   //64: Front-left brake temperature too low
   if (Sensors.getFLtemp2() <= 0) return 64;

   //65: Overengaged suspension
   //if (Sensors.getFLtravel() > 1) return 65;
   //66: Underengaged suspension
   //if (Sesnors.getFLtravel() < -1) return 66;

   //67: Front-left wheel is moving
   if (Sensors.getFLspeed() > 0) return 67;

   //68: High Front-left tire pressure
   if (Sensors.getFLpsi() > 50) return 68;

   //69: Low Front-left tire pressure
   if (Sensors.getFLpsi() < 24) return 69;


   //71: Rear-right tire tempaerture too high
   if (Sensors.getRRtemp1() > 90) return 71;

   //72: Rear-right tire temperature too low
   if (Sensors.getRRtemp1() < 10) return 72;
   
   //73: Rear-right brake temperature too high
   if (Sensors.getRRtemp2() > 450) return 73;

   //74: Rear-right brake temperature too low
   if (Sensors.getRRtemp2() <= 0) return 74;

   //75: Overengaged suspension
   //if (Sensors.getRRtravel() > 1) return 75;
   //76: Underengaged suspension
   //if (Sesnors.getRRtravel() < -1) return 76;

   //77: Rear-right wheel is moving
   if (Sensors.getRRspeed() > 0) return 77;

   //78: High Rear-right tire pressure
   if (Sensors.getRRpsi() > 50) return 78;

   //79: Low Rear-right tire presure
   if (Sensors.getRRpsi() < 24) return 79;


   //81: Rear-left tire tempaerture too high
   if (Sensors.getRLtemp1() > 90) return 81;

   //82: Rear-left tire temperature too low
   if (Sensors.getRLtemp1() < 10) return 82;
   
   //83: Rear-left brake temperature too high
   if (Sensors.getRLtemp2() > 450) return 83;

   //84: Rear-left brake temperature too low
   if (Sensors.getRLtemp2() <= 0) return 84;

   //85: Overengaged suspension
   //if (Sensors.getRLtravel() > 1) return 85;
   //86: Underengaged suspension
   //if (Sesnors.getRLtravel() < -1) return 86;

   //87: Rear-left wheel is moving
   if (Sensors.getRLspeed() > 0) return 87;

   //88: High Rear-left tire pressure
   if (Sensors.getRLpsi() > 50) return 88;

   //89: Low Rear-left tire presure
   if (Sensors.getRLpsi() < 24) return 89;

   //91: Accelerator engaged
   if (Sensors_Pedals.getAPPS() > 0) return 91;
   
   //92: Brakes not engaged upon startup
   if (Sensors_Pedals.getBrakePressure1() != 0 || Sensors_Pedals.getBrakePressure2() != 0) return 92;

   return 0;
}

bool drive(){
    //TODO: find how to get dash signals from the CAN
    return false;
}



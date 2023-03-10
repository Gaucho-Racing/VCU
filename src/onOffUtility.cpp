#include "Nodes.h"

//returns true if there is current running to the motor
bool onPressed(){ 
    if(Inverter.getDCCurrent() > 0) return true;
    else return false;
}

bool systemsCheck(){
    //TODO - insert acutal code
    //make sure the data works
    //outputs error message depending on what the error is

    //1: Unable to revieve CAN packets
   if ((Inverter.getAge()) > 1000) return 1;
   if ((Isolation_Monitor.getAge()) > 1000) return 1;
   if ((Sensors.getAge()) > 1000) return 1;
   if ((Charger.getAge()) > 1000) return 1;
   if ((Battery.getAge()) > 1000) return 1;

   //2 - 11: Motor faults, refer to CAN documentation;
   if (Inverter.getFaults() != 0) return Inverter.getFaults() + 1;

   //12: Motor is running when not supposed to
   if (Inverter.ERPM() != 0 || Inverter.dutyCycle() != 0 || Inverter.getACCurrent() != 0) return 12;

   //-1: Wait... the thing isn't actually on
   if (Inverter.getDCCurrent() <= 0) return -1;

   //13: Drive disabled
   if (Inverter.getDriveEnable() != 1) return 13;

   //14: Capacitor Temperature Limit Disabled
   if (!Inverter.CapTempLim() != 1) return 14;

   //15: DC Current Limit Disabled
   if (!Inverter.getDriveEnable() != 1) return 15;

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
   //24: Overexcessive current from battery
   if (Battery.getCurrent() > -500) return 24;

   //25: Charging while driving
   if (Battery.getCurrent() <= 0) return 25;

   //26: Low Voltage
   if (Battery.getVoltage() < 5) return 26;

   //27: Overexcessive Voltage
   if (Battery.getVoltage() > 240) return 27;

   //28: Low Battery
   if (Battery.getChargeState() < 20) return 28;

   //29: Battery Overcharge
   if (Battery.getChargeState() > 100) return 29;

   //30: Battery Health Low
   if (Battery.getHealth() < 80) return 30;

   //31: Faulty Battery Health Data
   if (Battery.getHealth() > 100) return 31;

   //31: High Battery Temperature
   if (Battery.getTemp() > 60) return 32;

   //33: Low Battery Temperature
   if (Battery.getTemp() < 0) return 33;

    return false;
}

bool drive(){
    //TODO
    return false;
}



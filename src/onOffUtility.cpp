    //onOffUtility.cpp
    // @yarwinliu, @rt.z, 03122023

    #include "main.h"
    #include "onOffUtility.h"
    #include <cmath>

//returns true if there is current running to the motor
bool onPressed(I_no_can_speak_flex &car) {  
    if(car.DTI.getDCCurrent() > 0) return true;
    else return false;
}

std::vector<int> systemsCheck(I_no_can_speak_flex &car) {
    std::vector<int> crit_codes;

    //TODO - insert acutal code
    //make sure the data works
    //outputs error message depending on what the error is

    //100: Unable to revieve CAN packets
    if ((car.DTI.getAge()) > 1000) crit_codes.push_back(100);
    if ((car.IMD.getAge()) > 1000) crit_codes.push_back(100);
    if ((car.sensors.getAge()) > 1000) crit_codes.push_back(100);
    if ((car.pedals.getAge()) > 1000) crit_codes.push_back(100);
    if ((car.charger.getAge()) > 1000) crit_codes.push_back(100);
    if ((car.BMS.getAge()) > 1000) crit_codes.push_back(100);

    //150 - 160: Motor faults, refer to CAN documentation
    int i = 0;
    if ((i = car.DTI.getFaults()) != 0) crit_codes.push_back(i + 149);

    //110: Motor is running when not supposed to
    if (car.DTI.getERPM() != 0 || car.DTI.getDuty() != 0 || car.DTI.getACCurrent() != 0) crit_codes.push_back(110);

    //106: Wait... the thing isn't actually on
    if (car.DTI.getDCCurrent() <= 0) crit_codes.push_back(106);

    //105: Drive disabled
    if (car.DTI.getDriveEnable() != 1) crit_codes.push_back(105);

    //016: Capacitor Temperature Limit Disabled
    if (!car.DTI.getCapTempLim() != 1) crit_codes.push_back(16);

    //017: IGBT Accel. Limit Disabled
    if (!car.DTI.getIgbtAccelTempLim() != 1) crit_codes.push_back(17);

    //018: IGBT Temp. Limit Disabled 
    if (!car.DTI.getIgbtTempLim() != 1) crit_codes.push_back(18);

    //019: Motor accel temp. limit disabled
    if (!car.DTI.getVoltInLim() != 1) crit_codes.push_back(19);

    //etc. (im too lazy to type them all out)
    if (!car.DTI.getMotorAccelTempLim() != 1) crit_codes.push_back(20);
    if (!car.DTI.getMotorTempLim() != 1) crit_codes.push_back(21);
    if (!car.DTI.getRPMMinLimit() != 1) crit_codes.push_back(22);
    if (!car.DTI.getRPMMaxLimit() != 1) crit_codes.push_back(23);
    if (!car.DTI.getPowerLimit() != 1) crit_codes.push_back(24);

    //30: Overexcessive current from battery
    if (car.BMS.getCurrent() < -500) crit_codes.push_back(30);

    //130: Okay, enough current draw…
    if (car.BMS.getCurrent() < -999) crit_codes.push_back(130);

    //131: Charging while driving
    if (car.BMS.getCurrent() >= 0) crit_codes.push_back(131);

    //132: Low Voltage
    if (car.BMS.getVoltage() < 5) crit_codes.push_back(131);

    //33: Overexcessive Voltage
    if (car.BMS.getVoltage() > 120) crit_codes.push_back(33);

    //133: Very Overexcessive Voltage
    if (car.BMS.getVoltage() > 120) crit_codes.push_back(133);

    //34: Low battery
    if (car.BMS.getChargeState() < 20) crit_codes.push_back(34);

    //134: Very Low battery
    if (car.BMS.getChargeState() < 5) crit_codes.push_back(134);

    //135: Battery Overcharge
    if (car.BMS.getChargeState() > 100) crit_codes.push_back(135);

    //36: Battery Health Low
    if (car.BMS.getHealth() < 80) crit_codes.push_back(36);

    //136: Battery Health Very Low
    if (car.BMS.getHealth() < 50) crit_codes.push_back(136);

    //137: Faulty Battery Health Data
    if (car.BMS.getHealth() > 100) crit_codes.push_back(137);

    //2, 102: High Battery Temperature
    if (car.BMS.getTemp() > 60) crit_codes.push_back(2);

    //101: Low Battery Temperature
    if (car.BMS.getTemp() < 0) crit_codes.push_back(101);


    //40: IMD High Uncertatinty
    if (car.IMD.getHigh_Uncertainty() != 1) crit_codes.push_back(40);
    
    //41: Isolation warning. See can documentation.
    if ((i = car.IMD.getIsolationStates()) == 10) crit_codes.push_back(41);

    //141: Isolation fault. See can documentation.
    if ((i = car.IMD.getIsolationStates()) == 11) crit_codes.push_back(141);

    //142: Isolation state unknown. See can documentation.
    if ((i = car.IMD.getIsolationStates()) == 1) crit_codes.push_back(142);

    //143: Isolation Hardware error.
    if (car.IMD.getHardware_Error() != 0) crit_codes.push_back(143);

    //144: Electrostatic potential energy exceeds 0.2J
    if (car.IMD.getTouch_energy_fault() != 0) crit_codes.push_back(144);

    //145: Exitation pulse not opertional
    if (car.IMD.getExc_off() != 0) crit_codes.push_back(145);

    //46: IMD: High battery Voltage / No max_battery_working_voltage set
    if (car.IMD.getHigh_Battery_Voltage() != 0) crit_codes.push_back(46);

    //47: Low car.BMS Voltage / car.BMS Disconnect
    if (car.IMD.getLow_Battery_Voltage() != 0) crit_codes.push_back(47);

    //50: car's moving... !!!! linear quantities assumed in meters, angualar quantities assumed in radians.
    if (
        fabs(car.sensors.getLinAccelX()) > 0.025 ||
        fabs(car.sensors.getLinAccelY()) > 0.025 ||
        fabs(car.sensors.getLinAccelZ()) > 0.025) {
        crit_codes.push_back(50);
    }

    if (
        fabs(car.sensors.getAngVeloX()) > 0.05 ||  
        fabs(car.sensors.getAngVeloY()) > 0.05 ||  
        fabs(car.sensors.getAngVeloZ()) > 0.05) {
        crit_codes.push_back(50);
    }

    //temperatures are assumed to be in centrigrade. Wheel speed units assumed to be meters per second (linear). (@(somebody that's not rt.z) do the conversions if they turn out to be in the whatever random other temperature unit everyone else uses)

    //51: Front-right tire tempaerture too high
    if (car.sensors.getFRtemp1() > 90) crit_codes.push_back(51);

    //52: Front-right tire temperature too low
    if (car.sensors.getFRtemp1() < 10) crit_codes.push_back(52);
    
    //53: Front-right brake temperature too high
    if (car.sensors.getFRtemp2() > 450) crit_codes.push_back(53);

    //54: Front-right brake temperature too low
    if (car.sensors.getFRtemp2() <= 0) crit_codes.push_back(54);

    //55: Overengaged suspension
    //if (car.sensors.getFRtravel() > 1) crit_codes.push_back(55);
    //56: Underengaged suspension
    //if (Sesnors.getFRtravel() < -1) crit_codes.push_back(56);

    //57: Front-right wheel is moving. 
    if (fabs(car.sensors.getFRspeed()) > 0.03) crit_codes.push_back(57);

    //58: High Front-right tire pressure
    if (car.sensors.getFRpsi() > 50) crit_codes.push_back(58);

    //59: Low Front-right tire pressure
    if (car.sensors.getFRpsi() < 24) crit_codes.push_back(59);


    //61: Front-left tire tempaerture too high
    if (car.sensors.getFLtemp1() > 90) crit_codes.push_back(61);

    //62: Front-left tire temperature too low
    if (car.sensors.getFLtemp1() < 10) crit_codes.push_back(62);
    
    //63: Front-left brake temperature too high
    if (car.sensors.getFLtemp2() > 450) crit_codes.push_back(63);

    //64: Front-left brake temperature too low
    if (car.sensors.getFLtemp2() <= 0) crit_codes.push_back(64);

    //65: Overengaged suspension
    //if (car.sensors.getFLtravel() > 1) crit_codes.push_back(65);
    //66: Underengaged suspension
    //if (Sesnors.getFLtravel() < -1) crit_codes.push_back(66);

    //67: Front-left wheel is moving. 
    if (fabs(car.sensors.getFLspeed()) > 0.03) crit_codes.push_back(67);

    //68: High Front-left tire pressure
    if (car.sensors.getFLpsi() > 50) crit_codes.push_back(68);

    //69: Low Front-left tire pressure
    if (car.sensors.getFLpsi() < 24) crit_codes.push_back(69);


    //71: Rear-right tire tempaerture too high
    if (car.sensors.getRRtemp1() > 90) crit_codes.push_back(71);

    //72: Rear-right tire temperature too low
    if (car.sensors.getRRtemp1() < 10) crit_codes.push_back(72);
    
    //73: Rear-right brake temperature too high
    if (car.sensors.getRRtemp2() > 450) crit_codes.push_back(73);

    //74: Rear-right brake temperature too low
    if (car.sensors.getRRtemp2() <= 0) crit_codes.push_back(74);

    //75: Overengaged suspension
    //if (car.sensors.getRRtravel() > 1) crit_codes.push_back(75);
    //76: Underengaged suspension
    //if (Sesnors.getRRtravel() < -1) crit_codes.push_back(76);

    //77: Rear-right wheel is moving
    if (car.sensors.getRRspeed() > 0) crit_codes.push_back(77);

    //78: High Rear-right tire pressure
    if (car.sensors.getRRpsi() > 50) crit_codes.push_back(78);

    //79: Low Rear-right tire presure
    if (car.sensors.getRRpsi() < 24) crit_codes.push_back(79);


    //81: Rear-left tire tempaerture too high
    if (car.sensors.getRLtemp1() > 90) crit_codes.push_back(81);

    //82: Rear-left tire temperature too low
    if (car.sensors.getRLtemp1() < 10) crit_codes.push_back(82);
    
    //83: Rear-left brake temperature too high
    if (car.sensors.getRLtemp2() > 450) crit_codes.push_back(83);

    //84: Rear-left brake temperature too low
    if (car.sensors.getRLtemp2() <= 0) crit_codes.push_back(84);

    //85: Overengaged suspension
    //if (car.sensors.getRLtravel() > 1) crit_codes.push_back(85);
    //86: Underengaged suspension
    //if (Sesnors.getRLtravel() < -1) crit_codes.push_back(86);

    //87: Rear-left wheel is moving
    if (car.sensors.getRLspeed() > 0) crit_codes.push_back(87);

    //88: High Rear-left tire pressure
    if (car.sensors.getRLpsi() > 50) crit_codes.push_back(88);

    //89: Low Rear-left tire presure
    if (car.sensors.getRLpsi() < 24) crit_codes.push_back(89);

    //191: Accelerator engaged
    if (car.pedals.getAPPS() > 0) crit_codes.push_back(191);
    
    //192: Brakes not engaged upon startup
    if (car.pedals.getBrakePressure1() != 0 || car.pedals.getBrakePressure2() != 0) crit_codes.push_back(192);

    return crit_codes;
}

bool driveEngaged(I_no_can_speak_flex &car) {
    //TODO: find how to get dash signals from the CAN
    return false;
}
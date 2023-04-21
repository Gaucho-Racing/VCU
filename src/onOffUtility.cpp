//onOffUtility.cpp
// @rt.z, @yarwinliu, 03122023

#include "main.h"
#include "constants.h"
#include "onOffUtility.h"
#include <vector>
#include <cmath>

//returns true if there is current running to the motor
bool onPressed(I_no_can_speak_flex &car) {  
    return (car.DTI.getDCCurrent() > 0);
}

bool isRejectingStartup(I_no_can_speak_flex &car) {
    //152: Drive disabled
    if (car.DTI.getDriveEnable() != 1) {
        car.sendDashError(152);
        return true;
    }

    //151: Wait... the thing isn't actually on
    if (car.DTI.getDCCurrent() <= 0) {
        car.sendDashError(151);
        return true;
    }

    //191: Accelerator engaged
    if ((car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 > 0) {
        car.sendDashError(191);
        return true;
    }
    
    //192: Brakes not engaged upon startup
    if (car.pedals.getBrakePressure1() != 0 || car.pedals.getBrakePressure2() != 0) {
        car.sendDashError(192);
        return true;
    }

    return false;
}

bool criticalCheck(I_no_can_speak_flex &car, bool send_dash_errors = true) {
    std::vector<int> crit_codes;

    //CAN FAULT (100):
    //100: Unable to revieve CAN packets
    if ((car.DTI.getAge()) > MAX_CAN_DURATION) crit_codes.push_back(100);
    if ((car.IMD.getAge()) > MAX_CAN_DURATION) crit_codes.push_back(100);
    if ((car.sensors.getAge()) > MAX_CAN_DURATION) crit_codes.push_back(100);
    if ((car.pedals.getAge()) > MAX_CAN_DURATION) crit_codes.push_back(100);
    if ((car.charger.getAge()) > MAX_CAN_DURATION) crit_codes.push_back(100);
    if ((car.BMS.getAge()) > MAX_CAN_DURATION) crit_codes.push_back(100);

    /* don't know if this will work…
        if (CANFailure()) crit_codes.push_back(100);
    */



    //IMPORTANT SH!T BELOW (150):
    //150: Motor is running when not supposed to
    if (car.DTI.getERPM() != 0 || car.DTI.getDuty() != 0 || car.DTI.getACCurrent() != 0) crit_codes.push_back(150);



    //Other CAN DTI data faults (160 - 169):
    //159 - 169: Motor faults, refer to CAN documentation
    int i = 0;
    if ((i = car.DTI.getFaults()) != 0) crit_codes.push_back(i + 158);



    //BATTERY STARTUP ERRORS (170 - 179)
    //130: Overexcessive current from battery at startup
    if (car.BMS.getCurrent() <= -1) crit_codes.push_back(170);

    //131: Charging while driving
    if (car.BMS.getCurrent() >= 0) crit_codes.push_back(171);

    //132: Low Voltage
    if (car.BMS.getVoltage() < 5) crit_codes.push_back(172);

    //133: Very Overexcessive Voltage
    if (car.BMS.getVoltage() > 240) crit_codes.push_back(173);

    //134: Very Low battery
    if (car.BMS.getChargeState() < 5) crit_codes.push_back(174);

    //135: Battery Overcharge
    if (car.BMS.getChargeState() > 100) crit_codes.push_back(175);

    //136: Battery Health Very Low
    if (car.BMS.getHealth() < 50) crit_codes.push_back(176);

    //137: Faulty Battery Health Data
    if (car.BMS.getHealth() > 100) crit_codes.push_back(177);

    //2, 102: High Battery Temperature
    if (car.BMS.getTemp() > CRITICAL_CELL_TEMP) crit_codes.push_back(102);

    //101: Low Battery Temperature
    if (car.BMS.getTemp() < 0) crit_codes.push_back(101);



    //IMD STARTUP ERRORS (180 - 189):
    //141: Isolation fault. See can documentation.
    if ((i = car.IMD.getIsolationStates()) == 11) crit_codes.push_back(181);

    //142: Isolation state unknown. See can documentation.
    if ((i = car.IMD.getIsolationStates()) == 1) crit_codes.push_back(182);

    //143: Isolation Hardware error.
    if (car.IMD.getHardware_Error() != 0) crit_codes.push_back(183);

    //144: Electrostatic potential energy exceeds 0.2J
    if (car.IMD.getTouch_energy_fault() != 0) crit_codes.push_back(184);

    //145: Exitation pulse not opertional
    if (car.IMD.getExc_off() != 0) crit_codes.push_back(185);

    //147: IMD: Low battery Voltage / Battery Disconnect
    if (car.IMD.getLow_Battery_Voltage() != 0) crit_codes.push_back(187);



    if (send_dash_errors) for (int code : crit_codes) car.sendDashError((byte)code);
    return (crit_codes.empty());
}

bool warningCheck(I_no_can_speak_flex &car, bool send_dash_warnings = true) {
    std::vector<int> warn_codes;


    //016: Capacitor Temperature Limit Disabled
    if (!car.DTI.getCapTempLim() != 1) warn_codes.push_back(16);

    //017: IGBT Accel. Limit Disabled
    if (!car.DTI.getIgbtAccelTempLim() != 1) warn_codes.push_back(17);

    //018: IGBT Temp. Limit Disabled 
    if (!car.DTI.getIgbtTempLim() != 1) warn_codes.push_back(18);

    //019: Motor accel temp. limit disabled
    if (!car.DTI.getVoltInLim() != 1) warn_codes.push_back(19);

    //etc. (im too lazy to type them all out)
    if (!car.DTI.getMotorAccelTempLim() != 1) warn_codes.push_back(20);
    if (!car.DTI.getMotorTempLim() != 1) warn_codes.push_back(21);
    if (!car.DTI.getRPMMinLimit() != 1) warn_codes.push_back(22);
    if (!car.DTI.getRPMMaxLimit() != 1) warn_codes.push_back(23);
    if (!car.DTI.getPowerLimit() != 1) warn_codes.push_back(24);



    //BATTERY STARTUP WARINGS (20 - 29)
    //33: Overexcessive Voltage
    if (car.BMS.getVoltage() > 120) warn_codes.push_back(23);

    //34: Low battery
    if (car.BMS.getChargeState() < 20) warn_codes.push_back(24);

    //36: Battery Health Low
    if (car.BMS.getHealth() < 80) warn_codes.push_back(26);

    if (car.BMS.getTemp() > CELL_TEMP_WARN) warn_codes.push_back(2);


    //IMD STARTUP WARNINGS (30 - 39)
    //40: IMD High Uncertatinty
    if (car.IMD.getHigh_Uncertainty() != 1) warn_codes.push_back(30);
    
    int i;
    //41: Isolation warning. See can documentation.
    if ((i = car.IMD.getIsolationStates()) == 10) warn_codes.push_back(31);

    //46: IMD: High battery Voltage / No max_battery_working_voltage set
    if (car.IMD.getHigh_Battery_Voltage() != 0) warn_codes.push_back(36);



    //49+: car's moving... !!!! linear quantities assumed in meters, angualar quantities assumed in radians.
    if (
        fabs(car.sensors.getLinAccelX()) > 0.025 ||
        fabs(car.sensors.getLinAccelY()) > 0.025 ||
        fabs(car.sensors.getLinAccelZ()) > 0.025) {
        warn_codes.push_back(49);
    }

    if (
        fabs(car.sensors.getAngVeloX()) > 0.05 ||  
        fabs(car.sensors.getAngVeloY()) > 0.05 ||  
        fabs(car.sensors.getAngVeloZ()) > 0.05) {
        warn_codes.push_back(50);
    }

    //57: Front-right wheel is moving. 
    if (fabs(car.sensors.getFRspeed()) > WARN_STARTUP_WHEEL_SPEED) warn_codes.push_back(57);

    //67: Front-left wheel is moving. 
    if (fabs(car.sensors.getFLspeed()) > WARN_STARTUP_WHEEL_SPEED) warn_codes.push_back(67);

    //77: Rear-right wheel is moving
    if (car.sensors.getRRspeed() > WARN_STARTUP_WHEEL_SPEED) warn_codes.push_back(77);

    //87: Rear-left wheel is moving
    if (car.sensors.getRLspeed() > WARN_STARTUP_WHEEL_SPEED) warn_codes.push_back(87);



    if (send_dash_warnings) for (int code : warn_codes) car.sendDashError((byte)code);
    return (warn_codes.empty());
}

bool driveEngaged(I_no_can_speak_flex &car) {
    //TODO: find how to get dash signals from the CAN
    return true;
}

// charge.cpp
// @rt.z

#include "main.h"
#include "constants.h"

States charge_precharge(I_no_can_speak_flex &car) {
   if (car.charger.getVoltage() > CHARGING_VOLTAGE) return CHARGE_CHARGING;
   if (car.charger.getCurrent() <= 0) return OFF;
   return CHARGE_PRECHARGE;
}

States charge_charging(I_no_can_speak_flex &car) {
   car.DTI.setRCurrent(0);
   // get data
   // push charge data to dash
   if (car.BMS.getChargeState() > 99) return CHARGE_FULL;
   if (car.charger.getCurrent() < 0) return OFF;
   return CHARGE_CHARGING;
}

States charge_full(I_no_can_speak_flex &car) {
   // get data
   car.DTI.setRCurrent(0);
   // push charge data to dash
   if (car.charger.getCurrent() > 0 && car.BMS.getChargeState() <= 99) return CHARGE_CHARGING;
   if (car.charger.getCurrent() <= 0) return OFF;
   return CHARGE_CHARGING;
}

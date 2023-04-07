// charge.cpp
// @rt.z

#include "main.h"

States charge_precharge() {
   /* interrupts logic, @nikunjparasar please include */
   delay(4000);
   // loop get data/interrupt check 
   return CHARGE_CHARGING;
}

States charge_charging() {
   while (1) {
      car.DTI.setRCurrent(0);
      // get data
      // push charge data to dash
      if (car.BMS.getChargeState() > 99) return CHARGE_FULL;
      if (car.BMS.getCurrent() < 0) return OFF;
   }
}

States charge_full() {
   while (1) {
      // get data
      car.DTI.setRCurrent(0);
      // push charge data to dash
      if (car.BMS.getCurrent() > 0 && car.BMS.getChargeState() <= 99) return CHARGE_CHARGING;
      if (car.BMS.getCurrent() < 0) return OFF;
   }
}

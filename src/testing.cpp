//testing.cpp
// @nikunjparasar, @Th3Will

#include "testing.h"
#include <Arduino.h>
unsigned long time69=0;
States testing(I_no_can_speak_flex &car, Switchboard& s, States state){
    if(millis()-time69>100){
        Serial.println("\n----------state----------");
        Serial.println(getTextForEnum(state).c_str());
        Serial.println("-------------------------");
        // printVals(car);
        Serial.print("APPS Sensor 1: ");
        Serial.println(s.ACCEL_1);
        Serial.print("APPS Sensor 2: ");
        Serial.println(s.ACCEL_2);
        Serial.print("Brake Sensor Front: ");
        Serial.println(s.BRAKE_FRONT);
        Serial.print("Brake Sensor Rear: ");
        Serial.println(s.BRAKE_REAR);


        time69 = millis();
    }
    // car.readData();
    //Serial.println(car.readData());
    return TESTING;

}


void printVals(I_no_can_speak_flex &car){
    
    //print out Inverter
    Serial.print("Inverters, ERPM: ");
    Serial.println(car.DTI.getERPM());
    Serial.print("Inverters, DC current: ");
    Serial.println(car.DTI.getDCCurrent());
    Serial.print("Inverters, Motor Temp: ");
    Serial.println(car.DTI.getMotorTemp());
    //print out Batt
    Serial.print("Batt, current: ");
    Serial.println(car.BMS.getCurrent());
    Serial.print("Batt, Voltage: ");
    Serial.println(car.BMS.getVoltage());
    Serial.print("Batt, charge state: ");
    Serial.println(car.BMS.getChargeState());
    //print out IMD
    Serial.print("IMD, Isolation State: ");
    // Serial.println(car.IMD.getIsolationStates());
    Serial.print("IMD, High Battery Voltage: ");
    // Serial.println(car.IMD.getHigh_Battery_Voltage());
    Serial.print("IMD, Low Battery Voltage: ");
    // Serial.println(car.IMD.getLow_Battery_Voltage());
    //print out charger
    Serial.print("Charger, Current: ");
    Serial.println(car.charger.getCurrent());
    Serial.print("Charger, Status: ");
    Serial.println(car.charger.getStatus());
    Serial.print("Charger, Voltage ");
    Serial.println(car.charger.getVoltage());
    //print out sensor
    Serial.print("Sensor, FRspeed ");
    Serial.println(car.sensors.getFRspeed());
    Serial.print("Sensor, FLspeed ");
    Serial.println(car.sensors.getFLspeed());
    Serial.print("Sensor, RRspeed ");
    Serial.println(car.sensors.getRRspeed());
    Serial.print("Sensor, RLspeed ");
    Serial.println(car.sensors.getRLspeed());
    Serial.print("Sensor, FRspeed ");
    Serial.println(car.sensors.getFRspeed());
    Serial.print("Sensor, Lin Accel X ");\
    Serial.println(car.sensors.getLinAccelX());
    Serial.print("Sensor, Lin Accel Y ");
    Serial.println(car.sensors.getLinAccelY());
    //print out pedals
    Serial.print("Pedals, APPS1 ");
    Serial.println(car.pedals.getAPPS1());
    Serial.print("Pedals, APPS2 ");
    Serial.println(car.pedals.getAPPS2());
    Serial.print("Pedals, BrakePressure1 ");
    Serial.println(car.pedals.getBrakePressure1());
    Serial.print("Pedals, BrakePressure2 ");
    Serial.println(car.pedals.getBrakePressure2());
}
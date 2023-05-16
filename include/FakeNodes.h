// @nikunjparasar

#ifndef FAKENODES_H
#define FAKENODES_H

#include <Arduino.h>
#include <FlexCAN_T4.h>
// #include <iostream>
// #include <limits.h>
// #include <SPI.h>
// #include <SD.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
// #include "data.h"
using namespace std;



/*


-------------------------------------------------------------------
TEMPLATE FOR NEW NODE

struct *NAME*
{
    unsigned long ID = 0;

    *NAME*(unsigned long id){ID = id;}

    void receive(unsigned long id, byte buf[]){
        -id will be the message ID from the node
        -buf is a byte array of the data from the CAN frame
        *CODE FOR SORTING YOUR DATA OR WHATEVER IDFK*
    }
};

--------------------------------------------------------------------
*/









struct Inverter1 
{
    
    vector<vector<double>> data;
    Inverter1(){
        data = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{7.530145586657266,78.98372650215578,75.53124207582078,22.11925890260471,19.738234308786662,79.89723114487323,39.18810081269424,52.4812979601762,35.549055180262165,42.22227897262706},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{20.0,2.0,1.0,6.0,7.0,-2.0,-2.0,-2.0,-2.0,-2.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
    }
    // get the value from the current line. 
    double getERPM() {return data[0][millis()/1000];} 
    double getDuty() {return data[1][millis()/1000];} 
    double getVoltIn() {return data[2][millis()/1000];}
    double getACCurrent() {return data[3][millis()/1000];}
    double getDCCurrent() {return data[4][millis()/1000];}
    double getInvTemp() {return data[5][millis()/1000];} 
    double getMotorTemp() {return data[6][millis()/1000];} 
    double getFaults() {return data[7][millis()/1000];}
    double getCurrentD() {return data[8][millis()/1000];}  
    double getCurrentQ() {return data[9][millis()/1000];}  
    double getThrottleIn() {return data[10][millis()/1000];}  
    double getBrakeIn() {return data[11][millis()/1000];}  
    double getD1() {return data[12][millis()/1000];}
    double getD2() {return data[13][millis()/1000];}
    double getD3() {return data[14][millis()/1000];}
    double getD4() {return data[15][millis()/1000];}
    double getDO1() {return data[16][millis()/1000];}
    double getDO2() {return data[17][millis()/1000];}  
    double getDO3() {return data[18][millis()/1000];}  
    double getDO4() {return data[18][millis()/1000];}  
    double getDriveEnable() {return data[19][millis()/1000];} 
    double getCapTempLim() {return data[20][millis()/1000];}
    double getDCCurrentLim() {return data[21][millis()/1000];}
    double getDriveEnableLim() {return data[22][millis()/1000];}
    double getIgbtAccelTempLim() {return data[23][millis()/1000];}
    double getIgbtTempLim() {return data[24][millis()/1000];}
    double getVoltInLim() {return data[25][millis()/1000];}
    double getMotorAccelTempLim() {return data[26][millis()/1000];}
    double getMotorTempLim() {return data[27][millis()/1000];}
    double getRPMMinLimit() {return data[28][millis()/1000];}
    double getRPMMaxLimit() {return data[29][millis()/1000];}
    double getPowerLimit() {return data[30][millis()/1000];}
    double getAge(){return data[31][millis()/1000];} //time since last data packet

    void setCurrent(float in){}          
    void setBrakeCurrent(float in) {}    
    void setERPM(long in)  {}            
    void setPosition(float in)  {}       
    void setRCurrent(float in)  {}       
    void setRBrakeCurrent(float in)  {}  
    void setMaxCurrent(float in)   {}    
    void setMaxBrakeCurrent(float in)  {}
    void setMaxDCCurrent(float in)    {} 
    void setMaxDCBrakeCurrent(float in) {}
    void setDriveEnable(byte in) {}

};







struct Battery1 ///done for now
{
    vector<vector<double>> data;
    Battery1(){
        // data = {{10.0,199.0,-10.0,128.0,188.0,77.0,-7.0,33.0,-1.0,109.0,85.0,52.0,59.0,107.0,36.0,-29.0,-199.0,-179.0,-65.0,-126.0,15.0,-189.0,-100.0,-140.0,180.0,-47.0,-91.0,72.0,184.0,43.0},{353.0,317.0,503.0,555.0,540.0,551.0,376.0,448.0,318.0,356.0,529.0,323.0,502.0,509.0,330.0,573.0,468.0,424.0,526.0,480.0,463.0,560.0,407.0,539.0,311.0,447.0,339.0,376.0,557.0,511.0},{20.0,4.0,88.0,49.0,56.0,62.0,95.0,61.0,0.0,91.0,88.0,35.0,44.0,98.0,95.0,56.0,19.0,98.0,54.0,22.0,65.0,24.0,74.0,16.0,34.0,83.0,12.0,72.0,40.0,44.0},{80.0,48.0,79.0,59.0,68.0,95.0,9.0,20.0,38.0,59.0,43.0,14.0,71.0,95.0,63.0,16.0,52.0,25.0,44.0,50.0,86.0,35.0,69.0,69.0,56.0,87.0,29.0,80.0,25.0,29.0},{131.0,119.0,107.0,35.0,25.0,7.0,102.0,16.0,29.0,75.0,6.0,71.0,149.0,124.0,83.0,58.0,134.0,131.0,10.0,30.0,150.0,14.0,141.0,79.0,38.0,78.0,112.0,121.0,58.0,126.0},{1.0,1.0,3.0,3.0,0.0,4.0,4.0,3.0,0.0,4.0,1.0,1.0,0.0,2.0,0.0,1.0,3.0,4.0,2.0,0.0,2.0,3.0,2.0,3.0,1.0,4.0,1.0,3.0,1.0,0.0},{1.0,2.0,0.0,1.0,3.0,1.0,3.0,1.0,2.0,4.0,4.0,1.0,2.0,3.0,1.0,4.0,2.0,4.0,1.0,2.0,2.0,0.0,0.0,0.0,1.0,1.0,4.0,1.0,2.0,4.0},{518.0,213.0,970.0,856.0,901.0,10.0,752.0,971.0,963.0,959.0,637.0,954.0,356.0,550.0,693.0,68.0,576.0,126.0,536.0,266.0,79.0,917.0,774.0,786.0,855.0,475.0,124.0,921.0,291.0,254.0}};
    data = {{  42, -196,  134, -130, -144,  146,    6,  167, -130,   34},
{ 428,  429,  374,  449,  557,  366,  571,  584,  534,  597},
{ 100,  100,  100,  100,  100,  100,  100,  100,  100,  100},
{ 100,  100,  100,  100,  100,  100,  100,  100,  100,  100},
{  24,   36,   23,   21,   33,   34,   34,   32,   34,   34},
{   4,    4,    4,    4,    4,    4,    4,    4,    4,    4},
{   4,    4,    4,    4,    4,    4,    4,    4,    4,    4},
{  10,   10,   10,   10,   10,   10,   10,   10,   10,   10}};
    }

    double getCurrent() {return data[0][millis()/1000];}  //Signed current [-3276.7, 3276.7]
    double getVoltage() {return data[1][millis()/1000];}  //Unsigned voltage [0, 6553.5]
    double getChargeState() {return data[2][millis()/1000];}  //Percent [0, 100]
    double getHealth() {return data[3][millis()/1000];}  //Percent [0, 100]
    double getTemp() {return data[4][millis()/1000];}  //Degrees Celcius [-40, 80]
    double getCellVoltage() {return data[5][millis()/1000];}  //Volts [0, 5]
    double getOCellVoltage() {return data[6][millis()/1000];}  //Volts [0, 5]
    double getAge(){return data[7][millis()/1000];} //time since last data packet

};





struct Isolation_Monitor1 // needs to be on a different bus
{
    
    vector<vector<double>> data;
    Isolation_Monitor1(){
        data = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
    }
 

    double getIsolation() {return data[0][millis()/1000];} //true: Status ok, false: fail/warning
    double getIsolationStates() {return data[1][millis()/1000];} //00:Ok, 01: status unknown, 10: warning, 11: fault
    double getHardware_Error() {return data[2][millis()/1000];}
    double getTouch_energy_fault() {return data[3][millis()/1000];}
    double getHigh_Uncertainty() {return data[4][millis()/1000];}
    double getExc_off() {return data[5][millis()/1000];}
    double getHigh_Battery_Voltage() {return data[6][millis()/1000];}
    double getLow_Battery_Voltage() {return data[7][millis()/1000];}
    double getAge(){return data[8][millis()/1000];} //time since last data packet
};




struct Charger1
{
    vector<vector<double>> data;
    Charger1(){
        data = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
    }

    double getVoltage() {return data[0][millis()/1000];} //Charge voltage
    double getCurrent() {return data[1][millis()/1000];} //Charge current
    double getStatus() {return data[2][millis()/1000];} //0:Undefined  1:Working  2:Stop  3:Stop or Standby
    double getAge(){return data[3][millis()/1000];} //Cycle time is 1 sec //time since last data packet
};



struct Sensors1 //TODO:   use the scaling thing
{
    vector<vector<double>> data;
    Sensors1(){
        data = {{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
    }

    double getLatitude() {return data[0][millis()/1000];}
    double getLatitudeHP() {return data[1][millis()/1000];}
    double getLongitude() {return data[2][millis()/1000];}
    double getLongitudeHP() {return data[3][millis()/1000];}
    double getGPSPrecision() {return data[4][millis()/1000];} //Units: mm
    double getLinAccelX() {return data[5][millis()/1000];}
    double getLinAccelY() {return data[6][millis()/1000];}//change scaling
    double getLinAccelZ() {return data[7][millis()/1000];}//change scaling
    double getAbsOrenX() {return data[8][millis()/1000];}//change scaling
    double getAbsOrenY() {return data[9][millis()/1000];}//change scaling
    double getAbsOrenZ() {return data[10][millis()/1000];}//change scaling
    double getAngVeloX() {return data[11][millis()/1000];}//change scaling
    double getAngVeloY() {return data[12][millis()/1000];}//change scaling
    double getAngVeloZ() {return data[13][millis()/1000];}//change scaling
    double getFRtemp1() {return data[14][millis()/1000];}//change scaling
    double getFRtemp2() {return data[15][millis()/1000];}//change scaling
    double getFRtravel() {return data[16][millis()/1000];}//change scaling
    double getFRspeed() {return data[17][millis()/1000];}//change scaling
    double getFRpsi() {return data[18][millis()/1000];}//change scaling
    double getFLtemp1() {return data[19][millis()/1000];}//change scaling
    double getFLtemp2() {return data[20][millis()/1000];}//change scaling
    double getFLtravel() {return data[21][millis()/1000];}//change scaling
    double getFLspeed() {return data[22][millis()/1000];}//change scaling
    double getFLpsi() {return data[23][millis()/1000];}//change scaling
    double getRRtemp1() {return data[24][millis()/1000];}//change scaling
    double getRRtemp2() {return data[25][millis()/1000];}//change scaling
    double getRRtravel() {return data[26][millis()/1000];}//change scaling
    double getRRspeed() {return data[27][millis()/1000];}//change scaling
    double getRRpsi() {return data[28][millis()/1000];}//change scaling
    double getRLtemp1() {return data[29][millis()/1000];}//change scaling
    double getRLtemp2() {return data[30][millis()/1000];}//change scaling
    double getRLtravel() {return data[31][millis()/1000];}//change scaling
    double getRLspeed() {return data[31][millis()/1000];}
    double getRLpsi() {return data[32][millis()/1000];}//change scaling
    double getAge(){return data[33][millis()/1000];} //time since last data packet
};




struct Sensors_Pedals1
{
    vector<vector<double>> data;
    Sensors_Pedals1(){
        data = {{40,40,40,40,40,40,40,40,40,40},
{40,40,40,40,40,40,40,40,40,40},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0, 0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}};
    }

    double getAPPS1() {return data[0][millis()/1000];} //Pedal position [0-100]
    double getAPPS2() {return data[1][millis()/1000];} //Pedal position [0-100]
    double getBrakeLimit() {return data[2][millis()/1000];} //Might not work?
    double getBrakePressure1() {return data[3][millis()/1000];} //psi
    double getBrakePressure2() {return data[4][millis()/1000];} //psi
    double getAge(){return data[5][millis()/1000];} //time since last data packet
};


/*
struct VCU
{
    unsigned long ID = 0;
    unsigned long receiveTime = 0;
    VCU(unsigned long id){ID = id;}
    void receive(unsigned long id, byte buf[]){receiveTime = millis();}

    unsigned long getAge(){return(millis() - receiveTime);} //time since last data packet
};


struct Dashboard
{
    byte data[1][8]={{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
    unsigned long ID = 0;
    unsigned long receiveTime = 0;
    Dashboard(unsigned long id){ID = id;}
    void receive(unsigned long id, byte buf[]){receiveTime = millis();}

    unsigned long getAge(){return(millis() - receiveTime);} //time since last data packet

    byte getMode() {return(data[0][0]);}
    //something about commands//steering angle?
};


struct Calculated_Vals
{
    unsigned long ID = 0;
    unsigned long receiveTime = 0;
    Calculated_Vals(unsigned long id){ID = id;}
    void receive(unsigned long id, byte buf[]){receiveTime = millis();}

    unsigned long getAge(){return(millis() - receiveTime);} //time since last data packet

    //mph, kw, 
};
*/

// struct Debug
// {
//     File logFile;
//     boolean logEnabled = false;
//     bool hasSD2 = false;
//     unsigned long ID = 0;
//     int SD_writes = 0;
//     String out = "";
//     long filters[9] {-1,-1,-1,-1,-1,-1,-1,-1,-1};
//     Debug(unsigned long id){ID = id;}
//     void receive(unsigned long id, byte buf[]){}
//     void CAN_CSV(CAN_message_t msg){
//         if(!logEnabled || !filter(msg)){return;}
//         if(!hasSD2){
//             Serial.println("No SD card");
//             return;
//         }
//         out = (String)micros()+",";
//         out += (String)msg.timestamp+",";
//         out += (String)msg.id+",";
//         for(int i=0; i<8; i++){
//             out+=((String)msg.buf[i]+",");
//         }
//         out += "\n";
//         logFile.write(out.c_str(),sizeof(out.c_str()));
//         Serial.print(out);
//         SD_writes++;
//         if(SD_writes > 100){
//             logFile.flush();
//             SD_writes = 0;
//         }
//     }
//     void write(){
//         logFile.flush();
//     }
//     bool filter(CAN_message_t msg){
//         if(filters[0] != -1){
//             if(msg.id != filters[0])
//                 return false;
//         }
//         for(int i=1; i<9; i++){
//             if(filters[i] != -1){
//                 if(msg.buf[i-1] != filters[i])
//                     return false;
//             }
//         }
//         return true;
//     }
//     void serialRead(){
//         String function = Serial.readStringUntil('\n');
//         if(function.toLowerCase() == "filter"){
//             Serial.println("Enter Filter ID");
//             while(!Serial.available())
//             filterWriter(Serial.readStringUntil('\n'), filters[0]);
            
//         }

//     }
//     void filterWriter(String in, long out){
//         out = in.toInt();
//     }
// };




/*

struct Logger
{
    String logName[62] = {
        "Time", "Drive Enable", "RPM", "Motor Power", "Duty Cycle", "Inverter Temp", "Motor Temp", 
        "Battery Temp", "State of Charge", "Battery Voltage", "Battery Current", "Battery Health", 
        "Acceleration X", "Acceleration Y", "Acceleration Z", "AAPS", "eThrottle", "eBrake", 
        "Brake Pressure F", "Brake Pressure R", "Cell Voltage", "OCell Voltage", "DTI Voltage", 
        "DTI AC Current", "DTI DC Current", "FR Tire Temp", "FL Tire Temp", "RR Tire Temp", "RL Tire Temp", 
        "FR Brake Temp", "FL Brake Temp", "RR Brake Temp", "RL Brake Temp", "FR PSI", "RL PSI", "RR PSI", 
        "RL PSI", "FR Speed", "FL Speed", "RR Speed", "RL Speed", "FR Travel", "FL Travel", "RR Travel", 
        "RL Travel", "Latitude", "Longitude", "GPS Precision", "Orentation X", "Orentation Y", "Orentation Z", 
        "Angular Velocity X", "Angular Velocity Y", "Angular Velocity Z", "Current Id", "Current Iq", "ERPM", 
        "DIO", "Charger stuff", "Charger idk", "Isolation State", "Inverter Faults"};
    Logger(){
        //find next file name
        String filename = "Log0.csv";
        int filenum = 0;
        while(SD.exists(filename.c_str())){
            filenum++;
            filename = "Rec"+(String)filenum+".csv";
        }
        //make a new file
        File logFile = SD.open(filename.c_str(), O_CREAT | O_WRITE);
        //write the names on the top
        for(int i = 0; i<62-1; i++){
            logFile.write((logName[i]+",").c_str(), logName[i].length()+1);
        }
        logFile.write((logName[61]+",").c_str(), logName[61].length()+1);
        logFile.write('\n');
    }
    void log(int log[]){

    }
    
};
*/
#endif
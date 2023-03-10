//charging state, motor should be off
using namespace std;

#include <iostream>
#include "Nodes.h" //import can functions


while (getVoltage() != 100 || getCurrent() == 0) { //current = 0 when manually unpluged
    setDriveEnable(0) // disable drive/motor
}

jumper_fun(fully_charged) // jump to fully charged, does not mean actually fully charged, just not charging

//useful funcs: 
/* float getCurrent() {return (BMSData[8])/10.0;}  //Signed current [-3276.7, 3276.7]
    float getVoltage() {return (BMSData[9])/10.0;}  //Unsigned voltage [0, 6553.5]
    float getChargeState() {return (BMSData[11])/2.0;}  //Percent [0, 100]
    int getHealth() {return (BMSData[15]);}  //Percent [0, 100]
    int getTemp() {return (BMSData[38]);}  //Degrees Celcius [-40, 80]
    float getCellVoltage() {return (BMSData[48])*0.0001;}  //Volts [0, 5]
    float getOCellVoltage() {return (BMSData[51])*0.0001;}  //Volts [0, 5]*/
    
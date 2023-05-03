// @nikunjparasar

#ifndef FAKENODES_H
#define FAKENODES_H

#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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


int timerLine = 0; //STUB

vector<vector<double>> read_csv(string filename) {
    vector<vector<double>> data;
    ifstream infile(filename);
    if (infile.is_open()) {
        string line;
        getline(infile, line); // skip first line
        while (getline(infile, line)) {
            vector<double> row;
            stringstream ss(line);
            string field;
            while (getline(ss, field, ',')) {
                double value = stod(field);
                row.push_back(value);
            }
            data.push_back(row);
        }
        infile.close();
    } else {
        Serial.println("Error opening file");
    }
    return data;
}


struct Inverter1 
{
    
    vector<vector<double>> data;

    Inverter1(string filename){
        data = read_csv(filename);
    }
    
    // get the value from the current line. 
    double getERPM() {return data[0][timerLine];} 
    double getDuty() {return data[1][timerLine];} 
    double getVoltIn() {return data[2][timerLine];}
    double getACCurrent() {return data[3][timerLine];}
    double getDCCurrent() {return data[4][timerLine];}
    double getInvTemp() {return data[5][timerLine];} 
    double getMotorTemp() {return data[6][timerLine];} 
    double getFaults() {return data[7][timerLine];}
    double getCurrentD() {return data[8][timerLine];}  
    double getCurrentQ() {return data[9][timerLine];}  
    double getThrottleIn() {return data[10][timerLine];}  
    double getBrakeIn() {return data[11][timerLine];}  
    double getD1() {return data[12][timerLine];}
    double getD2() {return data[13][timerLine];}
    double getD3() {return data[14][timerLine];}
    double getD4() {return data[15][timerLine];}
    double getDO1() {return data[16][timerLine];}
    double getDO2() {return data[17][timerLine];}  
    double getDO3() {return data[18][timerLine];}  
    double getDO4() {return data[18][timerLine];}  
    double getDriveEnable() {return data[19][timerLine];} 
    double getCapTempLim() {return data[20][timerLine];}
    double getDCCurrentLim() {return data[21][timerLine];}
    double getDriveEnableLim() {return data[22][timerLine];}
    double getIgbtAccelTempLim() {return data[23][timerLine];}
    double getIgbtTempLim() {return data[24][timerLine];}
    double getVoltInLim() {return data[25][timerLine];}
    double getMotorAccelTempLim() {return data[26][timerLine];}
    double getMotorTempLim() {return data[27][timerLine];}
    double getRPMMinLimit() {return data[28][timerLine];}
    double getRPMMaxLimit() {return data[29][timerLine];}
    double getPowerLimit() {return data[30][timerLine];}
    double getAge(){return data[31][timerLine];} //time since last data packet

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

    Battery1(string filename){
        data = read_csv(filename);

    }
    double getCurrent() {return data[0][timerLine];}  //Signed current [-3276.7, 3276.7]
    double getVoltage() {return data[1][timerLine];}  //Unsigned voltage [0, 6553.5]
    double getChargeState() {return data[2][timerLine];}  //Percent [0, 100]
    double getHealth() {return data[3][timerLine];}  //Percent [0, 100]
    double getTemp() {return data[4][timerLine];}  //Degrees Celcius [-40, 80]
    double getCellVoltage() {return data[5][timerLine];}  //Volts [0, 5]
    double getOCellVoltage() {return data[6][timerLine];}  //Volts [0, 5]
    double getAge(){return data[7][timerLine];} //time since last data packet

};





struct Isolation_Monitor1 // needs to be on a different bus
{
    
    vector<vector<double>> data;
    Isolation_Monitor1(string filename){
        data = read_csv(filename);
    }
 

    double getIsolation() {return data[0][timerLine];} //true: Status ok, false: fail/warning
    double getIsolationStates() {return data[1][timerLine];} //00:Ok, 01: status unknown, 10: warning, 11: fault
    double getHardware_Error() {return data[2][timerLine];}
    double getTouch_energy_fault() {return data[3][timerLine];}
    double getHigh_Uncertainty() {return data[4][timerLine];}
    double getExc_off() {return data[5][timerLine];}
    double getHigh_Battery_Voltage() {return data[6][timerLine];}
    double getLow_Battery_Voltage() {return data[7][timerLine];;}
    double getAge(){return data[8][timerLine];} //time since last data packet
};




struct Charger1
{
    vector<vector<double>> data;

    Charger1(string filename){
        data = read_csv(filename);
    }

    double getVoltage() {return data[0][timerLine];} //Charge voltage
    double getCurrent() {return data[1][timerLine];} //Charge current
    double getStatus() {return data[2][timerLine];} //0:Undefined  1:Working  2:Stop  3:Stop or Standby
    double getAge(){return data[3][timerLine];} //Cycle time is 1 sec //time since last data packet
};



struct Sensors1 //TODO:   use the scaling thing
{
    vector<vector<double>> data;
    Sensors1(string filename){
        data = read_csv(filename);
    }

    double getLatitude() {return data[0][timerLine];}
    double getLatitudeHP() {return data[1][timerLine];}
    double getLongitude() {return data[2][timerLine];}
    double getLongitudeHP() {return data[3][timerLine];}
    double getGPSPrecision() {return data[4][timerLine];} //Units: mm
    double getLinAccelX() {return data[5][timerLine];}
    double getLinAccelY() {return data[6][timerLine];}//change scaling
    double getLinAccelZ() {return data[7][timerLine];}//change scaling
    double getAbsOrenX() {return data[8][timerLine];}//change scaling
    double getAbsOrenY() {return data[9][timerLine];}//change scaling
    double getAbsOrenZ() {return data[10][timerLine];}//change scaling
    double getAngVeloX() {return data[11][timerLine];}//change scaling
    double getAngVeloY() {return data[12][timerLine];}//change scaling
    double getAngVeloZ() {return data[13][timerLine];}//change scaling
    double getFRtemp1() {return data[14][timerLine];}//change scaling
    double getFRtemp2() {return data[15][timerLine];}//change scaling
    double getFRtravel() {return data[16][timerLine];}//change scaling
    double getFRspeed() {return data[17][timerLine];}//change scaling
    double getFRpsi() {return data[18][timerLine];}//change scaling
    double getFLtemp1() {return data[19][timerLine];}//change scaling
    double getFLtemp2() {return data[20][timerLine];}//change scaling
    double getFLtravel() {return data[21][timerLine];}//change scaling
    double getFLspeed() {return data[22][timerLine];}//change scaling
    double getFLpsi() {return data[23][timerLine];}//change scaling
    double getRRtemp1() {return data[24][timerLine];}//change scaling
    double getRRtemp2() {return data[25][timerLine];}//change scaling
    double getRRtravel() {return data[26][timerLine];}//change scaling
    double getRRspeed() {return data[27][timerLine];}//change scaling
    double getRRpsi() {return data[28][timerLine];}//change scaling
    double getRLtemp1() {return data[0][timerLine];}//change scaling
    double getRLtemp2() {return data[29][timerLine];}//change scaling
    double getRLtravel() {return data[30][timerLine];}//change scaling
    double getRLspeed() {return data[31][timerLine];}//change scaling
    double getRLpsi() {return data[32][timerLine];}//change scaling
    double getAge(){return data[33][timerLine];} //time since last data packet
};




struct Sensors_Pedals1
{
    vector<vector<double>> data;
    Sensors_Pedals1(string filename){
        data = read_csv(filename);
    }

    double getAPPS1() {return data[0][timerLine];} //Pedal position [0-100]
    double getAPPS2() {return data[1][timerLine];} //Pedal position [0-100]
    double getBrakeLimit() {return data[2][timerLine];} //Might not work?
    double getBrakePressure1() {return data[3][timerLine];} //psi
    double getBrakePressure2() {return data[4][timerLine];} //psi
    double getAge(){return data[5][timerLine];} //time since last data packet
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
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
    long getERPM() {return data[0][timerLine];} 
    float getDuty() {return data[1][timerLine];} 
    int getVoltIn() {return data[2][timerLine];}
    float getACCurrent() {return data[3][timerLine];}
    float getDCCurrent() {return data[4][timerLine];}
    float getInvTemp() {return data[5][timerLine];} 
    float getMotorTemp() {return data[6][timerLine];} 
    byte getFaults() {return data[7][timerLine];}
    float getCurrentD() {return data[8][timerLine];}  
    float getCurrentQ() {return data[9][timerLine];}  
    byte getThrottleIn() {return data[10][timerLine];}  
    byte getBrakeIn() {return data[11][timerLine];}  
    bool getD1() {return data[12][timerLine];}
    bool getD2() {return data[13][timerLine];}
    bool getD3() {return data[14][timerLine];}
    bool getD4() {return data[15][timerLine];}
    bool getDO1() {return data[16][timerLine];}
    bool getDO2() {return data[17][timerLine];}  
    bool getDO3() {return data[18][timerLine];}  
    bool getDO4() {return data[18][timerLine];}  
    bool getDriveEnable() {return data[19][timerLine];} 
    bool getCapTempLim() {return data[20][timerLine];}
    bool getDCCurrentLim() {return data[21][timerLine];}
    bool getDriveEnableLim() {return data[22][timerLine];}
    bool getIgbtAccelTempLim() {return data[23][timerLine];}
    bool getIgbtTempLim() {return data[24][timerLine];}
    bool getVoltInLim() {return data[25][timerLine];}
    bool getMotorAccelTempLim() {return data[26][timerLine];}
    bool getMotorTempLim() {return data[27][timerLine];}
    bool getRPMMinLimit() {return data[28][timerLine];}
    bool getRPMMaxLimit() {return data[29][timerLine];}
    bool getPowerLimit() {return data[30][timerLine];}
    unsigned long getAge(){return data[31][timerLine];} //time since last data packet

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
\
    }
    float getCurrent() {return data[0][timerLine];}  //Signed current [-3276.7, 3276.7]
    float getVoltage() {return data[1][timerLine];}  //Unsigned voltage [0, 6553.5]
    float getChargeState() {return data[2][timerLine];}  //Percent [0, 100]
    byte getHealth() {return data[3][timerLine];}  //Percent [0, 100]
    byte getTemp() {return data[4][timerLine];}  //Degrees Celcius [-40, 80]
    float getCellVoltage() {return data[5][timerLine];}  //Volts [0, 5]
    float getOCellVoltage() {return data[6][timerLine];}  //Volts [0, 5]
    unsigned long getAge(){return data[7][timerLine];} //time since last data packet

};





struct Isolation_Monitor1 // needs to be on a different bus
{
    
    vector<vector<double>> data;
    Isolation_Monitor1(string filename){
        data = read_csv(filename);
    }
 

    boolean getIsolation() {return data[0][timerLine];} //true: Status ok, false: fail/warning
    byte getIsolationStates() {return data[1][timerLine];} //00:Ok, 01: status unknown, 10: warning, 11: fault
    boolean getHardware_Error() {return data[2][timerLine];}
    boolean getTouch_energy_fault() {return data[3][timerLine];}
    boolean getHigh_Uncertainty() {return data[4][timerLine];}
    boolean getExc_off() {return data[5][timerLine];}
    boolean getHigh_Battery_Voltage() {return data[6][timerLine];}
    boolean getLow_Battery_Voltage() {return data[7][timerLine];;}
    unsigned long getAge(){return data[8][timerLine];} //time since last data packet
};




struct Charger1
{
    vector<vector<double>> data;

    Charger1(string filename){
        data = read_csv(filename);
    }

    float getVoltage() {return data[0][timerLine];} //Charge voltage
    float getCurrent() {return data[1][timerLine];} //Charge current
    byte getStatus() {return data[2][timerLine];} //0:Undefined  1:Working  2:Stop  3:Stop or Standby
    unsigned long getAge(){return data[3][timerLine];} //Cycle time is 1 sec //time since last data packet
};



struct Sensors1 //TODO:   use the scaling thing
{
    vector<vector<double>> data;
    Sensors1(string filename){
        data = read_csv(filename);
    }

    float getLatitude() {return data[0][timerLine];}
    float getLatitudeHP() {return data[1][timerLine];}
    float getLongitude() {return data[2][timerLine];}
    float getLongitudeHP() {return data[3][timerLine];}
    float getGPSPrecision() {return data[4][timerLine];} //Units: mm
    float getLinAccelX() {return data[5][timerLine];}
    float getLinAccelY() {return data[6][timerLine];}//change scaling
    float getLinAccelZ() {return data[7][timerLine];}//change scaling
    float getAbsOrenX() {return data[8][timerLine];}//change scaling
    float getAbsOrenY() {return data[9][timerLine];}//change scaling
    float getAbsOrenZ() {return data[10][timerLine];}//change scaling
    float getAngVeloX() {return data[11][timerLine];}//change scaling
    float getAngVeloY() {return data[12][timerLine];}//change scaling
    float getAngVeloZ() {return data[13][timerLine];}//change scaling
    float getFRtemp1() {return data[14][timerLine];}//change scaling
    float getFRtemp2() {return data[15][timerLine];}//change scaling
    float getFRtravel() {return data[16][timerLine];}//change scaling
    float getFRspeed() {return data[17][timerLine];}//change scaling
    float getFRpsi() {return data[18][timerLine];}//change scaling
    float getFLtemp1() {return data[19][timerLine];}//change scaling
    float getFLtemp2() {return data[20][timerLine];}//change scaling
    float getFLtravel() {return data[21][timerLine];}//change scaling
    float getFLspeed() {return data[22][timerLine];}//change scaling
    float getFLpsi() {return data[23][timerLine];}//change scaling
    float getRRtemp1() {return data[24][timerLine];}//change scaling
    float getRRtemp2() {return data[25][timerLine];}//change scaling
    float getRRtravel() {return data[26][timerLine];}//change scaling
    float getRRspeed() {return data[27][timerLine];}//change scaling
    float getRRpsi() {return data[28][timerLine];}//change scaling
    float getRLtemp1() {return data[0][timerLine];}//change scaling
    float getRLtemp2() {return data[29][timerLine];}//change scaling
    float getRLtravel() {return data[30][timerLine];}//change scaling
    float getRLspeed() {return data[31][timerLine];}//change scaling
    float getRLpsi() {return data[32][timerLine];}//change scaling
    unsigned long getAge(){return data[33][timerLine];} //time since last data packet
};




struct Sensors_Pedals1
{
    vector<vector<double>> data;
    Sensors_Pedals1(string filename){
        data = read_csv(filename);
    }

    float getAPPS1() {return data[0][timerLine];} //Pedal position [0-100]
    float getAPPS2() {return data[1][timerLine];} //Pedal position [0-100]
    boolean getBrakeLimit() {return data[2][timerLine];} //Might not work?
    int getBrakePressure1() {return data[3][timerLine];} //psi
    int getBrakePressure2() {return data[4][timerLine];} //psi
    unsigned long getAge(){return data[5][timerLine];} //time since last data packet
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
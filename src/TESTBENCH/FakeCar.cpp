//@nikunjparasar
#include "FakeCar.h"
#include <SPI.h>
#include <SD.h>


// FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can1;
// CAN_message_t msg;
// File logFile;

// unsigned long lastRecieveTime=millis();

// unsigned long stopwatch=0;
// bool canSend = false;

// bool hasSD = false;



/*********************************************************************************************************
** Stuff
** 
*********************************************************************************************************/

//TODO - Make log that has seperate files for data and CAN
//     - Ping function for each node or something (mostly done)
//     - Make it so the CAN bus of the teensy can be easily chosen and support multiple can busses at a time



FakeCar::FakeCar(bool s){canSend = s;}

// bool FakeCar::begin(){   //Coordinate the magic CAN pixies to dance together 
//     Serial.begin(115200);
//     msg.flags.extended = 1;
//     hasSD=SD.begin(BUILTIN_SDCARD);
//      if(hasSD){
//         String filename = "test0.csv";
//         int filenum = 0;
//         char a[500];
//         filename.toCharArray(a,500);
//         while(SD.exists(a)){
//             filenum++;
//             filename = "test"+(String)filenum+".csv";
//             filename.toCharArray(a,500);
//         }
//         logFile = SD.open(a, O_CREAT | O_WRITE);
//         stuffz.hasSD2 = hasSD;
//         stuffz.logFile = logFile;
//     }
//     can1.begin();
//     can1.setBaudRate(1000000);
//     return true;
// }




// bool FakeCar::readData(){    //Read data from the inverter or the BMS
//     lastRecieveTime = millis();
//     if(!can1.read(msg)){ // fix this line I beg you
//     //Serial.println("no");
//         return 0;
//     }
//     if(!msg.flags.extended){
//         Serial.println("WHAT IS THIS SHIT???? I WANT AN EXTENDED FRAME!!!! COME ON DUDE");
//         return false;
//     }
//     stuffz.CAN_CSV(msg);
//     if((msg.id & 0xFF) == DTI.ID){
//         DTI.receive(msg.id, msg.buf);
//     }
//     else if(msg.id == BMS.ID){
//         BMS.receive(msg.id, msg.buf);
//         Serial.print("BMS "); Serial.println(msg.id);
//     }
//     else if(msg.id == 105){
//         Serial.println(micros()-stopwatch);
//     }
//     else{
//         Serial.print("Unknown CAN Id "); Serial.println(msg.id);
//     }
//     return true;
// }

// bool FakeCar::readData(INT32U *tim){//Read function that gives the time since the last read
//     *tim = millis() - lastRecieveTime;
//     return readData();
// }

// void FakeCar::rawData(INT32U *id, INT8U *buffer){*id=msg.id; buffer=msg.buf;}  //Gives back the raw Id and data array

// void FakeCar::BMSrequest(int pid){
//     Serial.println("BMSREQUEST MIGHT BE WRONG");
//     byte stuff[8] = {(byte)(pid & 0xFF00), (byte)(pid & 0xFF), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};//MGITH BE WRONG
//     if(canSend){send(BMS.ID, stuff);} //this line too
//     else{Serial.println("Nope you can't request BMS data cuz ur a reciever. So sad. Go cry about it");}
// }
// void FakeCar::send(long OutId, long data, int dataLength){    //Sends 8 bytes with that Id and that data shifted left all the way
//     byte stuff[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//     for(int i=0; i<dataLength; i++)
//         stuff[i] = (data >> (i*8));
//     for (int i = 0; i < 8; i++)
//         msg.buf[i] = stuff[i];
//     msg.id = OutId;
//     if(canSend){can1.write(msg);} //por favor mi amor
//     else{Serial.println("YOU TRIED TO SEND????? - note this will prob appear when recieving from the bms actually nevermind ill fix that now");}
// }
// void FakeCar::send(long OutId, byte stuff[]){    //Sends 8 bytes with that Id and that data shifted left all the way
//     for (int i = 0; i < 8; i++)
//         msg.buf[i] = stuff[i];
//     msg.id = OutId;
//     if(canSend){can1.write(msg);} //por favor mi amor
//     else{Serial.println("YOU TRIED TO SEND????? - note this will prob appear when recieving from the bms actually nevermind ill fix that now");}
// }

void FakeCar::sendDashError(byte error){
    Serial.println("DASHBOARD ERROR CODE " + error);
}


// void FakeCar::ping(byte id){
//     msg.id = id;
//     stopwatch=micros();
//     can1.write(msg);
// }





/*********************************************************************************************************
** Getter/Setter Stuff
** 
*********************************************************************************************************/

// bool FakeCar::getTrue(){return true;}         //Just returns true *For testing*
// bool FakeCar::getFalse(){return false;}       //Just returns true *For testing*




/*********************************************************************************************************
** Datalogging/Debuging
** 
*********************************************************************************************************/


// void FakeCar::log(){
// if(!hasSD){
//     Serial.println("No SD card");
//     return;
// }
// String write = "";

// write+=(String)millis()+",";  // format? time, dunno
// for(int i=0; i<5; i++){
//     for(int o=0; o<8; o++)
//         write+=((String)DTI.data[i][o]+",");
// }
// logFile.println(write);
// logFile.flush();
// }



// void FakeCar::printer(){
//     for(int i=0; i<5; i++){
//         for(int o=0; o<8; o++){
//         Serial.print(DTI.data[i][o]);
//         Serial.print(" ");
//         }
//         Serial.println();
//     }
//     Serial.println();
// }

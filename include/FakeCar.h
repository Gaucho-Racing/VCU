// @nikunjparasar


// #define INT8U byte
// #define INT32U unsigned long

#ifndef FAKECAR_H
#define FAKECAR_H

// #define Sender true
// #define Reciever false

#include "FlexCAN_T4.h"
#include <string>
#include "FakeNodes.h"
using namespace std;


class FakeCar
{
public:


    // FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can1;



    // CAN_message_t msg;
    bool canSend = false;
    
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            NODES WITH CSV
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

    Inverter1 DTI = Inverter1();
    Battery1 BMS = Battery1();
    Isolation_Monitor1 IMD = Isolation_Monitor1();
    Charger1 charger = Charger1();
    Sensors1 sensors = Sensors1();
    Sensors_Pedals1 pedals = Sensors_Pedals1();
    // VCU vcu = VCU(2021);
    // Debug stuffz = Debug(0);
   

    FakeCar(bool);
    // bool readData();
    // bool readData(INT32U*);
    // void getData();
    // bool begin();
    bool getTrue();
    bool getFalse();
    // void rawData(INT32U*, INT8U*);
    // void setDtiID(INT8U);
    // void setBmsId(INT8U);
    

    // bool BMSSHIT();
    

////////////////////////something to return id and data or somehitng

    // FOR SENDING SHIT WE CAN TEST ON ACTUAL FLEXCAN TESTBENCH
    // void send(long, long, int);
    // void send(long , byte[]);
    // void sendToInv(int, long, int);
    void sendDashError(byte);
    // void ping(byte);
    // void BMSrequest(int);
    // void log();
    // void printer();
};
#endif

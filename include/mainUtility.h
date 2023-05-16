//mainUtility.h
// @rt.z, @Th3Will

#ifndef MAIN_UTILITY
#define MAIN_UTILITY

#include <string>

void TS_WARN_Check(FakeCar &car);

//need extern to modify across files apparently
struct carFailure {

    //dash
    volatile bool sendToDash;
    //message to send to dash
    volatile std::string errMess;
};
//sub-system declarations 

#endif

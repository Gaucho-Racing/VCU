//on.cpp
#include <iostream>
//relevant files

using namespace std;

//Run all code for initialization; 
//One deliberate Systems check, 
//Read info from can and send to dashboard, 
//check for all conditions to allow for ON_READY
States on() {
    while(1){
        //Get data
        motorOutput = 0;
        //Send data to dash

        if(Systemscheck()){
            return ON_READY;
        }
    }
}

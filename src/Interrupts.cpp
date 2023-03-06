// code for various possible interrupts
// Nikunj Parasar

#include <avr/io.h>
#include <avr/interrupt.h>

// interrupt masks and flag bytes: https://www.pjrc.com/teensy/interrupts.html


//BSPD/APPS interference BSPD>.25 and Brakes engages
//this is not actually highest priority interrupt, im just testing stuff out

//byte, bit# for INT0_vect:	EIMSK,IINT0 --> this bit needs to be enabled somewhere

ISR(INT0_vect) {
    //realistically this can only happen during MOTOR_THROTTLE/DRIVE state
    States stateFrom = state; //store the state that we came from before interrupt triggered
    state = ERROR;
    while (getAPPS() > 0.25 && (getBrakePressure1() || getBrakePressure2())) {
        setCurrent(0.0);    
        cout << "Current Limited through BSPD/APPS Plausibility"
    }
    state = stateFrom; //restore current state
}


ISR(INT1_vect) {
    
}
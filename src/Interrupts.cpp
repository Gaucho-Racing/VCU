// code for various possible interrupts
// Nikunj Parasar


//THIS IS OUTDATED DO NOT USE//////////////////////////////////////

#include <avr/io.h>
#include <avr/interrupt.h>

// interrupt masks and flag bytes: https://www.pjrc.com/teensy/interrupts.html


//BSPD/APPS interference BSPD>.25 and Brakes engaged
//this is not actually highest priority interrupt, im just testing stuff out

//byte, bit# for INT0_vect:	EIMSK,IINT0 --> this bit needs to be enabled somewhere

//first need to reset interrupt flag which is EIFR,INTF0
// then set the interrupt mask above
//finally enable global interrupts 

//these need to be done with bit wise operations, which are documented on teensy website

//will add to this as the week goes on, but this should be the format in which interupts are defined and implemented

//Need to ask josh today at meeting abt how to do the mask bit stuff




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
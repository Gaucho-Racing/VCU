//off.cpp

// Starts at this state when the car is unlocked
States off() {
    while(1) {
        // Start power to necessary things 
        // Get whether on or off (some function) (see below if statement) 
        if(onPressed()){
            return ON;
        }
        if(getCurrent() > 0){
            return CHARGE_PRECHARGE;
        } 
        
        currentState = OFF;
        // No default return value ?
    }
}

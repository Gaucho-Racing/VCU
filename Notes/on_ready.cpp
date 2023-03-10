// on_ready.cpp

States on_ready() {
    while(1) {
        // global variable motorOutput
        motorOutput = 0;
        // Get necessary data
        // if drive mode engaged
        if(drive()){
            return MOTOR_OFF;
        }
    }
}

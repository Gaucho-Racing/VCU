// on_ready.cpp

States ON_READY() {
    while(1) {
         // global variable motorOutput
         //motorOutput = 0;
         setRCurrent(0);
         // Get necessary data
         // if drive mode engaged
         if(drive()) {
            return MOTOR_OFF;
         }
    }
}

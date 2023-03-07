#include bullshit;

States drive() {
  while(1) {
    
    // if throttle not applied
    if(getThrottleIn() == 0) {
      return ON_READY;
    }
    
    // brake pedal plausibility check
    if(getThrottleIn() > 25 && getBrakeIn() > 0) {
      setRcurrent(0);
    }
    
    // set motor output
    setRCurrent(motorOut(getThrottleIn());   
  
  }
}

float motorOut(float throttle ) {
  // i'm assuming throttle is a value between 0 and 100
  // can adjust accordingly later
  
  // figure out range from getXXspeed()
  float front = ( getFRspeed() + getFFspeed() ) / 2; // CAN typo lol, should be FL not FF
  float rear = ( getRRspeed() + getRLspeed() ) / 2;

  // wheels slipping: traction control
  if (rear > front) {
    // adjust 0.1 factor in testing
    return throttle - 0.1 * (rear - front);
  }

  else {
    return throttle;
  }
  
}

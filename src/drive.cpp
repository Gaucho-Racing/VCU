#include bullshit;

States drive() {
  while(1) {
    
    // if throttle not applied
    if(getAPPS() == 0) {
      return ON_READY;
    }
    
    // brake system plausibility check
    // temporary or redundant
    // getBrakePressure ????
    if(getAPPS() > 25 && getBrakeIn() > 0) {
      setRcurrent(0);
      return OFF; // STUB - will replace with interrupt
    }
    
    // set motor output
    setRCurrent(motorOut(getAPPS());   
  
  }
}

float motorOut(float throttle) {
  // i'm assuming throttle is a value between 0 and 100
  // can adjust accordingly later
  
  // figure out range/scaling from getXXspeed()
  // also not sure if avg is the best way to go
  float front = ( getFRspeed() + getFFspeed() ) / 2; // CAN typo lol, should be FL not FF
  float rear = ( getRRspeed() + getRLspeed() ) / 2; // MIGHT CHANGE TO MOTOR SPEED IN FUTURE

  // wheels slipping: traction control
  // multiplied by 10 is because of some CAN scaling shit
  if (rear > front) {
    // adjust 0.1 factor in testing
    return 10 * (throttle - 0.1 * (rear - front));
  }

  else {
    return 10 * (throttle);
  }
  
}

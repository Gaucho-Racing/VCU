#include "drive.h";

I_no_can_speak_flex car(true);

float motorOut(float throttle) {
  // i'm assuming throttle is a value between 0 and 100
  // can adjust accordingly later
  
  // figure out range/scaling from getXXspeed()
  // also not sure if avg is the best way to go
  float front = ( car.sensors.getFRspeed() + car.sensors.getFLspeed() ) / 2; // CAN typo lol, should be FL not FF
  float rear = ( car.sensors.getRRspeed() + car.sensors.getRLspeed() ) / 2; // MIGHT CHANGE TO MOTOR SPEED IN FUTURE

  // wheels slipping: traction control
  // multiplied by 10 is because of some CAN scaling shit
  if (rear > front) {
    // adjust 0.1 factor in testing
    // also add threshold for it to turn on
    return 10 * (throttle - 0.1 * (rear - front));
  }

  else {
    return 10 * (throttle);
  }
  
}

States drive(I_no_can_speak_flex cool_boi) {    
    // if throttle not applied
    if(car.pedals.getAPPS() == 0) {
      return ON_READY;
    }
    
    // set motor output
    car.DTI.setRCurrent(motorOut(car.pedals.getAPPS()));   
    
    return DRIVE;
}

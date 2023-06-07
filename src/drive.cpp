//drive.cpp
// @nikunjparasar, @rt.z

#include "main.h";
#include "onOffUtility.h";
#include <unordered_map>

float motorOut(float throttle, int maxCurrent, I_no_can_speak_flex& car, Switchboard& s) {
  // i'm assuming throttle is a value between 0 and 100
  // can adjust accordingly later
  
  // figure out range/scaling from getXXspeed()
  // also not sure if avg is the best way to go
  // float front = ( car.sensors.getFRspeed() + car.sensors.getFLspeed() ) / 2; // CAN typo lol, should be FL not FF
  // float rear = ( car.sensors.getRRspeed() + car.sensors.getRLspeed() ) / 2; // MIGHT CHANGE TO MOTOR SPEED IN FUTURE

   return 10 * (throttle);
  // // wheels slipping: traction control
  // // multiplied by 10 is because of some CAN scaling shit
  // if ( s.traction_control && rear  > front*1.25) {
  //   // adjust 0.1 factor in testing
  //   // also add threshold for it to turn on
    
  //   return 10 * (throttle - 0.1 * (rear - front));
  // }
  
}

States drive(I_no_can_speak_flex& car, Switchboard& s) {
    int brightness_fact = 50;
    if (!s.drive_enable) return OFF;
    led.clear();
    int R = s.COLOR_MAPPING[static_cast<int>(s.ROTARY_TEST_ACCEL * 1000) / 1000.0].first/brightness_fact;
    int B = s.COLOR_MAPPING[static_cast<int>(s.ROTARY_TEST_ACCEL * 1000 )/ 1000.0].second.second/brightness_fact;
    int G = s.COLOR_MAPPING[static_cast<int>(s.ROTARY_TEST_ACCEL * 1000) / 1000.0].second.first/brightness_fact;
    led.setPixelColor(0, led.Color(G,B,R));
    led.setPixelColor(1, led.Color(G,B,R));
    led.setPixelColor(2, led.Color(G,B,R));
    led.setPixelColor(3, led.Color(G,B,R));   
    

    led.show();
    // if throttle not applied
    // if((car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 <= 0.05) 
    if(s.ROTARY_TEST_ACCEL < 0.1){
      return ON_READY;
    }
      
    
    // set motor output
    car.DTI.setDriveEnable(1);
    car.DTI.setRCurrent(motorOut(s.ROTARY_TEST_ACCEL, 50, car, s));

    // car.DTI.setRCurrent(motorOut((car.pedals.getAPPS1()+car.pedals.getAPPS2())/2, car, s));
    return DRIVE;
}


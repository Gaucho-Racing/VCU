//drive.cpp
// @nikunjparasar

#include "main.h";
#include "onOffUtility.h";


float motorOut(float throttle, I_no_can_speak_flex& car, Switchboard& s) {

  // float front = ( car.sensors.getFRspeed() + car.sensors.getFLspeed() ) / 2; // CAN typo lol, should be FL not FF
  // float rear = ( car.sensors.getRRspeed() + car.sensors.getRLspeed() ) / 2; // MIGHT CHANGE TO MOTOR SPEED IN FUTURE
  const int HIGH_PWR_R_CURRENT = 50;
  const int LOW_PWR_R_CURRENT = 20;

  return s.full_pwr ? HIGH_PWR_R_CURRENT* throttle : LOW_PWR_R_CURRENT*throttle;
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
    int R = s.COLOR_MAPPING[static_cast<int>(s.ROTARY_TEST_ACCEL * 1000) / 1000.0].first/brightness_fact;
    int B = s.COLOR_MAPPING[static_cast<int>(s.ROTARY_TEST_ACCEL * 1000 )/ 1000.0].second.second/brightness_fact;
    int G = s.COLOR_MAPPING[static_cast<int>(s.ROTARY_TEST_ACCEL * 1000) / 1000.0].second.first/brightness_fact;
    led.setPixelColor(0, led.Color(G,B,R));
    led.setPixelColor(1, led.Color(G,B,R));
    led.setPixelColor(2, led.Color(G,B,R));


    if(s.full_pwr){
      if(millis()%1000 < 500){
        led.setPixelColor(3, led.Color(0, 0, 0));
        led.show();
      }else{
        led.setPixelColor(3, led.Color(0, 0, 255/10));
        led.show();
      }
    }
    else{
      if(millis()%1000 < 500){
        led.setPixelColor(3, led.Color(0, 0, 0));
        led.show();
      }else{
        led.setPixelColor(3, led.Color(0, 255/10, 255/10));
        led.show();
      }
    }
    

    led.show();
    // if throttle not applied
    // if((car.pedals.getAPPS1()+car.pedals.getAPPS2())/2 <= 0.05) 
    if(s.ROTARY_TEST_ACCEL < 0.05){
      return ON_READY;
    }
      
    
    // set motor output
    car.DTI.setDriveEnable(1);
    car.DTI.setRCurrent(motorOut(s.ROTARY_TEST_ACCEL, car, s));

    // car.DTI.setRCurrent(motorOut((car.pedals.getAPPS1()+car.pedals.getAPPS2())/2, car, s));
    return DRIVE;
}


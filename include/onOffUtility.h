//onOffUtility.h
// @rt.z

#ifndef ON_OFF_UTILITY
#define ON_OFF_UTILITY


//returns true if there is current running to the motor
bool onPressed(FakeCar &car);

bool isRejectingStartup(FakeCar &car);
bool criticalCheck(FakeCar &car, bool send_dash_errors = true);
bool warningCheck(FakeCar &car, bool send_dash_warnings = true);

bool driveEngaged(FakeCar &car);

#endif

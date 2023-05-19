//onOffUtility.h
// @rt.z

#ifndef ON_OFF_UTILITY
#define ON_OFF_UTILITY


//returns true if there is current running to the motor
bool onPressed(I_no_can_speak_flex &car);

bool isRejectingStartup(I_no_can_speak_flex &car, bool send_dash_errors = true);
bool criticalCheck(I_no_can_speak_flex &car, bool send_dash_errors = true);
bool warningCheck(I_no_can_speak_flex &car, bool send_dash_warnings = true);

bool driveEngaged(I_no_can_speak_flex &car);

#endif

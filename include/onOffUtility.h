//onOffUtility.cpp
// @yarwinliu, @rt.z, 03122023

#ifndef ON_OFF_UTILITY
#define ON_OFF_UTILITY


//returns true if there is current running to the motor
bool onPressed(I_no_can_speak_flex &car);

std::vector<int> startupCheck(I_no_can_speak_flex &car);

bool driveEngaged(I_no_can_speak_flex &car);

#endif

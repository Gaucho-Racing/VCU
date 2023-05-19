//onOffUtility.h
// @rt.z

#ifndef ON_OFF_UTILITY
#define ON_OFF_UTILITY

bool isRejectingStartup(FakeCar &car, bool send_dash_errors = true);
bool criticalCheck(FakeCar &car, bool send_dash_errors = true);
bool warningCheck(FakeCar &car, bool send_dash_warnings = true);

#endif

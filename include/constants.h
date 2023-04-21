#ifndef CONSTANTS
#define CONSTANTS
using namespace std;
//canIDs


//thresholds
/*should be used for checking whether a subsystem is within the healthy limit
 i.e. current is less than 50 or some other number*/
const byte CELL_TEMP_WARN = 57; // Deg Centigrade
const byte CRITICAL_CELL_TEMP = 60;  // Deg Centigrade
const int CELL_OVERHEAT_CURRENT_LIMIT = 60; //kW

const float CHARGING_VOLTAGE = 208; //volts

const int VALUE_MOT_TEMP_MAX = 0;
const int VALUE_MOT_TEMP_MIN = 0;
const float VALUE_NO_CURRENT = 0;
const float VALUE_APPS_BSPD_THROTTLE = 0.25;
const int VALUE_MIN_BRAKE_PRESSURE = 0;
const float VALUE_MIN_CURRENT_THRESHOLD = 0;
const int VALUE_HARD_BRAKE_LIMIT = 0;
const float VALUE_APPS_UNRESPONSIVE_MAX = 0;
const byte VALUE_CRITICAL_MOTOR_TEMP = 0;
const float VALUE_MIN_RESPONSIVE_CURRENT_MOTOR = 0;
const float VALUE_DTI_CURRENT_THRESHOLD = 0;
const float VALUE_G_FORCE_LIMIT = 0;

const float VALUE_MAX_CURRENT_DRAW_HIGH_MOTOR = 0;

#endif
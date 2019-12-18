#pragma once
#include "include.h"

const int MODE_ARDUINO_DISCONNECTED = 0;
const int MODE_ARDUINO_DETECTED = 1;
const int MODE_ARDUINO_CONNECTED = 2;

const int MOTORS_DISARMED = 0;
const int MOTORS_ARMING_IN_PROGRESS = 1;
const int MOTORS_ARMED = 2;
const int MOTORS_DISARMING_IN_PROGRESS = 3;

struct ArduinoState {
    int ArduinoDisonnected = 0;
    int ArduinoDetected = 1;
    int ArduinoConnected = 2;
};

struct Modes {
    int leftX = 0;
    int leftY = 0;
    int rightX = 0;
    int rightY = 0;
    bool radioSending = false;
    int motorsArmed = MOTORS_DISARMED;
    bool throttleModeActive = false;
    double thrust = 0.0;
    double buttons = 0.0;
};

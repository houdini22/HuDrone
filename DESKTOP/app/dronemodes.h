#ifndef DRONEMODES_H
#define DRONEMODES_H

#include "include.h"

const int MODE_ARDUINO_DISCONNECTED = 0;
const int MODE_ARDUINO_DETECTED = 1;
const int MODE_ARDUINO_CONNECTED = 2;

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
    bool motorsArmed = false;
    bool throttleModeActive = false;
    double thrust = 1.0;
};


#endif // DRONEMODES_H

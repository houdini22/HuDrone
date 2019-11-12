#ifndef BUTTONS_H
#define BUTTONS_H

#include "include.h"

struct ButtonsPressed {
    double leftX = 0.0;
    double leftY = 0.0;
    double rightX = 0.0;
    double rightY = 0.0;
    bool start = false;
    bool arming = false;
    bool a = false;
    bool b = false;
    bool x = false;
    bool y = false;
    bool leftShoulder = false;
    bool rightShoulder = false;
    bool dPadLeft = false;
    bool dPadRight = false;
    bool dPadUp = false;
    bool dPadDown = false;
};

Q_DECLARE_METATYPE(ButtonsPressed)

#endif // BUTTONS_H

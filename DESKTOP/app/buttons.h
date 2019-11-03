#ifndef BUTTONS_H
#define BUTTONS_H

#include "include.h"

struct ButtonsPressed {
    int leftX = 1100;
    int leftY = 1500;
    int rightX = 1500;
    int rightY = 1500;
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

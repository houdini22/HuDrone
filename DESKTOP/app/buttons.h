#ifndef BUTTONS_H
#define BUTTONS_H

#include "include.h"

struct SteeringGamepadButtons {
    double leftX = 0.0;
    double leftY = 0.0;
    double rightX = 0.0;
    double rightY = 0.0;
    bool a = false;
    bool b = false;
    bool x = false;
    bool y = false;
    bool l1 = false;
    bool l2 = false;
    bool r1 = false;
    bool r2 = false;
    bool l3 = false;
    bool r3 = false;
    bool select = false;
    bool start = false;
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool center = false;
    bool guide = false;
};

Q_DECLARE_METATYPE(SteeringGamepadButtons)

#endif // BUTTONS_H

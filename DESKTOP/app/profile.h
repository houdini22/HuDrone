#ifndef PROFILE_H
#define PROFILE_H

#include "include.h"

class Profile {
public:
    Profile(T_JSON);
    int getLeftX(double);
    int getLeftY(double);
    int getRightX(double);
    int getRightY(double);
private:
    T_JSON _configuration;
    T_JSON getFunction(QString name);
    int getValueToSend(T_JSON channelConfig, double value, bool invert);
};

#endif // PROFILE_H

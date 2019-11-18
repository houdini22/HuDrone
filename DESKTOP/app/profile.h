#ifndef PROFILE_H
#define PROFILE_H

#include "include.h"

class Profile {
public:
    Profile(T_JSON);
    static Profile * byName(QString name);
    int getLeftX(double);
    int getLeftY(double);
    int getMinLeftY();
    int getMaxLeftY();
    int getRightX(double);
    int getRightY(double);
    int getThrottleSteps();
    QString getChannelNumberOf(QString);
private:
    T_JSON _configuration;
    T_JSON getFunction(QString name);
    int getValueToSend(T_JSON channelConfig, double value, bool invert, bool fromMin = false);
};

#endif // PROFILE_H

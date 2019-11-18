#ifndef PROFILE_H
#define PROFILE_H

#include "include.h"

class Profile {
public:
    Profile(T_JSON);
    static Profile * byName(QString);
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
    QMap<QString, QString> getFunction(QString);
    int getValueToSend(QMap<QString, QString>, double, bool, bool fromMin = false);
    QMap<QString, QString> _channelNumbers;
    QMap<QString, QMap<QString, QString>> _channelFunctions;
    int _throttleSteps = 0;
};

#endif // PROFILE_H

#ifndef TIMERARDUINOPING_H
#define TIMERARDUINOPING_H

#include "include.h"

class TimersArduino;
class Drone;
class SendingRegistry;
class SteeringRegistry;
class Profile;

class TimerArduinoPing : public TimerArduinoAbstract {
    Q_OBJECT
public:
    explicit TimerArduinoPing(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
public slots:
    void execute();
};

#endif // TIMERARDUINOPING_H

#ifndef TIMERARDUINOSEND_H
#define TIMERARDUINOSEND_H

#include "include.h"

class TimersArduino;
class Drone;
class SendingRegistry;
class SteeringRegistry;
class Profile;

class TimerArduinoSend : public TimerArduinoAbstract {
    Q_OBJECT
public:
    explicit TimerArduinoSend(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
public slots:
    void execute();
};

#endif // TIMERARDUINOSEND_H

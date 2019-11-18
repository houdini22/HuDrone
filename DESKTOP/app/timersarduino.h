#ifndef TIMERSARDUINO_H
#define TIMERSARDUINO_H

#include "include.h"

class Drone;
class SendingRegistry;
class SteeringRegistry;
class Profile;
class TimerArduinoPing;
class TimerArduinoSend;

class TimersArduino {
public:
    TimersArduino(Drone * drone, SendingRegistry *, SteeringRegistry *, Profile *);
    ~TimersArduino();
    void start();
    void stop();
    void timeout();
private:
    TimerArduinoPing * _timer_arduino_ping;
    TimerArduinoSend * _timer_arduino_send;
};

#endif // TIMERSARDUINO_H

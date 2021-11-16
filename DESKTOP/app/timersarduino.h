#pragma once
#include "include.h"

class Drone;
class SendingRegistry;
class SteeringRegistry;
class Profile;
class TimerArduinoPing;
class TimerArduinoSend;
class TimerArduinoAbstract;
class TimerThread;

class TimersArduino {
public:
    explicit TimersArduino(Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    ~TimersArduino();
    void start();
    void stop();
    void timeout();
private:
    //TimerArduinoPing * _timer_arduino_ping = nullptr;
    TimerArduinoSend * _timer_arduino_send = nullptr;
    Drone * _drone = nullptr;
};

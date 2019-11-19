#include "include.h"

TimerArduinoPing::TimerArduinoPing(TimersArduino * timers, Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile)
    : TimerArduinoAbstract(timers, drone, sendingRegistry, steeringRegistry, profile) {
    connect(this->_timer, SIGNAL(timeout()), this, SLOT(execute()), Qt::DirectConnection);
}

int TimerArduinoPing::getMiliseconds() {
    return 100;
}

void TimerArduinoPing::execute() {
    this->send("p", true);
}

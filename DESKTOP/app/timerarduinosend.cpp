#include "include.h"

TimerArduinoSend::TimerArduinoSend(TimersArduino * timers, Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile)
    : TimerArduinoAbstract(timers, drone, sendingRegistry, steeringRegistry, profile) {
    connect(this->_timer, SIGNAL(timeout()), this, SLOT(execute()), Qt::DirectConnection);
}

int TimerArduinoSend::getMiliseconds() {
    return 20;
}

void TimerArduinoSend::execute() {

}

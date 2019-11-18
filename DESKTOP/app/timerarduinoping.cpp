#include "include.h"

TimerArduinoPing::TimerArduinoPing(TimersArduino * timers, Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile)
    : TimerArduinoAbstract(timers, drone, sendingRegistry, steeringRegistry, profile) {

}

void TimerArduinoPing::execute() {
    qDebug() << "Timer...";
}

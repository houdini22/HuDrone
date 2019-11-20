#include "include.h"

TimersArduino::TimersArduino(Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile) {
    this->_drone = drone;

    this->_timer_arduino_ping = new TimerArduinoPing(this, drone, sendingRegistry, steeringRegistry, profile);
    this->_timer_arduino_send = new TimerArduinoSend(this, drone, sendingRegistry, steeringRegistry, profile);
}

TimersArduino::~TimersArduino() {
    delete this->_timer_arduino_ping;
    delete this->_timer_arduino_send;
}

void TimersArduino::start() {
    this->_timer_arduino_ping->start();
    this->_timer_arduino_send->start();
}

void TimersArduino::stop() {
    this->_timer_arduino_ping->stop();
    this->_timer_arduino_send->stop();
}

void TimersArduino::timeout() {

}

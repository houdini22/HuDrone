#include "include.h"

TimerArduinoAbstract::TimerArduinoAbstract(TimersArduino * timers, Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile) {
    this->_timer = new QTimer(nullptr);
    this->_thread = new QThread(this);
    this->_timers = timers;
    this->_drone = drone;
    this->_sending_registry = sendingRegistry;
    this->_steering_registry = steeringRegistry;
    this->_profile = profile;

    qDebug() << "Timer created.";
}

TimerArduinoAbstract::~TimerArduinoAbstract() {
    delete this->_thread;
    delete this->_timer;
}

void TimerArduinoAbstract::start() {
    this->_timer->setInterval(this->getMiliseconds());
    this->_timer->moveToThread(this->_thread);
    this->_thread->start();
}

void TimerArduinoAbstract::stop() {
    this->_thread->terminate();
    this->_thread->wait();
}

void TimerArduinoAbstract::timeout() {
    qDebug() << "Timeout.";
    this->_timers->timeout();
}

void TimerArduinoAbstract::send(const QString & buffer, bool check = false) {
    if (this->_sending_registry->getData()->contains("arduino0")) {
        QSerialPort * arduino = this->_sending_registry->getData()->take("arduino0")->service;
        if (arduino->isOpen()) {
            if (buffer.length() > 0) {
                arduino->write(buffer.toStdString().c_str(), buffer.length());
                if (check) {
                    if (!arduino->waitForBytesWritten(1000)) {
                        this->timeout();
                    }
                }
            }
        } else {
            this->timeout();
        }
    }
}

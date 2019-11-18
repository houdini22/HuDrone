#include "include.h"

TimerArduinoAbstract::TimerArduinoAbstract(TimersArduino * timers, Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile)
    : QObject() {
    this->_timer = new QTimer(this);
    this->_timers = timers;
    this->_drone = drone;
    this->_sending_registry = sendingRegistry;
    this->_steering_registry = steeringRegistry;
    this->_profile = profile;

    connect(_timer, SIGNAL(timeout()), this, SLOT(execute()));
}

void TimerArduinoAbstract::start(int miliseconds) {
    _timer->start(miliseconds);
}

void TimerArduinoAbstract::stop() {
    _timer->stop();
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

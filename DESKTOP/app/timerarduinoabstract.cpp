#include "include.h"

TimerArduinoAbstract::TimerArduinoAbstract(TimersArduino * timers, Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile) {
    this->_thread = new TimerThread();
    this->_timer = new QTimer(this->_thread);
    this->_thread->setTimer(this->_timer);
    this->_timers = timers;
    this->_drone = drone;
    this->_sending_registry = sendingRegistry;
    this->_steering_registry = steeringRegistry;
    this->_profile = profile;

    connect(sendingRegistry, SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData *> *)), this, SLOT(slotSendingsDataChanged(QHash<QString, SendingData *> *)));
}

void TimerArduinoAbstract::slotSendingsDataChanged(QHash<QString, SendingData *> * sendingData) {
    this->_sending_data = sendingData;
}

TimerArduinoAbstract::~TimerArduinoAbstract() {
    delete this->_timer;
    delete this->_thread;
}

void TimerArduinoAbstract::start() {
    this->_timer->setInterval(this->getMiliseconds());
    this->_thread->start();
}

void TimerArduinoAbstract::stop() {
    this->_thread->terminate();
    this->_thread->wait();
}

QTimer * TimerArduinoAbstract::getTimer() {
    return this->_timer;
}

void TimerArduinoAbstract::timeout() {
    qDebug() << "Timeout.";
    this->_timers->timeout();
}

void TimerArduinoAbstract::send(const QString & buffer, bool check = false) {
    if (this->_sending_data != nullptr) {
        if (this->_sending_data->contains("arduino0")) {
            QSerialPort * arduino = this->_sending_data->take("arduino0")->service;
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
}

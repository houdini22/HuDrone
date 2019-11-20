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
}

void TimerArduinoAbstract::slotSendingsDataChanged(QHash<QString, SendingData> data) {
    qDebug() << "TimerArduinoAbstract::slotSendingsDataChanged" << data.size();
    this->_sendings_data = data;
}

void TimerArduinoAbstract::slotSteeringsDataChanged(QHash<QString, SteeringData> data) {
    qDebug() << "TimerArduinoAbstract::slotSteeringsDataChanged" << data.size();
    this->_steerings_data = data;
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
    /*
    if (this->_sending_data.contains("arduino0")) {
        this->_sending_data.take("arduino0")->mode = MODE_ARDUINO_DISCONNECTED;
        this->_sending_data->take("arduino0")->service->close();
    }
    */
    this->_timers->timeout();
}

void TimerArduinoAbstract::send(const QString & buffer, bool check = false) {
    if (this->_sendings_data.contains("arduino0")) {
        qDebug() << 2;
        SendingData data = this->_sendings_data.take("arduino0");
        if (data.mode == MODE_ARDUINO_CONNECTED && data.service != nullptr) {
            qDebug() << 3;
            QSerialPort * arduino = data.service;
            if (arduino->isOpen()) {
                qDebug() << 4;
                if (buffer.length() > 0) {
                    qDebug() << "BUFF: " << buffer;
                    arduino->write(buffer.toStdString().c_str(), buffer.length());
                    if (check) {
                        if (!arduino->waitForBytesWritten(1000)) {
                            this->timeout();
                        }
                    }
                }
            }
        }
    }
}

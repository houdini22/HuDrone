#include "include.h"

SendingArduino::SendingArduino(Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile) : SendingInterface(drone, sendingRegistry, steeringRegistry) {
    this->_data = new SendingData;
    this->_data->name = "arduino0";
    this->_profile = profile;

    connect(this,
            SIGNAL(signalArduinoConnected(QSerialPort *)),
            this->_drone,
            SLOT(slotArduinoConnected(QSerialPort *)));
    connect(this->_sending_registry,
            SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData *> *)),
            this->_drone,
            SLOT(slotSendingsDataChanged(QHash<QString, SendingData *> *)));
    connect(this->_steering_registry,
            SIGNAL(signalSteeringsDataChanged(QHash<QString, SteeringData *> *)),
            this->_drone,
            SLOT(slotSteeringsDataChanged(QHash<QString, SteeringData *> *)));
}

void SendingArduino::start() {    
    this->_thread_box_connect = new ThreadBoxConnect(this->_drone, this->_sending_registry, this->_steering_registry, this->_profile);
    connect(this,
            SIGNAL(signalSendingDataChanged(SendingData *)),
            this->_thread_box_connect,
            SLOT(slotSendingDataChanged(SendingData *)));
    connect(this->_thread_box_connect,
            SIGNAL(arduinoConnected(QSerialPort *)),
            this,
            SLOT(slotArduinoConnected(QSerialPort *)));
    emit signalSendingDataChanged(this->_data);
    this->_thread_box_connect->start();
}

void SendingArduino::stop() {
    disconnect(this,
            SIGNAL(signalArduinoConnected(QSerialPort *)),
            this->_drone,
            SLOT(slotArduinoConnected(QSerialPort *)));
    disconnect(this->_sending_registry,
            SIGNAL(signalSendingsDataChanged(QHash<QString,SendingData*>*)),
            this->_drone,
            SLOT(slotSendingsDataChanged(QHash<QString,SendingData*>*)));
    disconnect(this,
            SIGNAL(signalSendingDataChanged(SendingData*)),
            this->_sending_registry,
            SLOT(slotSendingDataChanged(SendingData*)));
    disconnect(this->_thread_box_connect,
            SIGNAL(signalSendingDataChanged(SendingData *)),
            this,
            SLOT(slotSendingDataChanged(SendingData *)));
    disconnect(this->_thread_box_connect,
            SIGNAL(arduinoConnected(QSerialPort *)),
            this,
            SLOT(slotArduinoConnected(QSerialPort *)));

    this->_thread_box_connect->terminate();
    this->_thread_box_connect->wait();
    delete this->_thread_box_connect;
}

void SendingArduino::slotSendingDataChanged(SendingData * data) {
    this->_data = data;
    emit signalSendingDataChanged(this->_data);
}

void SendingArduino::slotArduinoConnected(QSerialPort * arduino) {
    emit signalArduinoConnected(arduino);
}

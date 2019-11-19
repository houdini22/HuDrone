#include "include.h"

SendingArduino::SendingArduino(Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile) : SendingInterface(drone, sendingRegistry, steeringRegistry) {
    this->_data.name = "arduino0";
    this->_profile = profile;
    this->_thread_box_connect = new ThreadBoxConnect(this->_drone, this->_sending_registry, this->_steering_registry, this->_profile);
}

void SendingArduino::start() {    
    connect(this,
            SIGNAL(signalSendingDataChanged(SendingData)),
            this->_sending_registry,
            SLOT(slotSendingDataChanged(SendingData)));

    emit signalSendingDataChanged(this->_data);
    this->_thread_box_connect->start();
}

void SendingArduino::stop() {
    this->_thread_box_connect->terminate();
    this->_thread_box_connect->wait();

    disconnect(this,
               SIGNAL(signalSendingDataChanged(SendingData)),
               this->_sending_registry,
               SLOT(slotSendingDataChanged(SendingData)));

}

void SendingArduino::slotSendingDataChanged(SendingData data) {
    if (this->_data.name.compare(data.name) == 0) {
        this->_data = data;
    }
}

void SendingArduino::slotArduinoConnected(QSerialPort * arduino) {
    emit signalArduinoConnected(arduino);
}

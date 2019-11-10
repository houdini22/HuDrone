#include "include.h"

SendingArduino::SendingArduino(Drone * drone, SendingRegistry * registry) : SendingInterface(drone, registry) {
    this->_data = new SendingData;
    this->_data->name = "arduino0";
}

void SendingArduino::start() {
    connect(this,
            SIGNAL(signalSendingDataChanged(SendingData*)),
            this->registry,
            SLOT(slotSendingDataChanged(SendingData*)));

    this->_thread_box_connect = new ThreadBoxConnect(this->registry);
    //this->_thread_arduino_ping = new ThreadArduinoPing(this->registry);
    this->_thread_arduino_send = new ThreadArduinoSend(this->drone, this->registry);

    connect(this->_thread_box_connect,
            SIGNAL(signalSendingDataChanged(SendingData *)),
            this,
            SLOT(slotSendingDataChanged(SendingData *)));
    connect(this->_thread_box_connect,
            SIGNAL(arduinoConnected(QSerialPort *)),
            this,
            SLOT(slotArduinoConnected(QSerialPort *)));
    //connect(this->_thread_arduino_ping,
    //        SIGNAL(signalSendingDataChanged(SendingData *)),
    //        this,
    //        SLOT(slotSendingDataChanged(SendingData *)));

    emit signalSendingDataChanged(this->_data);

    this->_thread_box_connect->start();
    //this->_thread_arduino_ping->start();
    this->_thread_arduino_send->start();
}

void SendingArduino::stop() {
    disconnect(this,
            SIGNAL(signalSendingDataChanged(SendingData*)),
            this->registry,
            SLOT(slotSendingDataChanged(SendingData*)));
    disconnect(this->_thread_box_connect,
            SIGNAL(signalSendingDataChanged(SendingData *)),
            this,
            SLOT(slotSendingDataChanged(SendingData *)));
    disconnect(this->_thread_box_connect,
            SIGNAL(arduinoConnected(QSerialPort *)),
            this,
            SLOT(slotArduinoConnected(QSerialPort *)));
    //disconnect(this->_thread_arduino_ping,
    //        SIGNAL(signalSendingDataChanged(SendingData *)),
    //        this,
    //        SLOT(slotSendingDataChanged(SendingData *)));

    this->_thread_box_connect->terminate();
    //this->_thread_arduino_ping->terminate();
    this->_thread_arduino_send->terminate();

    this->_thread_box_connect->wait();
    //this->_thread_arduino_ping->wait();
    this->_thread_arduino_send->wait();

    delete this->_thread_box_connect;
    //delete this->_thread_arduino_ping;
    delete this->_thread_arduino_send;
}

void SendingArduino::slotSendingDataChanged(SendingData * data) {
    this->_data = data;
    emit signalSendingDataChanged(this->_data);
}

void SendingArduino::slotArduinoConnected(QSerialPort * arduino) {
    emit signalArduinoConnected(arduino);
}

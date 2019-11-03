#include "include.h"

SendingArduino::SendingArduino(Drone * drone, SendingRegistry * registry) : SendingInterface(drone, registry) {
    this->data = new SendingData;
    this->data->name = "arduino0";

    connect(this, SIGNAL(signalSendingDataChanged(SendingData*)), this->registry, SLOT(slotSendingDataChanged(SendingData*)));

    this->threadArduinoDetect = new ThreadArduinoDetect(this->registry);
    connect(this->threadArduinoDetect, SIGNAL(signalSendingDataChanged(SendingData *)), this, SLOT(slotSendingDataChanged(SendingData *)));

    this->threadArduinoConnect = new ThreadArduinoConnect(this->registry);
    connect(this->threadArduinoConnect, SIGNAL(signalSendingDataChanged(SendingData *)), this, SLOT(slotSendingDataChanged(SendingData *)));

    this->threadArduinoPing = new ThreadArduinoPing(this->registry);
    connect(this->threadArduinoPing, SIGNAL(signalSendingDataChanged(SendingData *)), this, SLOT(slotSendingDataChanged(SendingData *)));

    this->threadArduinoSend = new ThreadArduinoSend(this->drone, this->registry);
}

void SendingArduino::start() {
    this->threadArduinoDetect->start();
    this->threadArduinoConnect->start();
    this->threadArduinoPing->start();
    this->threadArduinoSend->start();
}

void SendingArduino::slotSendingDataChanged(SendingData * data) {
    this->data = data;
    emit signalSendingDataChanged(this->data);
}

#include "include.h"

SendingArduino::SendingArduino(Drone * drone, SendingRegistry * registry) : SendingInterface(drone, registry) {
    this->data = new SendingData;
    this->data->name = "arduino0";

    connect(this, SIGNAL(signalSendingDataChanged(SendingData*)), this->registry, SLOT(slotSendingDataChanged(SendingData*)));

    this->threadBoxConnect = new ThreadBoxConnect(this->registry);
    connect(this->threadBoxConnect, SIGNAL(signalSendingDataChanged(SendingData *)), this, SLOT(slotSendingDataChanged(SendingData *)));

    this->threadArduinoPing = new ThreadArduinoPing(this->registry);
    connect(this->threadArduinoPing, SIGNAL(signalSendingDataChanged(SendingData *)), this, SLOT(slotSendingDataChanged(SendingData *)));

    this->threadArduinoSend = new ThreadArduinoSend(this->drone, this->registry);
}

void SendingArduino::start() {
    this->threadBoxConnect->start();
    this->threadArduinoPing->start();
    this->threadArduinoSend->start();
}

void SendingArduino::slotSendingDataChanged(SendingData * data) {
    this->data = data;
    emit signalSendingDataChanged(this->data);
}

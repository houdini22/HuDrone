#include "include.h"

SendingRegistry::SendingRegistry(Drone *drone) {
    this->drone = drone;
    this->sendingsData = new QHash<QString, SendingData *>;
    this->modes = new Modes;
}

void SendingRegistry::add(SendingInterface * handler) {
    this->registry.append(handler);
}

void SendingRegistry::start() {
    for (int i = 0; i < this->registry.size(); i += 1) {
        SendingInterface * _interface = this->registry.at(i);
        SendingData * data = _interface->getData();
        this->sendingsData->insert(data->name, data);
        emit signalSendingDataChanged(data);
    }

    emit signalSendingsDataChanged(this->sendingsData);
}

void SendingRegistry::startThreads() {
    for (int i = 0; i < this->registry.size(); i += 1) {
        this->registry.at(i)->start();
    }
}

void SendingRegistry::stopThreads() {
    for (int i = 0; i < this->registry.size(); i += 1) {
        this->registry.at(i)->stop();
    }
}

void SendingRegistry::slotSendingDataChanged(SendingData * data) {
    this->sendingsData->insert(data->name, data);
    emit signalSendingsDataChanged(this->sendingsData);
    emit signalSendingDataChanged(data);
}

Modes * SendingRegistry::getModes() {
    return this->modes;
}

void SendingRegistry::setModes(Modes * modes) {
    this->modes = modes;
    emit signalModesChanged(this->modes);
}

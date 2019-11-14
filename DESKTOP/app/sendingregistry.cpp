#include "include.h"

SendingRegistry::SendingRegistry(Drone *drone) {
    this->_drone = drone;
    this->_sendings_data = new QHash<QString, SendingData *>;
    this->_modes = new Modes;
}

SendingRegistry::~SendingRegistry() {
    delete this->_modes;
    this->_sendings_data->clear();
    delete this->_sendings_data;
    this->_registry.clear();
}

void SendingRegistry::add(SendingInterface * handler) {
    this->_registry.append(handler);
    this->_sendings_data->insert(handler->getData()->name, handler->getData());
    emit signalSendingsDataChanged(this->_sendings_data);
}

void SendingRegistry::start() {}

void SendingRegistry::startThreads() {
    for (int i = 0; i < this->_registry.size(); i += 1) {
        this->_registry.at(i)->start();
    }
}

void SendingRegistry::stopThreads() {
    for (int i = 0; i < this->_registry.size(); i += 1) {
        this->_registry.at(i)->stop();
    }
}

void SendingRegistry::slotSendingDataChanged(SendingData * data) {
    this->_sendings_data->insert(data->name, data);
    emit signalSendingsDataChanged(this->_sendings_data);
    emit signalSendingDataChanged(data);
}

Modes * SendingRegistry::getModes() {
    return this->_modes;
}

void SendingRegistry::setModes(Modes * modes) {
    this->_modes = modes;
    emit signalModesChanged(this->_modes);
}

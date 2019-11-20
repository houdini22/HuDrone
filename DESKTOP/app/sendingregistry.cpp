#include "include.h"

SendingRegistry::SendingRegistry(Drone * drone) {
    this->_drone = drone;
    this->_modes = new Modes;

    connect(this, SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData>)), this->_drone, SLOT(slotSendingsDataChanged(QHash<QString, SendingData>)));
}

SendingRegistry::~SendingRegistry() {
    delete this->_modes;
    this->_sendings_data.clear();
    this->_registry.clear();
}

void SendingRegistry::add(SendingInterface * handler) {
    this->_registry.append(handler);
    this->_sendings_data.insert(handler->getData().name, handler->getData());
}

void SendingRegistry::start() {
    emit signalSendingsDataChanged(this->_sendings_data);
    this->startThreads();
}

void SendingRegistry::stop() {
    this->stopThreads();
}

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

void SendingRegistry::slotSendingDataChanged(SendingData data) {
    qDebug() << "SendingRegistry::slotSendingDataChanged:" << data.name;
    this->_sendings_data.remove(data.name);
    this->_sendings_data.insert(data.name, data);
    emit signalSendingsDataChanged(this->_sendings_data);
}

Modes * SendingRegistry::getModes() {
    return this->_modes;
}

QHash<QString, SendingData> SendingRegistry::getData() {
    return this->_sendings_data;
}

void SendingRegistry::setModes(Modes * modes) {
    this->_modes = modes;
    emit signalModesChanged(this->_modes);
}

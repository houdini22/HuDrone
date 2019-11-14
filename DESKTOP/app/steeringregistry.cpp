#include "include.h"

SteeringRegistry::SteeringRegistry(Drone *drone) {
    this->_drone = drone;
    this->_steerings_data = new QHash<QString, SteeringData *>;
}

SteeringRegistry::~SteeringRegistry() {
    this->_steerings_data->clear();
    delete this->_steerings_data;
}

void SteeringRegistry::add(SteeringInterface * handler) {
    this->_registry.append(handler);
    connect(handler,
            SIGNAL(signalSteeringDataChanged(SteeringData *)),
            this,
            SLOT(slotSteeringDataChanged(SteeringData *)));
    this->_steerings_data->insert(handler->getData()->name, handler->getData());
    emit signalSteeringsDataChanged(this->_steerings_data);
}

void SteeringRegistry::slotSteeringDataChanged(SteeringData * data) {
    this->_steerings_data->insert(data->name, data);
    emit signalSteeringsDataChanged(this->_steerings_data);
    emit signalSteeringDataChanged(data);
}

void SteeringRegistry::start() {}

void SteeringRegistry::startThreads() {
    for (int i = 0; i < this->_registry.size(); i += 1) {
        this->_registry.at(i)->start();
    }
}

void SteeringRegistry::stopThreads() {
    for (int i = 0; i < this->_registry.size(); i += 1) {
        this->_registry.at(i)->stop();
    }
}

QHash<QString, SteeringData *> * SteeringRegistry::getData() {
    return this->_steerings_data;
}

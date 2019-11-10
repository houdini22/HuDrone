#include "include.h"

SteeringRegistry::SteeringRegistry(Drone *drone) {
    this->drone = drone;
    this->steeringsData = new QHash<QString, SteeringData *>;
}

SteeringRegistry::~SteeringRegistry() {
    this->steeringsData->clear();
    delete this->steeringsData;
}

void SteeringRegistry::add(SteeringInterface * handler) {
    this->registry.append(handler);
}

void SteeringRegistry::slotSteeringDataChanged(SteeringData * data) {
    this->steeringsData->insert(data->name, data);
    emit signalSteeringsDataChanged(this->steeringsData);
    emit signalSteeringDataChanged(data);
}

void SteeringRegistry::start() {
    for (int i = 0; i < this->registry.size(); i += 1) {
        SteeringInterface * _interface = this->registry.at(i);
        SteeringData * data = _interface->getData();
        this->steeringsData->insert(data->name, data);
        emit signalSteeringDataChanged(data);
    }

    emit signalSteeringsDataChanged(this->steeringsData);
}

void SteeringRegistry::startThreads() {
    for (int i = 0; i < this->registry.size(); i += 1) {
        this->registry.at(i)->start();
    }
}

void SteeringRegistry::stopThreads() {
    for (int i = 0; i < this->registry.size(); i += 1) {
        this->registry.at(i)->stop();
    }
}
QHash<QString, SteeringData *> * SteeringRegistry::getData() {
    return this->steeringsData;
}

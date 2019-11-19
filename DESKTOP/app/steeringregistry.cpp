#include "include.h"

SteeringRegistry::SteeringRegistry(Drone * drone) {
    this->_drone = drone;

    connect(this, SIGNAL(signalSteeringsDataChanged(QHash<QString, SteeringData>)), this->_drone, SLOT(slotSteeringsDataChanged(QHash<QString, SteeringData>)));
}

SteeringRegistry::~SteeringRegistry() {
    this->_steerings_data.clear();
}

void SteeringRegistry::add(SteeringInterface * handler) {
    this->_registry.append(handler);
    connect(handler,
            SIGNAL(signalSteeringDataChanged(SteeringData)),
            this,
            SLOT(slotSteeringDataChanged(SteeringData)));
    this->_steerings_data.insert(handler->getData().name, handler->getData());
}

void SteeringRegistry::slotSteeringDataChanged(SteeringData data) {
    this->_steerings_data.remove(data.name);
    this->_steerings_data.insert(data.name, data);
    emit signalSteeringsDataChanged(this->_steerings_data);
}

void SteeringRegistry::start() {
    emit signalSteeringsDataChanged(this->_steerings_data);
    this->startThreads();
}

void SteeringRegistry::stop() {
    this->stopThreads();
}

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

QHash<QString, SteeringData> SteeringRegistry::getData() {
    return this->_steerings_data;
}

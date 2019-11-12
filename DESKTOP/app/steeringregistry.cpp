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

    connect(handler,
            SIGNAL(signalSteeringDataChanged(SteeringData *)),
            this,
            SLOT(slotSteeringDataChanged(SteeringData *)));

    this->steeringsData->insert(handler->getData()->name, handler->getData());
}

void SteeringRegistry::slotSteeringDataChanged(SteeringData * data) {
    this->steeringsData->insert(data->name, data);
    emit signalSteeringsDataChanged(this->steeringsData);
    emit signalSteeringDataChanged(data);
}

void SteeringRegistry::start() {

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

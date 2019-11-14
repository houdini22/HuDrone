#include "include.h"

SendingInterface::SendingInterface(Drone * drone, SendingRegistry * registry, SteeringRegistry * steeringRegistry) {
    this->_drone = drone;
    this->_sending_registry = registry;
    this->_steering_registry = steeringRegistry;
}

void SendingInterface::start() {}

void SendingInterface::stop() {}

SendingData * SendingInterface::getData() {
    return this->_data;
}

#include "include.h"

SendingInterface::SendingInterface(Drone * drone, SendingRegistry * registry) {
    this->drone = drone;
    this->registry = registry;
}

void SendingInterface::start() {}

SendingData * SendingInterface::getData() {
    return this->data;
}

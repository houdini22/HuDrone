#include "include.h"

//
SteeringInterface::SteeringInterface(Drone * drone, SteeringRegistry * registry) {
    this->drone = drone;
    this->registry = registry;
}

void SteeringInterface::start() {}

void SteeringInterface::stop() {}

SteeringData * SteeringInterface::getData() {
    return this->data;
}

bool SteeringInterface::hasDataChanged(SteeringData * data) {
    if (data->isConnected != this->data->isConnected) {
        return true;
    } else if (data->isEnabled != this->data->isEnabled) {
        return true;
    }

    return false;
}

void SteeringInterface::setData(SteeringData * data) {
    if (this->hasDataChanged(data)) {
        this->data = data;
        emit signalSteeringDataChanged(this->data);
    }
}

//
SteeringGamepad0::SteeringGamepad0(Drone * drone, SteeringRegistry * registry) : SteeringInterface(drone, registry) {
    this->data = new SteeringData;
    this->data->name = "gamepad0";
    this->data->isEnabled = true;

    this->_gamepads = QGamepadManager::instance();
    connect(this->_gamepads, SIGNAL(connectedGamepadsChanged()), this, SLOT(slotConnectedGamepadsChanged()));

    this->slotConnectedGamepadsChanged();
}

void SteeringGamepad0::slotConnectedGamepadsChanged() {
    this->data->isConnected = this->_gamepads->isGamepadConnected(0);
    if (this->_gamepads->isGamepadConnected(0)) {
        this->_gamepad = new QGamepad(0, this);

        connect(this->_gamepad, &QGamepad::axisLeftXChanged, this, [this](double value) {
            this->data->buttonsPressed.leftX = value;
            emit signalSteeringDataChanged(this->data);
        });
    } else {
        if (this->_gamepad != nullptr) {
            disconnect(this->_gamepad);
            delete this->_gamepad;
            this->_gamepad = nullptr;
        }
    }
    emit signalSteeringDataChanged(this->data);
}

void SteeringGamepad0::start() {

}

#include "include.h"

//
SteeringInterface::SteeringInterface(Drone * drone, SteeringRegistry * registry) {
    this->drone = drone;
    this->registry = registry;
}

void SteeringInterface::start() {}

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

    this->threadConnect = new ThreadGamepad0();
    this->threadGamepadUpdate = new ThreadGamepad0Update(this->registry, this->drone);

    connect(this, SIGNAL(signalSteeringDataChanged(SteeringData*)), this->registry, SLOT(slotSteeringDataChanged(SteeringData*)));
    connect(this->threadConnect, SIGNAL(signalGamepadIsConnected(bool)), this, SLOT(slotGamepadIsConnected(bool)));
    connect(this->threadGamepadUpdate, SIGNAL(signalButtonsChanged(ButtonsPressed)), this, SLOT(slotButtonsChanged(ButtonsPressed)));
}

void SteeringGamepad0::start() {
    this->threadConnect->start();
    this->threadGamepadUpdate->start();
}

void SteeringGamepad0::slotGamepadIsConnected(bool value) {
    if (this->data->isConnected != value) {
        this->data->isConnected = value;
        emit signalSteeringDataChanged(this->data);
    }
}

void SteeringGamepad0::slotButtonsChanged(ButtonsPressed buttons) {
    this->data->buttonsPressed = buttons;
    emit signalSteeringDataChanged(this->data);
}

//
SteeringGamepad1::SteeringGamepad1(Drone * drone, SteeringRegistry * registry) : SteeringInterface(drone, registry) {
    this->data = new SteeringData;
    this->data->name = "gamepad1";

    this->threadConnect = new ThreadGamepad1();
    this->threadGamepadUpdate = new ThreadGamepad1Update(this->registry, this->drone);

    connect(this, SIGNAL(signalSteeringDataChanged(SteeringData*)), this->registry, SLOT(slotSteeringDataChanged(SteeringData*)));
    connect(this->threadConnect, SIGNAL(signalGamepadIsConnected(bool)), this, SLOT(slotGamepadIsConnected(bool)));
    connect(this->threadGamepadUpdate, SIGNAL(signalButtonsChanged(ButtonsPressed)), this, SLOT(slotButtonsChanged(ButtonsPressed)));
}

void SteeringGamepad1::start() {
    this->threadConnect->start();
    this->threadGamepadUpdate->start();
}

void SteeringGamepad1::slotGamepadIsConnected(bool value) {
    if (this->data->isConnected != value) {
        this->data->isConnected = value;
        emit signalSteeringDataChanged(this->data);
    }
}

void SteeringGamepad1::slotButtonsChanged(ButtonsPressed buttons) {
    this->data->buttonsPressed = buttons;
    emit signalSteeringDataChanged(this->data);
}

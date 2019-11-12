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

        connect(this->_gamepad, SIGNAL(gamepadAxisEvent(int deviceId, QGamepadManager::GamepadAxis axis, double value)), this, SLOT(slotGamepadAxisEvent(int deviceId, QGamepadManager::GamepadAxis axis, double value)));
        connect(this->_gamepad, SIGNAL(gamepadButtonPressEvent(int deviceId, QGamepadManager::GamepadButton button, double value)), this, SLOT(slotGamepadButtonPressEvent(int deviceId, QGamepadManager::GamepadButton button, double value)));
        connect(this->_gamepad, SIGNAL(gamepadButtonReleaseEvent(int deviceId, QGamepadManager::GamepadButton button)), this, SLOT(slotGamepadButtonReleaseEvent(int deviceId, QGamepadManager::GamepadButton button)));
    } else {
        disconnect(this->_gamepad, SIGNAL(gamepadAxisEvent(int deviceId, QGamepadManager::GamepadAxis axis, double value)), this, SLOT(slotGamepadAxisEvent(int deviceId, QGamepadManager::GamepadAxis axis, double value)));
        disconnect(this->_gamepad, SIGNAL(gamepadButtonPressEvent(int deviceId, QGamepadManager::GamepadButton button, double value)), this, SLOT(slotGamepadButtonPressEvent(int deviceId, QGamepadManager::GamepadButton button, double value)));
        disconnect(this->_gamepad, SIGNAL(gamepadButtonReleaseEvent(int deviceId, QGamepadManager::GamepadButton button)), this, SLOT(slotGamepadButtonReleaseEvent(int deviceId, QGamepadManager::GamepadButton button)));

        delete this->_gamepad;
    }
    emit signalSteeringDataChanged(this->data);
}

void SteeringGamepad0::slotGamepadAxisEvent(int deviceId, QGamepadManager::GamepadAxis axis, double value) {
    qDebug() << deviceId;
    if (deviceId == 0) {
        switch (axis) {
            case QGamepadManager::GamepadAxis::AxisLeftX:
                this->data->buttonsPressed.leftX = value;
                break;

            case QGamepadManager::GamepadAxis::AxisLeftY:
                this->data->buttonsPressed.leftY = value;
                break;

            case QGamepadManager::GamepadAxis::AxisRightX:
                this->data->buttonsPressed.rightX = value;
                break;

            case QGamepadManager::GamepadAxis::AxisRightY:
                this->data->buttonsPressed.rightY = value;
                break;

            default:
                break;
        }

        emit signalSteeringDataChanged(this->data);
        qDebug() << value;
    }
}

void SteeringGamepad0::slotGamepadButtonPressEvent(int deviceId, QGamepadManager::GamepadButton button, double value) {

}

void SteeringGamepad0::slotGamepadButtonReleaseEvent(int deviceId, QGamepadManager::GamepadButton button) {

}

void SteeringGamepad0::start() {

}

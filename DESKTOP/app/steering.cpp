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
        connect(this->_gamepad, &QGamepad::axisLeftYChanged, this, [this](double value) {
            this->data->buttonsPressed.leftY = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::axisRightXChanged, this, [this](double value) {
            this->data->buttonsPressed.rightX = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::axisRightYChanged, this, [this](double value) {
            this->data->buttonsPressed.rightY = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonAChanged, this, [this](bool value) {
            this->data->buttonsPressed.a = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonBChanged, this, [this](bool value) {
            this->data->buttonsPressed.b = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonXChanged, this, [this](bool value) {
            this->data->buttonsPressed.x = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonYChanged, this, [this](bool value) {
            this->data->buttonsPressed.y = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonL1Changed, this, [this](bool value) {
            this->data->buttonsPressed.l1 = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonR1Changed, this, [this](bool value) {
            this->data->buttonsPressed.r1 = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonL2Changed, this, [this](bool value) {
            this->data->buttonsPressed.l2 = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonR2Changed, this, [this](bool value) {
            this->data->buttonsPressed.r2 = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonL3Changed, this, [this](bool value) {
            this->data->buttonsPressed.l3 = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonR3Changed, this, [this](bool value) {
            this->data->buttonsPressed.r3 = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonSelectChanged, this, [this](bool value) {
            this->data->buttonsPressed.select = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonStartChanged, this, [this](bool value) {
            this->data->buttonsPressed.start = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonUpChanged, this, [this](bool value) {
            this->data->buttonsPressed.up = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonDownChanged, this, [this](bool value) {
            this->data->buttonsPressed.down = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonLeftChanged, this, [this](bool value) {
            this->data->buttonsPressed.left = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonRightChanged, this, [this](bool value) {
            this->data->buttonsPressed.right = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonCenterChanged, this, [this](bool value) {
            this->data->buttonsPressed.center = value;
            emit signalSteeringDataChanged(this->data);
        });
        connect(this->_gamepad, &QGamepad::buttonGuideChanged, this, [this](bool value) {
            this->data->buttonsPressed.guide = value;
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

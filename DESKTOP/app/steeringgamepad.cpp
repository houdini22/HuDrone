#include "include.h"

SteeringGamepad::SteeringGamepad(Drone * drone, SteeringRegistry * steeringRegistry, int deviceId) : SteeringInterface(drone, steeringRegistry) {
    this->_gamepads = QGamepadManager::instance();
    this->_data.name = "gamepad0";
    this->_data.type = "gamepad";
    this->_data.isEnabled = true;
    this->_device_id = deviceId;

    connect(steeringRegistry,
            SIGNAL(signalSteeringsDataChanged(QVector<SteeringData>)),
            this->_drone,
            SLOT(slotSteeringsDataChanged(QVector<SteeringData>)));

    this->start();
}

QString SteeringGamepad::getType() {
    return "gamepad";
}

int SteeringGamepad::getDeviceId() {
    return this->_device_id;
}

void SteeringGamepad::start() {
    this->_gamepad = new QGamepad(this->_device_id, this);
    this->_data.isConnected = true;
    qDebug() << "Gamepad device id: " << this->_device_id;

    connect(this->_gamepad, &QGamepad::axisLeftXChanged, this, [this](double value) {
        this->_data.buttons.leftX = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::axisLeftYChanged, this, [this](double value) {
        this->_data.buttons.leftY = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::axisRightXChanged, this, [this](double value) {
        this->_data.buttons.rightX = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::axisRightYChanged, this, [this](double value) {
        this->_data.buttons.rightY = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonAChanged, this, [this](bool value) {
        this->_data.buttons.a = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonBChanged, this, [this](bool value) {
        this->_data.buttons.b = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonXChanged, this, [this](bool value) {
        this->_data.buttons.x = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonYChanged, this, [this](bool value) {
        this->_data.buttons.y = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonL1Changed, this, [this](bool value) {
        this->_data.buttons.l1 = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonR1Changed, this, [this](bool value) {
        this->_data.buttons.r1 = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonL2Changed, this, [this](bool value) {
        this->_data.buttons.l2 = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonR2Changed, this, [this](bool value) {
        this->_data.buttons.r2 = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonL3Changed, this, [this](bool value) {
        this->_data.buttons.l3 = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonR3Changed, this, [this](bool value) {
        this->_data.buttons.r3 = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonSelectChanged, this, [this](bool value) {
        this->_data.buttons.select = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonStartChanged, this, [this](bool value) {
        this->_data.buttons.start = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonUpChanged, this, [this](bool value) {
        this->_data.buttons.up = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonDownChanged, this, [this](bool value) {
        this->_data.buttons.down = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonLeftChanged, this, [this](bool value) {
        this->_data.buttons.left = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonRightChanged, this, [this](bool value) {
        this->_data.buttons.right = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonCenterChanged, this, [this](bool value) {
        this->_data.buttons.center = value;
        emit signalSteeringDataChanged(this->_data);
    });
    connect(this->_gamepad, &QGamepad::buttonGuideChanged, this, [this](bool value) {
        this->_data.buttons.guide = value;
        emit signalSteeringDataChanged(this->_data);
    });

    emit signalSteeringDataChanged(this->_data);
}

void SteeringGamepad::stop() {
    if (this->_gamepad != nullptr) {
        disconnect(this->_gamepad);
        delete this->_gamepad;
        this->_gamepad = nullptr;
    }
}

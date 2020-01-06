#pragma once
#include "include.h"

struct SteeringGamepadButtons;
class Drone;
class SteeringRegistry;

//
struct SteeringData {
    QString name = "";
    QString type = "";
    bool isConnected = false;
    bool isEnabled = false;
    SteeringGamepadButtons buttons;
};

//
class SteeringInterface : public QObject {
    Q_OBJECT
public:
    SteeringInterface(Drone * drone, SteeringRegistry * registry) {
        this->_drone = drone;
        this->_registry = registry;
        this->_data.name = generate_random_string(16);
    }
    virtual void start() {}
    virtual void stop() {}
    virtual QString getType() { return ""; }
    SteeringData getData() {
        return this->_data;
    }
protected:
    SteeringRegistry * _registry;
    Drone * _drone;
    SteeringData _data;
signals:
    void signalSteeringDataChanged(SteeringData);
};

class SteeringGamepad : public SteeringInterface {
    Q_OBJECT
public:
    explicit SteeringGamepad(Drone *, SteeringRegistry *, int);
    void start() override;
    void stop() override;
    QString getType() override;
    int getDeviceId();
private:
    QGamepadManager * _gamepads = nullptr;
    QGamepad * _gamepad = nullptr;
    int _device_id = -1;
};

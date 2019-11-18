#pragma once
#include "include.h"

class ThreadGamepad0;
class ThreadGamepad0Update;
class ThreadGamepad1;
class ThreadGamepad1Update;
struct SteeringGamepadButtons;
class Drone;
class SteeringRegistry;

//
struct SteeringData {
    QString name = "";
    bool isConnected = false;
    bool isEnabled = false;
    SteeringGamepadButtons buttons;
};

//
class SteeringInterface : public QObject {
    Q_OBJECT
public:
    SteeringInterface(Drone *, SteeringRegistry *);
    virtual void start() {}
    virtual void stop() {}
    SteeringData * getData();
protected:
    SteeringRegistry * _registry;
    Drone * _drone;
    SteeringData * _data;
signals:
    void signalSteeringDataChanged(SteeringData *);
};

//
class SteeringGamepad0 : public SteeringInterface {
    Q_OBJECT
public:
    SteeringGamepad0(Drone * _drone, SteeringRegistry * _registry);
    void start() override;
private:
    QGamepadManager * _gamepads = nullptr;
    QGamepad * _gamepad = nullptr;
public slots:
    void slotConnectedGamepadsChanged();
};

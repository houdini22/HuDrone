#ifndef STEERINGGAMEPAD_H
#define STEERINGGAMEPAD_H

#include "include.h"

class ThreadGamepad0;
class ThreadGamepad0Update;
class ThreadGamepad1;
class ThreadGamepad1Update;
struct ButtonsPressed;
class Drone;
class SteeringRegistry;

//
struct SteeringData {
    QString name = "";
    bool isConnected = false;
    bool isEnabled = false;
    ButtonsPressed buttonsPressed;
};

//
class SteeringInterface : public QObject {
    Q_OBJECT
public:
    SteeringInterface(Drone * drone, SteeringRegistry * registry);
    virtual void start();
    virtual void stop();
    SteeringData * getData();
protected:
    SteeringRegistry * registry;
    Drone * drone;
    SteeringData * data;
signals:
    void signalSteeringDataChanged(SteeringData *);
};

//
class SteeringGamepad0 : public SteeringInterface {
    Q_OBJECT
public:
    SteeringGamepad0(Drone * drone, SteeringRegistry * registry);
    void start() override;
private:
    QGamepadManager * _gamepads = nullptr;
    QGamepad * _gamepad = nullptr;
public slots:
    void slotConnectedGamepadsChanged();
};

#endif // STEERINGGAMEPAD_H

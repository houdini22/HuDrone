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
    SteeringData * getData();
    void setData(SteeringData * data);
protected:
    SteeringRegistry * registry;
    Drone * drone;
    SteeringData * data;
    bool hasDataChanged(SteeringData * data);
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
    ThreadGamepad0 * threadConnect;
    ThreadGamepad0Update * threadGamepadUpdate;
public slots:
    void slotGamepadIsConnected(bool);
    void slotButtonsChanged(ButtonsPressed);
};

//
class SteeringGamepad1 : public SteeringInterface {
    Q_OBJECT
public:
    SteeringGamepad1(Drone * drone, SteeringRegistry * registry);
    void start() override;
private:
    ThreadGamepad1 * threadConnect;
    ThreadGamepad1Update * threadGamepadUpdate;
public slots:
    void slotGamepadIsConnected(bool);
    void slotButtonsChanged(ButtonsPressed);
signals:
    void signalSteeringDataChanged(SteeringData *);
};

#endif // STEERINGGAMEPAD_H

#ifndef THREADGAMEPADUPDATE_H
#define THREADGAMEPADUPDATE_H

#include "include.h"

class Drone;

class ThreadGamepadUpdate : public QThread
{
    Q_OBJECT
public:
    explicit ThreadGamepadUpdate(SteeringRegistry * registry, Drone * drone);
    void run();
private:
    QString name;
    Drone * drone;
    SteeringRegistry * registry;
    SteeringData * steeringData;
    //GAMEPAD_DEVICE gamepad = GAMEPAD_0;
public slots:
    void slotSteeringDataChanged(SteeringData *);
signals:
    void signalButtonsChanged(SteeringGamepadButtons buttons);
};

class ThreadGamepad0Update : public ThreadGamepadUpdate {
public:
    ThreadGamepad0Update(SteeringRegistry * registry, Drone * drone);
protected:
    int gamepad = 0;
};

class ThreadGamepad1Update : public ThreadGamepadUpdate {
public:
    ThreadGamepad1Update(SteeringRegistry * registry, Drone * drone);
protected:
    int gamepad = 1;
};

#endif // THREADGAMEPADUPDATE_H

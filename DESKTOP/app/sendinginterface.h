#pragma once
#include "include.h"

class Drone;
class SendingRegistry;
class SteeringRegistry;
class MySerialPort;

struct SendingData {
    QString name = "";
    int mode = MODE_ARDUINO_DISCONNECTED;
    QTcpSocket * service = nullptr;
};

class SendingInterface {
public:
    SendingInterface(Drone *, SendingRegistry *, SteeringRegistry *);
    virtual void start();
    virtual void stop();
    SendingData getData();
protected:
    SendingRegistry * _sending_registry;
    SteeringRegistry * _steering_registry;
    Drone * _drone;
    SendingData _data;
};

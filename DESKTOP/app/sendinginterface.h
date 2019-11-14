#ifndef SENDINGINTERFACE_H
#define SENDINGINTERFACE_H

#include "include.h"

class Drone;
class SendingRegistry;
class SteeringRegistry;

struct SendingData {
    QString name = "";
    int mode = MODE_ARDUINO_DISCONNECTED;
    QSerialPort * service = NULL;
};

class SendingInterface : public QObject {
    Q_OBJECT
public:
    SendingInterface(Drone *, SendingRegistry *, SteeringRegistry *);
    virtual void start();
    virtual void stop();
    SendingData * getData();
protected:
    SendingRegistry * _sending_registry;
    SteeringRegistry * _steering_registry;
    Drone * _drone;
    SendingData * _data;
};

#endif // SENDINGINTERFACE_H

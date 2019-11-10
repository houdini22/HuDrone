#ifndef SENDINGINTERFACE_H
#define SENDINGINTERFACE_H

#include "include.h"

class Drone;
class SendingRegistry;

struct SendingData {
    QString name = "";
    int mode = MODE_ARDUINO_DISCONNECTED;
    QString deviceString = "";
    QSerialPort * service = NULL;
};

class SendingInterface {
public:
    SendingInterface(Drone * drone, SendingRegistry * registry);
    virtual void start();
    virtual void stop();
    SendingData * getData();
protected:
    SendingRegistry * registry;
    Drone * drone;
    SendingData * _data;
};

#endif // SENDINGINTERFACE_H

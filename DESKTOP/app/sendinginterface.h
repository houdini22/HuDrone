#ifndef SENDINGINTERFACE_H
#define SENDINGINTERFACE_H

#include "include.h"

class Drone;
class SendingRegistry;

struct SendingData {
    QString name = "";
    int mode = MODE_ARDUINO_DISCONNECTED;
    QString deviceString = "";
    LibSerial::SerialPort * service = NULL;
};

class SendingInterface {
public:
    SendingInterface(Drone * drone, SendingRegistry * registry);
    virtual void start();
    SendingData * getData();
protected:
    SendingRegistry * registry;
    Drone * drone;
    SendingData * data;
};

#endif // SENDINGINTERFACE_H

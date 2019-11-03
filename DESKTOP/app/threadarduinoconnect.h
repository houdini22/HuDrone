#ifndef THREADARDUINOCONNECT_H
#define THREADARDUINOCONNECT_H

#include "include.h"

class Drone;

class ThreadArduinoConnect : public QThread
{
    Q_OBJECT
public:
    explicit ThreadArduinoConnect(SendingRegistry * registry);
    void run();
private:
    SendingData * sendingData;
    SendingRegistry * registry;
public slots:
    void slotSendingDataChanged(SendingData * sendingData);
signals:
    void signalSendingDataChanged(SendingData *);
};

#endif // THREADARDUINOCONNECT_H

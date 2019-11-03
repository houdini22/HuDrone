#ifndef THREADARDUINOPING_H
#define THREADARDUINOPING_H

#include "include.h"

class Drone;

class ThreadArduinoPing : public QThread
{
    Q_OBJECT
public:
    explicit ThreadArduinoPing(SendingRegistry * registry);
    void run();
private:
    SendingData * sendingData;
    SendingRegistry * registry;
public slots:
    void slotSendingDataChanged(SendingData *);
signals:
    void signalSendingDataChanged(SendingData *);
};

#endif // THREADARDUINOPING_H

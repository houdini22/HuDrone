#ifndef THREADARDUINOPING_H
#define THREADARDUINOPING_H

#include "include.h"

class Drone;

class ThreadArduinoPing : public QThread {
    Q_OBJECT
public:
    explicit ThreadArduinoPing(SendingRegistry * _registry);
    ~ThreadArduinoPing();
    void run();
    void start();
private:
    SendingData * _sending_data = nullptr;
    SendingRegistry * _registry = nullptr;
    bool _is_running = false;
public slots:
    void slotSendingDataChanged(SendingData *);
    void terminate();
signals:
    void signalSendingDataChanged(SendingData *);
};

#endif // THREADARDUINOPING_H

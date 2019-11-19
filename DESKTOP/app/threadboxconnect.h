#pragma once
#include "include.h"

class ThreadBoxConnect : public QThread {
    Q_OBJECT
public:
    explicit ThreadBoxConnect();
    explicit ThreadBoxConnect(Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    ~ThreadBoxConnect() override;
    void run() override;
    void start();
private:
    Drone * _drone = nullptr;
    QSerialPort * _arduino = nullptr;
    SendingRegistry * _sending_registry = nullptr;
    SteeringRegistry * _steering_registry = nullptr;
    bool _is_running = false;
    Profile * _profile = nullptr;
    void timeout();
    SendingData * _sending_data = nullptr;
    SteeringData * _steering_data = nullptr;
signals:
    void arduinoConnected(QSerialPort *);
    void signalSendingDataChanged(SendingData *);
public slots:
    void terminate();
    void slotSendingDataChanged(SendingData *);
};

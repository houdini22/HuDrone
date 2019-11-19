#pragma once
#include "include.h"

struct SteeringData;

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
    SendingData _sending_data;
signals:
    void arduinoConnected(QSerialPort *);
    void signalSendingDataChanged(SendingData);
public slots:
    void terminate();
    void slotSendingsDataChanged(QHash<QString, SendingData>);
};

#pragma once
#include "include.h"

class ThreadBoxConnect;
class SendingInterface;

class SendingArduino : public QObject, public SendingInterface {
    Q_OBJECT
public:
    SendingArduino(Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    void start();
    void stop();
private:
    ThreadBoxConnect * _thread_box_connect = nullptr;
    Profile * _profile = nullptr;
public slots:
    void slotSendingDataChanged(SendingData);
    void slotArduinoConnected(QSerialPort *);
signals:
    void signalSendingDataChanged(SendingData);
    void signalArduinoConnected(QSerialPort *);
};

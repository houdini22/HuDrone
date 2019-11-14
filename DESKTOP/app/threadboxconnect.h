#ifndef THREADBOXCONNECT_H
#define THREADBOXCONNECT_H

#include "include.h"

class ThreadBoxConnect : public QThread {
    Q_OBJECT
public:
    explicit ThreadBoxConnect();
    explicit ThreadBoxConnect(Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    ~ThreadBoxConnect();
    void run();
    void start();
protected:
    Drone * _drone = nullptr;
    QSerialPort * _arduino = nullptr;
    SendingRegistry * _sending_registry = nullptr;
    SteeringRegistry * _steering_registry = nullptr;
    bool _is_running = false;
    Profile * _profile = nullptr;
    int axisValueFromDouble(double);
    QString createAxisBuffer(double, double, double, double);
    QString createAxisBuffer(int, int, int, int);
    void send(QString);
    int _leftX;
    int _leftY;
    int _rightX;
    int _rightY;
    void timeout();
    void setRadioSending(bool value);
    void setMotorsArmed(bool value);
    void setThrottleMode(bool value);
    void setRadioValues(int leftX, int leftY, int rightX, int rightY);
    SendingData * _sending_data;
    SteeringData * _steering_data;
signals:
    void arduinoConnected(QSerialPort *);
    void signalSendingDataChanged(SendingData *);
public slots:
    void terminate();
    void slotSendingDataChanged(SendingData * sendingData);
    void slotSteeringDataChanged(SteeringData * steeringData);
};

#endif // THREADBOXCONNECT_H

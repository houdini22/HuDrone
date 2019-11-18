#ifndef THREADBOXCONNECT_H
#define THREADBOXCONNECT_H

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
    int axisValueFromDouble(double);
    QString createAxisBuffer(double, double, double, double);
    QString createAxisBuffer(int, int, int, int);
    void send(const QString &);
    int _leftX = 0;
    int _leftY = 0;
    int _rightX = 0;
    int _rightY = 0;
    void timeout();
    void setRadioSending(bool value);
    void setMotorsArmed(bool value);
    void setThrottleMode(bool value);
    void setRadioValues(int leftX, int leftY, int rightX, int rightY);
    SendingData * _sending_data = nullptr;
    SteeringData * _steering_data = nullptr;
signals:
    void arduinoConnected(QSerialPort *);
    void signalSendingDataChanged(SendingData *);
public slots:
    void terminate();
    void slotSendingDataChanged(SendingData *);
    void slotSteeringsDataChanged(QHash<QString, SteeringData *> *);
};

#endif // THREADBOXCONNECT_H

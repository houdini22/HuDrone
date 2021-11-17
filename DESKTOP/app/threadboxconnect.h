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
    QTcpSocket * _arduino = nullptr;
    SendingRegistry * _sending_registry = nullptr;
    SteeringRegistry * _steering_registry = nullptr;
    bool _is_running = false;
    Profile * _profile = nullptr;
    void timeout();
    QVector<SteeringData> _steerings_data;
    SendingData _sending_data;
    QString createAxisBuffer(double, double, double, double);
    QString createAxisBuffer(int, int, int, int);
    void setRadioSending(bool);
    void setMotorsArmed(int);
    void setThrottleMode(bool);
    void setRadioValues(int, int, int, int);
    void radioSend();
    SteeringGamepadButtons getButtons(QString, int);
    bool hasButtons(QString, int);
    int _leftX = 0;
    int _leftY = 0;
    int _rightX = 0;
    int _rightY = 0;
    int _lock = 0;
    int _stepThrottle = 0;
    unsigned long long _steps = 0;
    unsigned long long _lastReceivedPong = 0;
    bool _sequenceInProgress = false;
    int _sequenceTime = -1;
signals:
    //void arduinoConnected(QSerialPort *);
    void signalSendingDataChanged(SendingData);
public slots:
    void terminate();
    void slotSendingsDataChanged(QHash<QString, SendingData>);
    void slotSteeringsDataChanged(QVector<SteeringData>);
};

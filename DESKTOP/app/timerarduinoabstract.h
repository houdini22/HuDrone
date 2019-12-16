#pragma once
#include "include.h"

class TimersArduino;
class Drone;
class SendingRegistry;
class SteeringRegistry;
class Profile;
class TimerThread;
struct SendingData;
struct SteeringData;

class TimerArduinoAbstract : public QObject {
    Q_OBJECT
public:
    explicit TimerArduinoAbstract(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    ~TimerArduinoAbstract();
    void start();
    void stop();
    virtual int getMiliseconds() = 0;
    QTimer * getTimer();
protected:
    QTimer * _timer = nullptr;
    TimerThread * _thread = nullptr;
    TimersArduino * _timers = nullptr;
    Drone * _drone = nullptr;
    SendingRegistry * _sending_registry = nullptr;
    SteeringRegistry * _steering_registry = nullptr;
    Profile * _profile = nullptr;
    QHash<QString, SendingData> _sendings_data;
    QHash<QString, SteeringData> _steerings_data;
    void send(const QString &, bool, bool);
private:
    void timeout();
public slots:
    virtual void execute() = 0;
    void slotSendingsDataChanged(QHash<QString, SendingData>);
    void slotSteeringsDataChanged(QHash<QString, SteeringData>);
};

class TimerArduinoPing : public TimerArduinoAbstract {
    Q_OBJECT
public:
    explicit TimerArduinoPing(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    int getMiliseconds() override;
public slots:
    void execute() override;
};

class TimerArduinoSend : public TimerArduinoAbstract {
    Q_OBJECT
public:
    explicit TimerArduinoSend(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    int getMiliseconds() override;
public slots:
    void execute() override;
private:
    QString createAxisBuffer(double, double, double, double);
    QString createAxisBuffer(int, int, int, int);
    void setRadioSending(bool);
    void setMotorsArmed(bool);
    void setThrottleMode(bool);
    void setRadioValues(int, int, int, int);
    int _leftX = 0;
    int _leftY = 0;
    int _rightX = 0;
    int _rightY = 0;
    int _lock = 0;
    int _leftYthrottle = 0;
    unsigned long long _miliseconds = 0;
    bool _armingInProgress = false;
    int _armingSequenceTime = -1;
};

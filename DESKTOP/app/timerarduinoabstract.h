#pragma once
#include "include.h"

class TimersArduino;
class Drone;
class SendingRegistry;
class SteeringRegistry;
class Profile;

class TimerArduinoAbstract : public QObject {
    Q_OBJECT
public:
    explicit TimerArduinoAbstract(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    ~TimerArduinoAbstract();
    void start(int);
    void stop();
protected:
    QTimer * _timer = nullptr;
    TimersArduino * _timers = nullptr;
    Drone * _drone = nullptr;
    SendingRegistry * _sending_registry = nullptr;
    SteeringRegistry * _steering_registry = nullptr;
    Profile * _profile = nullptr;
    void send(const QString &, bool);
private:
    void timeout();
public slots:
    virtual void execute() = 0;
};

class TimerArduinoPing : public TimerArduinoAbstract {
    Q_OBJECT
public:
    explicit TimerArduinoPing(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
public slots:
    void execute() override;
};

class TimerArduinoSend : public TimerArduinoAbstract {
    Q_OBJECT
public:
    explicit TimerArduinoSend(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
public slots:
    void execute() override;
};

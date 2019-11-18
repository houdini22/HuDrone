#ifndef TIMERARDUINOABSTRACT_H
#define TIMERARDUINOABSTRACT_H

#include "include.h"

class TimersArduino;
class Drone;
class SendingRegistry;
class SteeringRegistry;
class Profile;

class TimerArduinoAbstract : public QObject {
    Q_OBJECT
public:
    TimerArduinoAbstract(TimersArduino *, Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
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
    void execute() {}
};

#endif // TIMERARDUINOABSTRACT_H

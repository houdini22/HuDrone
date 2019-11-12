#ifndef THREADARDUINOSEND_H
#define THREADARDUINOSEND_H

/*
#include "include.h"

class Drone;

#define MIN_SEND_VALUE_FORCE 1000
#define MAX_SEND_VALUE_FORCE 2000

class ThreadArduinoSend : public QThread
{
    Q_OBJECT
public:
    explicit ThreadArduinoSend(Drone * _drone, SendingRegistry * _registry);
    void run();
    void start();
private:
    Drone * _drone;
    SendingRegistry * _registry;
    SendingData * _sending_data;
    SteeringData * _steering_data;
    bool _is_running = false;

    void send(QString buffer);

    QString createAxisBuffer(double leftX, double leftY, double rightX, double rightY);
    QString createAxisBuffer(int leftX, int leftY, int rightX, int rightY);

    int axisValueFromDouble(double value);

    void setRadioSending(bool value);
    void setMotorsArmed(bool value);
    void setThrottleMode(bool value);
    void setRadioValues(int leftX, int leftY, int rightX, int rightY);

    int leftX;
    int leftY;
    int rightX;
    int rightY;
public slots:
    void slotSendingDataChanged(SendingData * _sending_data);
    void slotSteeringDataChanged(SteeringData * steeringsData);
    void terminate();
};
*/

#endif // THREADARDUINOSEND_H

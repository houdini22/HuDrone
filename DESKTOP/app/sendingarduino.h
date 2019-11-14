#ifndef SENDINGARDUINO_H
#define SENDINGARDUINO_H

#include "include.h"

class ThreadBoxConnect;

class SendingArduino : public SendingInterface {
    Q_OBJECT
public:
    SendingArduino(Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    void start();
    void stop();
private:
    ThreadBoxConnect * _thread_box_connect = nullptr;
    Profile * _profile;
public slots:
    void slotSendingDataChanged(SendingData *);
    void slotArduinoConnected(QSerialPort *);
signals:
    void signalSendingDataChanged(SendingData *);
    void signalArduinoConnected(QSerialPort *);
};

#endif // SENDINGARDUINO_H

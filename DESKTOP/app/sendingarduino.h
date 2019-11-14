#ifndef SENDINGARDUINO_H
#define SENDINGARDUINO_H

#include "include.h"

class ThreadBoxConnect;
//class ThreadArduinoPing;
class ThreadArduinoSend;

class SendingArduino : public QObject, public SendingInterface {
    Q_OBJECT
public:
    SendingArduino(Drone *, SendingRegistry *, SteeringRegistry *, Profile *);
    void start() override;
    void stop() override;
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

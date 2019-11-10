#ifndef SENDINGARDUINO_H
#define SENDINGARDUINO_H

#include "include.h"

class ThreadBoxConnect;
class ThreadArduinoPing;
class ThreadArduinoSend;

class SendingArduino : public QObject, public SendingInterface {
    Q_OBJECT
public:
    SendingArduino(Drone * drone, SendingRegistry * registry);
    void start() override;
    void stop() override;
private:
    ThreadBoxConnect * threadBoxConnect;
    ThreadArduinoPing * threadArduinoPing;
    ThreadArduinoSend * threadArduinoSend;
public slots:
    void slotSendingDataChanged(SendingData*);
    void slotArduinoConnected(QSerialPort *);
signals:
    void signalSendingDataChanged(SendingData *);
    void signalArduinoConnected(QSerialPort *);
};

#endif // SENDINGARDUINO_H

#ifndef SENDINGARDUINO_H
#define SENDINGARDUINO_H

#include "include.h"

class ThreadArduinoConnect;
class ThreadArduinoDetect;
class ThreadArduinoPing;
class ThreadArduinoSend;

class SendingArduino : public QObject, public SendingInterface {
    Q_OBJECT
public:
    SendingArduino(Drone * drone, SendingRegistry * registry);
    void start() override;
private:
    ThreadArduinoConnect * threadArduinoConnect;
    ThreadArduinoDetect * threadArduinoDetect;
    ThreadArduinoPing * threadArduinoPing;
    ThreadArduinoSend * threadArduinoSend;
public slots:
    void slotSendingDataChanged(SendingData*);
signals:
    void signalSendingDataChanged(SendingData *);
};

#endif // SENDINGARDUINO_H

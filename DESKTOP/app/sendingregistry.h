#ifndef SENDINGREGISTRY_H
#define SENDINGREGISTRY_H

#include "include.h"

class Drone;
class SendingInterface;
struct SendingData;

class SendingRegistry : public QObject {
    Q_OBJECT
public:
    SendingRegistry(Drone * drone);
    ~SendingRegistry();
    void add(SendingInterface * handler);
    void start();
    void startThreads();
    void stopThreads();
    Modes * getModes();
    void setModes(Modes * modes);
private:
    QList<SendingInterface *> registry;
    Drone * drone;
    QHash<QString, SendingData *> * sendingsData;
    Modes * modes;
signals:
    void signalSendingDataChanged(SendingData *);
    void signalSendingsDataChanged(QHash<QString, SendingData *> *);
    void signalModesChanged(Modes *);
public slots:
    void slotSendingDataChanged(SendingData*);
};

#endif // STEERINGREGISTRY_H

#ifndef SENDINGREGISTRY_H
#define SENDINGREGISTRY_H

#include "include.h"

class Drone;
class SendingInterface;
class SendingArduino;
struct SendingData;

class SendingRegistry : public QObject {
    Q_OBJECT
public:
    SendingRegistry(Drone * _drone);
    ~SendingRegistry();
    void add(SendingInterface * handler);
    void start();
    void startThreads();
    void stopThreads();
    Modes * getModes();
    void setModes(Modes * _modes);
private:
    QList<SendingInterface *> _registry;
    Drone * _drone;
    QHash<QString, SendingData *> * _sendings_data;
    Modes * _modes;
signals:
    void signalSendingDataChanged(SendingData *);
    void signalSendingsDataChanged(QHash<QString, SendingData *> *);
    void signalModesChanged(Modes *);
public slots:
    void slotSendingDataChanged(SendingData *);
};

#endif // STEERINGREGISTRY_H

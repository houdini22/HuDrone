#pragma once
#include "include.h"

class Drone;
class SendingInterface;
class SendingArduino;
struct SendingData;

class SendingRegistry : public QObject {
    Q_OBJECT
public:
    SendingRegistry(Drone *);
    ~SendingRegistry();
    void add(SendingInterface *);
    void start();
    void stop();
    Modes * getModes();
    void setModes(Modes *);
    QHash<QString, SendingData> getData();
private:
    QList<SendingInterface *> _registry;
    Drone * _drone;
    QHash<QString, SendingData> _sendings_data;
    Modes * _modes;
    void startThreads();
    void stopThreads();
signals:
    void signalSendingDataChanged(SendingData);
    void signalSendingsDataChanged(QHash<QString, SendingData>);
    void signalModesChanged(Modes *);
public slots:
    void slotSendingDataChanged(SendingData);
};

#ifndef STEERINGREGISTRY_H
#define STEERINGREGISTRY_H

#include "include.h"

class Drone;
class SteeringInterface;
struct SteeringData;

class SteeringRegistry : public QObject {
    Q_OBJECT
public:
    SteeringRegistry(Drone * drone);
    void add(SteeringInterface * handler);
    void start();
    void startThreads();
    QHash<QString, SteeringData *> * getData();
private:
    QList<SteeringInterface *> registry;
    Drone * drone;
    QHash<QString, SteeringData *> * steeringsData;
public slots:
    void slotSteeringDataChanged(SteeringData *);
signals:
    void signalSteeringsDataChanged(QHash<QString, SteeringData *> *);
    void signalSteeringDataChanged(SteeringData *);
};

#endif // STEERINGREGISTRY_H

#ifndef STEERINGREGISTRY_H
#define STEERINGREGISTRY_H

#include "include.h"

class Drone;
class SteeringInterface;
struct SteeringData;

class SteeringRegistry : public QObject {
    Q_OBJECT
public:
    SteeringRegistry(Drone * _drone);
    ~SteeringRegistry();
    void add(SteeringInterface * handler);
    void start();
    void startThreads();
    void stopThreads();
    QHash<QString, SteeringData *> * getData();
private:
    QList<SteeringInterface *> _registry;
    Drone * _drone;
    QHash<QString, SteeringData *> * _steerings_data;
public slots:
    void slotSteeringDataChanged(SteeringData *);
signals:
    void signalSteeringsDataChanged(QHash<QString, SteeringData *> *);
    void signalSteeringDataChanged(SteeringData *);
};

#endif // STEERINGREGISTRY_H

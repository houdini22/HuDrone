#pragma once
#include "include.h"

class Drone;
class SteeringInterface;
struct SteeringData;

class SteeringRegistry : public QObject {
    Q_OBJECT
public:
    SteeringRegistry(Drone * _drone);
    ~SteeringRegistry() override;
    void add(SteeringInterface * handler);
    void start();
    void stop();
    QHash<QString, SteeringData *> * getData();
private:
    QList<SteeringInterface *> _registry;
    Drone * _drone;
    QHash<QString, SteeringData *> * _steerings_data;
    void startThreads();
    void stopThreads();
public slots:
    void slotSteeringDataChanged(SteeringData *);
signals:
    void signalSteeringsDataChanged(QHash<QString, SteeringData *> *);
    void signalSteeringDataChanged(SteeringData *);
};

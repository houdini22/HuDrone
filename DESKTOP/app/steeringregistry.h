#pragma once
#include "include.h"

class Drone;
struct SteeringData;
class SteeringInterface;

class SteeringRegistry : public QObject {
    Q_OBJECT
public:
    SteeringRegistry(Drone *);
    ~SteeringRegistry() override;
    void add(SteeringInterface *);
    void start();
    void stop();
    QVector<SteeringData> getData();
private:
    QList<SteeringInterface *> _registry;
    Drone * _drone = nullptr;
    QVector<SteeringData> _steerings_data;
    QGamepadManager * _gamepads = nullptr;
    void startThreads();
    void stopThreads();
public slots:
    void slotSteeringDataChanged(SteeringData);
private slots:
    void slotGamepadConnected(int);
    void slotGamepadDisconnected(int);
signals:
    void signalSteeringsDataChanged(QVector<SteeringData>);
};

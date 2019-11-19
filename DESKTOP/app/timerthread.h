#pragma once
#include "include.h"

class TimerArduinoAbstract;

class TimerThread : public QThread {
public:
    TimerThread();
    void run() override;
    void setTimer(QTimer *);
    void start();
    void terminate();
private:
    QTimer * _timer = nullptr;
};

#ifndef THREADGAMEPAD_H
#define THREADGAMEPAD_H

#include "include.h"

class ThreadGamepad0 : public QThread {
    Q_OBJECT
public:
    ThreadGamepad0();
    void run();
signals:
    void signalGamepadIsConnected(bool value);
};

class ThreadGamepad1 : public QThread {
    Q_OBJECT
public:
    explicit ThreadGamepad1();
    void run();
signals:
    void signalGamepadIsConnected(bool value);
};

#endif // THREADGAMEPAD_H

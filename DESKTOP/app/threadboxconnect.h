#ifndef THREADBOXCONNECT_H
#define THREADBOXCONNECT_H

#include "include.h"

class ThreadBoxConnect : public QThread
{
    Q_OBJECT
public:
    explicit ThreadBoxConnect();
    void run();
signals:
    void arduinoConnected(SerialPort *);
};

#endif // THREADBOXCONNECT_H

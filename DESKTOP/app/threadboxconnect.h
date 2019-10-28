#ifndef THREADBOXCONNECT_H
#define THREADBOXCONNECT_H

#include "include.h"

class ThreadBoxConnect : public QThread
{
    Q_OBJECT
public:
    explicit ThreadBoxConnect();
    void run();
protected:
    SerialPort * _arduino = nullptr;
signals:
    void arduinoConnected(SerialPort *);
public slots:
    void terminate();
};

#endif // THREADBOXCONNECT_H

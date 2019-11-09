#ifndef THREADBOXCONNECT_H
#define THREADBOXCONNECT_H

#include "include.h"

class ThreadBoxConnect : public QThread
{
    Q_OBJECT
public:
    explicit ThreadBoxConnect();
    explicit ThreadBoxConnect(SendingRegistry *);
    void run();
protected:
    QSerialPort * _arduino = nullptr;
    SendingRegistry * _registry = nullptr;
    SendingData * _sending_data = nullptr;
signals:
    void arduinoConnected(QSerialPort *);
    void signalSendingDataChanged(SendingData *);
public slots:
    void terminate();
    void slotSendingDataChanged(SendingData *);
};

#endif // THREADBOXCONNECT_H

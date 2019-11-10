#ifndef THREADBOXCONNECT_H
#define THREADBOXCONNECT_H

#include "include.h"

class ThreadBoxConnect : public QThread {
    Q_OBJECT
public:
    explicit ThreadBoxConnect();
    explicit ThreadBoxConnect(SendingRegistry *);
    ~ThreadBoxConnect();
    void run();
    void start();
protected:
    QSerialPort * _arduino = nullptr;
    SendingRegistry * _registry = nullptr;
    SendingData * _sending_data = nullptr;
    bool _is_running = false;
signals:
    void arduinoConnected(QSerialPort *);
    void signalSendingDataChanged(SendingData *);
public slots:
    void slotSendingDataChanged(SendingData *);
    void terminate();
};

#endif // THREADBOXCONNECT_H

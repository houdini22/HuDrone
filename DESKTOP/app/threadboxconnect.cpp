#include "include.h"

ThreadBoxConnect::ThreadBoxConnect(): QThread() {}

ThreadBoxConnect::ThreadBoxConnect(Drone * drone, SendingRegistry * registry, SteeringRegistry * steeringRegistry, Profile * profile): QThread() {
    this->_drone = drone;
    this->_sending_registry = registry;
    this->_steering_registry = steeringRegistry;
    this->_profile = profile;

    connect(this->_sending_registry,
            SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData>)),
            this,
            SLOT(slotSendingsDataChanged(QHash<QString, SendingData>)));
    connect(this,
            SIGNAL(signalSendingDataChanged(SendingData)),
            this->_sending_registry,
            SLOT(slotSendingDataChanged(SendingData)));
}

ThreadBoxConnect::~ThreadBoxConnect() {
    disconnect(this->_sending_registry,
            SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData>)),
            this,
            SLOT(slotSendingsDataChanged(QHash<QString, SendingData>)));
    disconnect(this,
            SIGNAL(signalSendingDataChanged(SendingData)),
            this->_sending_registry,
            SLOT(slotSendingDataChanged(SendingData)));
}

void ThreadBoxConnect::start() {
    this->_is_running = true;
    QThread::start();
}

void ThreadBoxConnect::terminate() {
    this->_is_running = false;
    QThread::terminate();
}

void ThreadBoxConnect::run() {
    while (this->_is_running) {
        if (this->_sending_data.mode == MODE_ARDUINO_CONNECTED) {
            this->_arduino->write("T");
            QThread::msleep(50);
        } else {
            if (this->_arduino) {
                delete this->_arduino;
            }

            this->_arduino = new QTcpSocket(this);
            this->_arduino->connectToHost("192.168.4.1", 23);
            this->_arduino->waitForReadyRead(3000);
            char * c = new char;
            this->_arduino->read(c, 1);
            char _c = *c;
            if (_c == 'C') {
                this->_arduino->write("M 0003");
                this->_arduino->write("T");
                this->_sending_data.mode = MODE_ARDUINO_CONNECTED;
                this->_sending_data.service = this->_arduino;
                emit signalSendingDataChanged(this->_sending_data);
                QThread::msleep(50);
            }
        }
    }
}

void ThreadBoxConnect::slotSendingsDataChanged(QHash<QString, SendingData> data) {
    if (data.contains("arduino0")) {
        qDebug() << "ThreadBoxConnect::slotSendingsDataChanged";
        this->_sending_data = data["arduino0"];
    }
}

void ThreadBoxConnect::timeout() {
    qDebug() << "ThreadBoxConnect::timeout";
    if (this->_sending_data.name.compare("arduino0") == 0) {
        this->_sending_data.mode = MODE_ARDUINO_DISCONNECTED;
        delete this->_sending_data.service;
        this->_sending_data.service = nullptr;
        this->_arduino = nullptr;
        emit signalSendingDataChanged(this->_sending_data);
    }
}

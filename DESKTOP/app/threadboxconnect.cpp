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
            QThread::msleep(1000);
            continue;
        }

        QList<QSerialPortInfo> ports = SerialPortUtilities::getAvailablePorts();

        for (int i = 0; i < ports.size(); i += 1) {
            if (this->_arduino != nullptr) {
                delete this->_arduino;
            }

            this->_arduino = new MySerialPort(ports.at(i));
            bool isOpened = this->_arduino->open();
            if (isOpened) {
                this->_sending_data.service = this->_arduino;
                this->_sending_data.mode = MODE_ARDUINO_DETECTED;
                emit signalSendingDataChanged(this->_sending_data);

                bool isConnected = this->_arduino->connectDevice();
                if (isConnected) {
                    this->_sending_data.mode = MODE_ARDUINO_CONNECTED;
                    emit signalSendingDataChanged(this->_sending_data);
                    qDebug() << "connected";
                    continue;
                } else {
                    this->timeout();
                }
            } else {
                this->timeout();
            }
        }

        QThread::msleep(2000);
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

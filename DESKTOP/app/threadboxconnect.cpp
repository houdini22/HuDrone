#include "include.h"

#define BUTTON_TIMEOUT 150

ThreadBoxConnect::ThreadBoxConnect(): QThread() {}

ThreadBoxConnect::ThreadBoxConnect(Drone * drone, SendingRegistry * registry, SteeringRegistry * steeringRegistry, Profile * profile): QThread() {
    this->_drone = drone;
    this->_sending_registry = registry;
    this->_steering_registry = steeringRegistry;
    this->_profile = profile;

    connect(this,
            SIGNAL(signalSendingDataChanged(SendingData)),
            this->_sending_registry,
            SLOT(slotSendingDataChanged(SendingData)));
}

ThreadBoxConnect::~ThreadBoxConnect() {
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
            QThread::msleep(4000);
            continue;
        }

        QList<QSerialPortInfo> ports = SerialPortUtilities::getAvailablePorts();

        for (int i = 0; i < ports.size(); i += 1) {
            if (this->_arduino != nullptr) {
                this->_arduino->close();
                delete this->_arduino;
            }

            this->_arduino = new QSerialPort();
            this->_arduino->open(QIODevice::ReadWrite);
            this->_arduino->setPort(ports.at(i));
            this->_arduino->setBaudRate(QSerialPort::Baud115200);
            this->_arduino->setDataBits(QSerialPort::Data8);
            this->_arduino->setParity(QSerialPort::NoParity);
            this->_arduino->setStopBits(QSerialPort::OneStop);
            this->_arduino->setFlowControl(QSerialPort::NoFlowControl);

            while (!this->_arduino->isOpen()) {
                this->_arduino->open(QIODevice::ReadWrite);
                if (this->_arduino->isOpen()) {
                    break;
                }
                QThread::msleep(50);
            }

            this->_sending_data.service = this->_arduino;
            this->_sending_data.mode = MODE_ARDUINO_DETECTED;
            emit signalSendingDataChanged(this->_sending_data);
            qDebug() << "Emited.";
            qDebug() << "Opened.";
            qDebug() << "Writing hello message...";

            this->_arduino->write("h", 1);
            if (this->_arduino->waitForBytesWritten(1000)) {
                qDebug() << "Sent.";

                if (this->_arduino->waitForReadyRead(1000)) {
                    qDebug() << "Received.";

                    char d;
                    this->_arduino->read(&d, 1);
                    if (d == 'h') {
                        qDebug() << "Connected.";

                        this->_sending_data.service = this->_arduino;
                        this->_sending_data.mode = MODE_ARDUINO_CONNECTED;
                        emit signalSendingDataChanged(this->_sending_data);
                        qDebug() << "emited";
                        continue;
                    }
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

void ThreadBoxConnect::slotSendingDataChanged(SendingData data) {
    if (data.name.compare("arduino0") == 0) {
        this->_sending_data = data;
    }
}

void ThreadBoxConnect::timeout() {
    if (this->_sending_data.name.compare("arduino0") == 0) {
        this->_sending_data.mode = MODE_ARDUINO_DISCONNECTED;
        this->_sending_data.service->close();
        emit signalSendingDataChanged(this->_sending_data);
    }
}

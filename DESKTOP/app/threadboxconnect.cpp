#include "include.h"

ThreadBoxConnect::ThreadBoxConnect(): QThread() {}

ThreadBoxConnect::ThreadBoxConnect(SendingRegistry * registry): QThread() {
    this->_registry = registry;
    connect(this->_registry, SIGNAL(signalSendingDataChanged(SendingData*)), this, SLOT(slotSendingDataChanged(SendingData *)));
}

void ThreadBoxConnect::terminate() {
    QThread::terminate();
}

void ThreadBoxConnect::run() {
    QString data;

    while (1) {
        if (this->_registry != nullptr) {
            if (this->_sending_data->mode == MODE_ARDUINO_CONNECTED) {
                QThread::msleep(1000);
                continue;
            }
        }
        QList<QSerialPortInfo> ports = SerialPortUtilities::getAvailablePorts();

        for (int i = 0; i < ports.size(); i += 1) {
            qDebug() << ports.at(i).portName();

            this->_arduino = new QSerialPort();
            this->_arduino->open(QIODevice::ReadWrite);
            this->_arduino->setPort(ports.at(i));
            this->_arduino->setBaudRate(QSerialPort::Baud115200);
            this->_arduino->setDataBits(QSerialPort::Data8);
            this->_arduino->setParity(QSerialPort::NoParity);
            this->_arduino->setStopBits(QSerialPort::OneStop);
            this->_arduino->setFlowControl(QSerialPort::NoFlowControl);

            int steps = 10;

            while (!this->_arduino->isOpen()) {
                this->_arduino->open(QIODevice::ReadWrite);

                if (this->_arduino->isOpen()) {
                    qDebug() << "Opened, writable.";
                    this->_arduino->write("h");

                    while(1) {
                        //QString data = QString(this->_arduino->read(1));
                        qDebug() << this->_arduino->read(1);
                        if (data.contains("h")) {
                            if (this->_registry != nullptr) {
                                this->_sending_data->service = this->_arduino;
                                this->_sending_data->mode = MODE_ARDUINO_CONNECTED;
                                emit signalSendingDataChanged(this->_sending_data);
                            }
                            emit arduinoConnected(this->_arduino);
                            return;
                        }
                        QThread::msleep(50);
                    }
                } else {
                    qDebug() << "Connect failed.";
                    delete this->_arduino;
                    this->_arduino = nullptr;
                }

                steps -= 1;
                if (steps == 0) {
                    break;
                }
                QThread::msleep(50);
            }
        }

        QThread::msleep(2000);
    }
}

void ThreadBoxConnect::slotSendingDataChanged(SendingData * sendingData) {
    if (sendingData->name.compare("arduino0") == 0) {
        this->_sending_data = sendingData;
    }
}

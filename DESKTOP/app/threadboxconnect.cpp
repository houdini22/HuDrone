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
            this->_arduino->setPort(ports.at(i));
            this->_arduino->setBaudRate(QSerialPort::Baud115200);
            this->_arduino->setDataBits(QSerialPort::Data8);
            this->_arduino->setParity(QSerialPort::NoParity);
            this->_arduino->setStopBits(QSerialPort::OneStop);
            this->_arduino->setFlowControl(QSerialPort::NoFlowControl);

            this->_arduino->open(QIODevice::ReadWrite);

            for (int i = 0; i < 5; i += 1) {
                if (!this->_arduino->isOpen()) {
                    this->_arduino->open(QIODevice::ReadWrite);
                    QThread::msleep(200);
                } else {
                    break;
                }
            }

            if (this->_arduino->isOpen() && this->_arduino->isWritable()) {
                QString data = this->_arduino->readAll();
                if (data.contains("Hello.")) {
                    this->_sending_data->service = this->_arduino;
                    this->_sending_data->mode = MODE_ARDUINO_CONNECTED;
                    emit arduinoConnected(this->_arduino);
                    emit signalSendingDataChanged(this->_sending_data);
                }
            } else {
                this->_arduino->clear();
                this->_arduino->close();
                delete this->_arduino;
                this->_arduino = nullptr;
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

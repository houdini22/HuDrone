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

            while (!this->_arduino->isOpen()) {
                this->_arduino->open(QIODevice::ReadWrite);
                if (this->_arduino->isOpen()) {
                    break;
                }
                QThread::msleep(50);
            }

            if (this->_registry != nullptr) {
                this->_sending_data->service = this->_arduino;
                this->_sending_data->mode = MODE_ARDUINO_DETECTED;
                emit signalSendingDataChanged(this->_sending_data);
            }

            qDebug() << "Opened.";

            while (this->_arduino->bytesAvailable() == 0) {
                qDebug() << "Writing hello message...";
                this->_arduino->write("h", 1);
                while (this->_arduino->waitForBytesWritten(4000)) {}
                qDebug() << "Sent.";

                QThread::msleep(200);
            }

            qDebug() << "Received.";

            char d;
            this->_arduino->read(&d, 1);
            if (d == 'h') {
                qDebug() << "Connected.";
                if (this->_registry != nullptr) {
                    this->_sending_data->service = this->_arduino;
                    this->_sending_data->mode = MODE_ARDUINO_CONNECTED;
                    emit signalSendingDataChanged(this->_sending_data);
                }
                emit arduinoConnected(this->_arduino);
                return;
            }

            qDebug() << "Connect failed.";
            this->_arduino->close();
            delete this->_arduino;
            this->_arduino = nullptr;
        }

        QThread::msleep(2000);
    }
}

void ThreadBoxConnect::slotSendingDataChanged(SendingData * sendingData) {
    if (sendingData->name.compare("arduino0") == 0) {
        this->_sending_data = sendingData;
    }
}

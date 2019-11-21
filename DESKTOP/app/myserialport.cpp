#include "include.h"

MySerialPort::MySerialPort(QSerialPortInfo portInfo) : QObject() {
    this->_device = new QSerialPort(this);
    this->_device->open(QIODevice::ReadWrite);
    this->_device->setPort(portInfo);
    this->_device->setBaudRate(QSerialPort::Baud115200);
    this->_device->setDataBits(QSerialPort::Data8);
    this->_device->setParity(QSerialPort::NoParity);
    this->_device->setStopBits(QSerialPort::OneStop);
    this->_device->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->_device, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(this->_device, SIGNAL(bytesWritten(qint64)), this, SLOT(slotBytesWritten(qint64)));
}

bool MySerialPort::open() {
    if (this->_device->isOpen()) {
        return true;
    }
    int attempts = 10;
    while (!this->_device->isOpen()) {
        this->_device->open(QIODevice::ReadWrite);
        if (this->_device->isOpen()) {
            return true;
        }
        attempts--;
        if (attempts == 0) {
            break;
        }
    }
    return false;
}

bool MySerialPort::isConnected() {
    return this->_is_connected;
}

int MySerialPort::write(QString buffer) {
    if (this->isConnected()) {
        int written = (int) this->_device->write(buffer.toStdString().c_str(), buffer.length());
        if (written != buffer.length()) {
            qDebug() << "Error written:" << written << ", buffer:" << buffer.length();
        } else {
            qDebug() << "Written: " << written;
        }
        return written;
    }

    return -1;
}

bool MySerialPort::connectDevice() {
    this->_device->write("h", 1);
    if (this->_device->waitForBytesWritten(1000)) {
        if (this->_device->waitForReadyRead(1000)) {
            char d;
            this->_device->read(&d, 1);
            if (d == 'h') {
                qDebug() << "Connected.";
                this->_is_connected = true;
                return true;
            }
        }
    }
    return false;
}

void MySerialPort::slotReadyRead() {
    qDebug() << "ready read";
}

void MySerialPort::slotBytesWritten(qint64 bytes) {
    qDebug() << "bytes written" << bytes;
}

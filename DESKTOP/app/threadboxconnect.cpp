#include "include.h"

ThreadBoxConnect::ThreadBoxConnect(): QThread() {}

void ThreadBoxConnect::terminate() {
    QThread::terminate();
    if (this->_arduino != nullptr) {
        this->_arduino->closeSerial();
        delete this->_arduino;
    }
}

void ThreadBoxConnect::run() {
    while (1) {
        QList<QSerialPortInfo> ports = SerialPortUtilities::getAvailablePorts();

        for (int i = 0; i < ports.size(); i += 1) {
            const char * portName = ports.at(i).portName().toStdString().c_str();
            this->_arduino = new SerialPort((char *) portName);

            qDebug() << "PORT: " << portName;

            int errors = 0;

            while (!this->_arduino->isConnected()) {
                QThread::msleep(2000);
                qDebug() << "Waiting..." << errors << "..." << portName;
                errors += 1;

                if (errors == 5) {
                    delete this->_arduino;
                    this->_arduino = nullptr;
                    break;
                }
            }

            if (this->_arduino == nullptr) {
                continue;
            }

            if (this->_arduino->isConnected()) {
                char incomingData[255];
                this->_arduino->readSerialPort(incomingData, 6);
                QString data(incomingData);

                qDebug() << data;

                if (data.contains("Hello.")) {
                    qDebug() << "Connected.";
                    emit arduinoConnected(this->_arduino);
                    return;
                }
            }
        }

        qDebug() << "Sleeping...";
        QThread::msleep(2000);
    }
}


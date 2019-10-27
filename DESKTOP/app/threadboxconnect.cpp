#include "include.h"

ThreadBoxConnect::ThreadBoxConnect(): QThread() {

}

void ThreadBoxConnect::run() {
    while (1) {
        QList<QSerialPortInfo> ports = SerialPortUtilities::getAvailablePorts();

        for (int i = 0; i < ports.size(); i += 1) {
            const char * portName = ports.at(i).portName().toStdString().c_str();
            SerialPort * arduino = new SerialPort((char *) portName);

            qDebug() << "PORT: " << portName;

            int errors = 0;

            while (!arduino->isConnected()) {
                QThread::msleep(2000);
                qDebug() << "Waiting..." << errors << "..." << portName;
                errors += 1;

                if (errors == 5) {
                    delete arduino;
                    arduino = nullptr;
                    break;
                }
            }

            if (arduino == nullptr) {
                continue;
            }

            if (arduino->isConnected()) {
                char incomingData[255];
                arduino->readSerialPort(incomingData, 6);
                QString data(incomingData);

                qDebug() << data;

                if (data.contains("Hello.")) {
                    qDebug() << "Connected.";
                    emit arduinoConnected(arduino);
                    return;
                }
            }
        }

        qDebug() << "Sleeping...";
        QThread::msleep(2000);
    }
}

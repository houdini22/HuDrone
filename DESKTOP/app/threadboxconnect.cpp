#include "include.h"

ThreadBoxConnect::ThreadBoxConnect(): QThread() {

}

void ThreadBoxConnect::run() {
    while (1) {
        QList<QSerialPortInfo> ports = SerialPortUtilities::getAvailablePorts();
        SerialPort * arduino;

        for (int i = 0; i < ports.size(); i += 1) {
            const char * portName = ports.at(i).portName().toStdString().c_str();
            arduino = new SerialPort((char *) portName);
            int errors = 0;
            while (!arduino->isConnected()) {
                QThread::msleep(100);
                qDebug() << "Waiting...";
                errors += 1;

                if (errors == 10) {
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
                arduino->readSerialPort(incomingData, 255);
                if (strcmp(incomingData, "Hello.") == 0) {
                    emit arduinoConnected(arduino);
                    break;
                }
            }
        }

        QThread::msleep(1000);
    }
}

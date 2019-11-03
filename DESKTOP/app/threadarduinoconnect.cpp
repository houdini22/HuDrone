#include "QThread"
#include "include.h"

ThreadArduinoConnect::ThreadArduinoConnect(SendingRegistry * registry): QThread() {
    this->registry = registry;
    connect(this->registry, SIGNAL(signalSendingDataChanged(SendingData *)), this, SLOT(slotSendingDataChanged(SendingData *)));
}

void ThreadArduinoConnect::run() {
    while (1) {
        if (this->sendingData->mode == MODE_ARDUINO_DETECTED) {
            SerialPort * arduino = new SerialPort(this->sendingData->deviceString.toStdString());

            try {
                qDebug("Opening...");
                arduino->Open(SerialPort::BAUD_115200, SerialPort::CHAR_SIZE_8,
                              SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                              SerialPort::FLOW_CONTROL_NONE);
                arduino->SetDtr(true);
            } catch (SerialPort::OpenFailed ex) {
                qDebug("Open Failed.");
                QThread::msleep(1000);
                continue;
            }

            while (!arduino->IsOpen()) {}
            qDebug("Opened.");

            QThread::msleep(2000);

            while (true) {
                SerialPort::DataBuffer buffer;

                try {
                    qDebug("Pinging...");
                    arduino->Write("h");
                    arduino->Read(buffer, 0, 0);
                } catch (SerialPort::ReadTimeout ex) {
                    qDebug("Timeout.");
                    QThread::msleep(500);
                    continue;
                } catch (SerialPort::NotOpen ex) {
                    qDebug("Not opened.");
                    QThread::msleep(500);
                    break;
                }

                bool connected = false;
                for (unsigned long i = 0; i < buffer.size(); i += 1) {
                    if (buffer[i] == 'h') {
                        connected = true;
                        break;
                    }
                }

                if (connected) {
                    qDebug("OK. Connected.");
                    this->sendingData->service = arduino;
                    this->sendingData->mode = MODE_ARDUINO_CONNECTED;
                    emit signalSendingDataChanged(this->sendingData);
                    break;
                } else {
                    try {
                        qDebug("Fail. Closing.");
                        arduino->Close();
                    } catch(SerialPort::NotOpen ex) {}
                    break;
                }

                QThread::msleep(1000);
            }
        }

        QThread::msleep(1000);
    }
}

void ThreadArduinoConnect::slotSendingDataChanged(SendingData * sendingData) {
    if (sendingData->name.compare("arduino0") == 0) {
        this->sendingData = sendingData;
    }
}

#include "QThread"
#include "include.h"

ThreadArduinoPing::ThreadArduinoPing(SendingRegistry * registry): QThread()
{
    this->registry = registry;
    connect(this->registry, SIGNAL(signalSendingDataChanged(SendingData *)), this, SLOT(slotSendingDataChanged(SendingData *)));
}

void ThreadArduinoPing::run() {
    while (1) {
        /*
         * if (this->sendingData->mode == MODE_ARDUINO_CONNECTED) {
            QSerialPort * arduino = this->sendingData->service;
            arduino->write("p", 1);

            if (false) {
                this->sendingData->mode = MODE_ARDUINO_DISCONNECTED;
                this->sendingData->deviceString = "";
                this->sendingData->service->close();
                delete this->sendingData->service;
                this->sendingData->service = nullptr;

                emit signalSendingDataChanged(this->sendingData);
            }
        }
         */

        QThread::msleep(100);
    }
}

void ThreadArduinoPing::slotSendingDataChanged(SendingData * sendingData) {
    if (sendingData->name.compare("arduino0") == 0) {
        this->sendingData = sendingData;
    }
}

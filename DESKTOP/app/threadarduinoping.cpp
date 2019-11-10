#include "QThread"
#include "include.h"

ThreadArduinoPing::ThreadArduinoPing(SendingRegistry * registry): QThread() {
    this->_registry = registry;

    connect(this->_registry,
            SIGNAL(signalSendingDataChanged(SendingData *)),
            this,
            SLOT(slotSendingDataChanged(SendingData *)));
}

void ThreadArduinoPing::start() {
    this->_is_running = true;
    QThread::start();
}

void ThreadArduinoPing::terminate() {
    this->_is_running = false;
    QThread::terminate();
}

ThreadArduinoPing::~ThreadArduinoPing() {
    disconnect(this->_registry,
               SIGNAL(signalSendingDataChanged(SendingData *)),
               this,
               SLOT(slotSendingDataChanged(SendingData *)));
}

void ThreadArduinoPing::run() {
    while (this->_is_running) {
        if (this->_sending_data->mode == MODE_ARDUINO_CONNECTED) {
            QSerialPort * arduino = this->_sending_data->service;
            arduino->write("p", 1);

            if (false) {
                this->_sending_data->mode = MODE_ARDUINO_DISCONNECTED;
                this->_sending_data->deviceString = "";
                this->_sending_data->service->close();
                delete this->_sending_data->service;
                this->_sending_data->service = nullptr;

                emit signalSendingDataChanged(this->_sending_data);
            }
        }

        QThread::msleep(100);
    }
}

void ThreadArduinoPing::slotSendingDataChanged(SendingData * sendingData) {
    if (sendingData->name.compare("arduino0") == 0) {
        this->_sending_data = sendingData;
    }
}

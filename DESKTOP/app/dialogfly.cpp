#include "include.h"
#include "ui_dialogfly.h"

DialogFly::DialogFly(QWidget *parent, Drone * drone) : QDialog(parent), ui(new Ui::DialogFly) {
    this->_drone = drone;

    ui->setupUi(this);

    connect(this->_drone,
            SIGNAL(signalSendingsDataChanged(QHash<QString,SendingData*>*)),
            this,
            SLOT(slotSendingsDataChanged(QHash<QString,SendingData*>*)));

    this->_drone->startThreads();
}

void DialogFly::slotSendingsDataChanged(QHash<QString,SendingData*>* data) {
    SendingData * data2 = data->take("arduino0");

    QLabel * label = this->_layout->findChild<QLabel * >(QString("labelDeviceHudroneBox"));

    if (data2->mode == MODE_ARDUINO_DETECTED) {
        label->setDisabled(true);
        label->setText("connecting...");
    } else if (data2->mode == MODE_ARDUINO_CONNECTED) {
        label->setDisabled(false);
        label->setText("connected");
    } else if (data2->mode == MODE_ARDUINO_DISCONNECTED) {
        label->setDisabled(true);
        label->setText("connect...");
    }
}

void DialogFly::closeEvent(QCloseEvent *) {
    this->_drone->stopThreads();
}

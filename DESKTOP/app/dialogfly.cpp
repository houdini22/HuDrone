#include "include.h"
#include "ui_dialogfly.h"

DialogFly::DialogFly(QWidget *parent, Drone * drone) : QDialog(parent), ui(new Ui::DialogFly) {
    this->_drone = drone;

    ui->setupUi(this);
}

void DialogFly::showEvent(QShowEvent *) {
    connect(this->_drone,
            SIGNAL(signalSendingsDataChanged(QHash<QString,SendingData*>*)),
            this,
            SLOT(slotSendingsDataChanged(QHash<QString,SendingData*>*)));
    connect(this->_drone,
            SIGNAL(signalSteeringDataChanged(QHash<QString,SteeringData*>*)),
            this,
            SLOT(slotSteeringDataChanged(QHash<QString,SteeringData*>*)));

    this->_drone->start();
}

void DialogFly::slotSendingsDataChanged(QHash<QString,SendingData*>* data) {
    SendingData * data2 = data->take("arduino0");

    QLabel * label = this->ui->labelDeviceHudroneBox;

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

void DialogFly::slotSteeringDataChanged(QHash<QString,SteeringData*>* data) {
    SteeringData * data2 = data->take("gamepad0");

    QLabel * label = this->ui->labelDeviceGamepad0;

    if (data2->isConnected) {
        label->setDisabled(false);
        label->setText("connected");
    } else {
        label->setDisabled(true);
        label->setText("connect...");
    }
}

void DialogFly::closeEvent(QCloseEvent *) {
    disconnect(this->_drone,
               SIGNAL(signalSendingsDataChanged(QHash<QString,SendingData*>*)),
               this,
               SLOT(slotSendingsDataChanged(QHash<QString,SendingData*>*)));

    this->_drone->stop();
}

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
            SIGNAL(signalSteeringsDataChanged(QHash<QString,SteeringData*>*)),
            this,
            SLOT(slotSteeringsDataChanged(QHash<QString,SteeringData*>*)));

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

void DialogFly::slotSteeringsDataChanged(QHash<QString,SteeringData*>* data) {
    SteeringData * gamepad0 = data->take("gamepad0");
    SteeringData * gamepad1 = data->take("gamepad1");

    qDebug() << gamepad0->isConnected;

    QLabel * label = this->ui->labelDeviceGamepad0;
    if (gamepad0->isConnected) {
        label->setDisabled(false);
        label->setText("connected");
    } else {
        label->setDisabled(true);
        label->setText("connect...");
    }

    /*
    QLabel * label2 = this->ui->labelDeviceGamepad1;
    if (gamepad1->isConnected) {
        label2->setDisabled(false);
        label2->setText("connected");
    } else {
        label2->setDisabled(true);
        label2->setText("connect...");
    }
    */
}

void DialogFly::closeEvent(QCloseEvent *) {
    disconnect(this->_drone,
               SIGNAL(signalSendingsDataChanged(QHash<QString,SendingData*>*)),
               this,
               SLOT(slotSendingsDataChanged(QHash<QString,SendingData*>*)));
    disconnect(this->_drone,
            SIGNAL(signalSteeringsDataChanged(QHash<QString,SteeringData*>*)),
            this,
            SLOT(slotSteeringsDataChanged(QHash<QString,SteeringData*>*)));

    this->_drone->stop();
}

#include "include.h"
#include "ui_dialogfly.h"

DialogFly::DialogFly(QWidget *parent, Drone * drone, QString profileName) : QDialog(parent), ui(new Ui::DialogFly) {
    this->_drone = drone;
    this->_profile = Profile::byName(profileName);

    ui->setupUi(this);
}

void DialogFly::showEvent(QShowEvent *) {
    connect(this->_drone,
            SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData *> *)),
            this,
            SLOT(slotSendingsDataChanged(QHash<QString, SendingData *> *)));
    connect(this->_drone,
            SIGNAL(signalSteeringsDataChanged(QHash<QString, SteeringData *> *)),
            this,
            SLOT(slotSteeringsDataChanged(QHash<QString, SteeringData *> *)));
    connect(this->_drone,
            SIGNAL(signalModesChanged(Modes *)),
            this,
            SLOT(slotModesChanged(Modes *)));

    this->_drone->start(this->_profile);
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

void DialogFly::slotSteeringsDataChanged(QHash<QString, SteeringData *> * data) {
    if (data->contains("gamepad0")) {
        SteeringData * gamepad0 = data->take("gamepad0");

        QLabel * label = this->ui->labelDeviceGamepad0;
        if (gamepad0->isConnected) {
            label->setDisabled(false);
            label->setText("connected");
        } else {
            label->setDisabled(true);
            label->setText("connect...");
        }
    }

    /*
    SteeringData * gamepad1 = data->take("gamepad1");
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

void DialogFly::slotModesChanged(Modes * modes) {
    this->_modes = modes;

    this->ui->labelLeftX->setText(QString::number(this->_modes->leftX));
    this->ui->labelLeftY->setText(QString::number(this->_modes->leftY));
    this->ui->labelRightX->setText(QString::number(this->_modes->rightX));
    this->ui->labelRightY->setText(QString::number(this->_modes->rightY));

    if (this->_modes->radioSending) {
        this->ui->labelRadioSending->setText("yes");
    } else {
        this->ui->labelRadioSending->setText("no");
    }

    if (this->_modes->motorsArmed) {
        this->ui->labelMotorsArmed->setText("yes");
    } else {
        this->ui->labelMotorsArmed->setText("no");
    }

    if (this->_modes->throttleModeActive) {
        this->ui->labelThrottleModeActive->setText("yes");
    } else {
        this->ui->labelThrottleModeActive->setText("no");
    }

    this->ui->labelThrottleLevel->setText(QString::number(this->_modes->thrust * 100.0) + "%");
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
    disconnect(this->_drone,
            SIGNAL(signalModesChanged(Modes *)),
            this,
            SLOT(slotModesChanged(Modes *)));

    this->_drone->stop();

    delete this->_profile;
}

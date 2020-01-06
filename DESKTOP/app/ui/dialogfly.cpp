#include "include.h"
#include "ui_dialogfly.h"

DialogFly::DialogFly(QWidget *parent, Drone * drone, QString profileName) : QDialog(parent), ui(new Ui::DialogFly) {
    this->_drone = drone;
    this->_profile = Profile::byName(profileName);

    ui->setupUi(this);
}

void DialogFly::showEvent(QShowEvent *) {
    connect(this->_drone,
            SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData>)),
            this,
            SLOT(slotSendingsDataChanged(QHash<QString, SendingData>)));
    connect(this->_drone,
            SIGNAL(signalSteeringsDataChanged(QVector<SteeringData>)),
            this,
            SLOT(slotSteeringsDataChanged(QVector<SteeringData>)));
    connect(this->_drone,
            SIGNAL(signalModesChanged(Modes *)),
            this,
            SLOT(slotModesChanged(Modes *)));

    this->_drone->start(this->_profile);
}

void DialogFly::slotSendingsDataChanged(QHash<QString, SendingData> data) {
    if (data.contains("arduino0")) {
        SendingData data2 = data["arduino0"];

        QLabel * label = this->ui->labelDeviceHudroneBox;

        if (data2.mode == MODE_ARDUINO_DETECTED) {
            label->setDisabled(true);
            label->setText("connecting...");
        } else if (data2.mode == MODE_ARDUINO_CONNECTED) {
            label->setDisabled(false);
            label->setText("connected");
        } else if (data2.mode == MODE_ARDUINO_DISCONNECTED) {
            label->setDisabled(true);
            label->setText("connect...");
        }
    }
}

void DialogFly::slotSteeringsDataChanged(QVector<SteeringData> data) {
    int counter = 0;
    bool found = false;
    QLabel * label = this->ui->labelDeviceGamepad0;

    for (int i = 0; i < data.size(); i += 1) {
        if (data.at(i).type.compare("gamepad") == 0 && counter == 0) {
            SteeringData gamepad0 = data.at(i);

            if (gamepad0.isConnected) {
                label->setDisabled(false);
                label->setText("connected");
                found = true;
            }

            break;
        }

        counter++;
    }

    if (!found) {
        label->setDisabled(true);
        label->setText("connect...");
    }
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

    switch (this->_modes->motorsArmed) {
        case MOTORS_ARMED:
            this->ui->labelMotorsArmed->setText("armed");
            break;

        case MOTORS_ARMING_IN_PROGRESS:
            this->ui->labelMotorsArmed->setText("arming...");
            break;

        case MOTORS_DISARMED:
            this->ui->labelMotorsArmed->setText("disarmed");
            break;

        case MOTORS_DISARMING_IN_PROGRESS:
            this->ui->labelMotorsArmed->setText("disarming...");
            break;
    }

    if (this->_modes->throttleModeActive) {
        this->ui->labelThrottleModeActive->setText("yes");
    } else {
        this->ui->labelThrottleModeActive->setText("no");
    }

    this->ui->labelThrottleLevel->setText(QString::number(this->_modes->thrust * 100.0) + "%");
    this->ui->labelButtonsLevel->setText(QString::number(this->_modes->buttons * 100.0) + "%");
}

void DialogFly::closeEvent(QCloseEvent *) {
    disconnect(this->_drone,
               SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData>)),
               this,
               SLOT(slotSendingsDataChanged(QHash<QString, SendingData>)));
    disconnect(this->_drone,
               SIGNAL(signalSteeringsDataChanged(QVector<SteeringData>)),
               this,
               SLOT(slotSteeringsDataChanged(QVector<SteeringData>)));
    disconnect(this->_drone,
               SIGNAL(signalModesChanged(Modes *)),
               this,
               SLOT(slotModesChanged(Modes *)));

    this->_drone->stop();

    delete this->_profile;
}

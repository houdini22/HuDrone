#include "include.h"

#define BUTTON_TIMEOUT 20

ThreadBoxConnect::ThreadBoxConnect(): QThread() {}

ThreadBoxConnect::ThreadBoxConnect(Drone * drone, SendingRegistry * registry, SteeringRegistry * steeringRegistry, Profile * profile): QThread() {
    this->_drone = drone;
    this->_sending_registry = registry;
    this->_steering_registry = steeringRegistry;
    this->_profile = profile;

    connect(this->_sending_registry,
            SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData>)),
            this,
            SLOT(slotSendingsDataChanged(QHash<QString, SendingData>)));
    connect(this,
            SIGNAL(signalSendingDataChanged(SendingData)),
            this->_sending_registry,
            SLOT(slotSendingDataChanged(SendingData)));
    connect(this->_drone,
            SIGNAL(signalSteeringsDataChanged(QVector<SteeringData>)),
            this,
            SLOT(slotSteeringsDataChanged(QVector<SteeringData>)));

    this->_stepThrottle = this->_profile->getMinLeftY();
}

void ThreadBoxConnect::slotSteeringsDataChanged(QVector<SteeringData> data) {
    this->_steerings_data = data;
}

ThreadBoxConnect::~ThreadBoxConnect() {
    disconnect(this->_sending_registry,
               SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData>)),
               this,
               SLOT(slotSendingsDataChanged(QHash<QString, SendingData>)));
    disconnect(this,
               SIGNAL(signalSendingDataChanged(SendingData)),
               this->_sending_registry,
               SLOT(slotSendingDataChanged(SendingData)));
    disconnect(this->_drone,
               SIGNAL(signalSteeringsDataChanged(QVector<SteeringData>)),
               this,
               SLOT(slotSteeringsDataChanged(QVector<SteeringData>)));
}

void ThreadBoxConnect::start() {
    this->_is_running = true;
    QThread::start();
}

void ThreadBoxConnect::terminate() {
    this->_is_running = false;
    QThread::terminate();
}

void ThreadBoxConnect::run() {
    while (this->_is_running) {
        if (this->_sending_data.mode == MODE_ARDUINO_CONNECTED) {
            QThread::msleep(10);

            if (this->_steps % 5 == 0) {
                this->_arduino->write("T");
                /*char *c;
                this->_arduino->waitForReadyRead(150);
                this->_arduino->read(c, 1);
                if (*c == 'T') {
                    this->_lastReceivedPong = this->_steps;
                }*/
            }

            this->_steps++;

            if (this->hasButtons("gamepad", 0)) {
                if (this->_lock > 0) {
                    this->_lock--;
                }

                if (this->_sequenceInProgress) {
                    this->_sequenceTime++;
                }

                Modes * modes = this->_drone->getModes();
                SteeringGamepadButtons buttons = this->getButtons("gamepad", 0);

                if (this->_sequenceInProgress) {
                    QMap<QString, int> values = this->_profile->getArmingSeqenceValueInTime(modes->motorsArmed, this->_sequenceTime * 10);
                    int numberOfEnd = 0;
                    for (auto it = values.begin(); it != values.end(); ++it) {
                        if (it.value() == -1) {
                            numberOfEnd++;
                        }
                    }
                    bool end = numberOfEnd == values.size();

                    if (end) {
                        this->_sequenceInProgress = false;
                        this->_sequenceTime = -1;

                        if (modes->motorsArmed == MOTORS_ARMING_IN_PROGRESS) {
                            this->setMotorsArmed(MOTORS_ARMED);
                            return;
                        } else if (modes->motorsArmed == MOTORS_DISARMING_IN_PROGRESS) {
                            this->setMotorsArmed(MOTORS_DISARMED);
                            return;
                        }

                        this->radioSend();
                    } else {
                        this->setRadioValues(
                                    values["roll"] != -1 ? values["roll"] : this->_profile->getLeftX(buttons.leftX),
                                    values["throttle"] != -1 ? values["throttle"] : this->_profile->getLeftY(buttons.leftY),
                                    values["pitch"] != -1 ? values["pitch"] : this->_profile->getRightX(buttons.rightX, modes->buttons),
                                    values["yaw"] != -1 ? values["yaw"] : this->_profile->getRightY(buttons.rightY, modes->buttons));
                    }
                } else {
                    this->radioSend();
                }

                if (this->_lock > 0) {
                    continue;
                }

                if (buttons.down) {
                    if (!modes->throttleModeActive) {
                        this->setThrottleMode(true);
                    } else {
                        this->setThrottleMode(false);
                    }
                    this->_lock = BUTTON_TIMEOUT;
                    continue;
                }

                if (buttons.l1) {
                    modes->thrust -= (double) (((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY()) / (double) this->_profile->getThrottleSteps()) / ((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY());
                    if (modes->thrust < 0.0001) {
                        modes->thrust = 0.0;
                    }
                    this->_stepThrottle = this->_profile->getMinLeftY() + ((double) (this->_profile->getMaxLeftY() - this->_profile->getMinLeftY()) * modes->thrust);
                    this->_drone->setModes(modes);
                    this->_lock = BUTTON_TIMEOUT;
                    continue;
                }

                if (buttons.r1) {
                    modes->thrust += (double) (((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY()) / (double) this->_profile->getThrottleSteps()) / ((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY());
                    if (modes->thrust > 1.0) {
                        modes->thrust = 1.0;
                    }
                    this->_stepThrottle = this->_profile->getMinLeftY() + ((double) (this->_profile->getMaxLeftY() - this->_profile->getMinLeftY()) * modes->thrust);
                    this->_drone->setModes(modes);
                    this->_lock = BUTTON_TIMEOUT;
                    continue;
                }

                if (buttons.left) {
                    modes->buttons -= 0.05;
                    if (modes->buttons < 0.0001) {
                        modes->buttons = 0.0;
                    }
                    this->_lock = BUTTON_TIMEOUT;
                    this->_drone->setModes(modes);
                    continue;
                }

                if (buttons.right) {
                    modes->buttons += 0.05;
                    if (modes->buttons > 1.0) {
                        modes->buttons = 1.0;
                    }
                    this->_lock = BUTTON_TIMEOUT;
                    this->_drone->setModes(modes);
                    continue;
                }

                if (buttons.start) {
                    if (!modes->radioSending) {
                        this->_arduino->write("n");
                        this->setRadioSending(true);
                    } else {
                        this->_arduino->write("f");
                        this->setRadioSending(false);
                    }
                    this->_lock = BUTTON_TIMEOUT;
                    continue;
                }

                if (modes->radioSending) {
                    if (buttons.l2 && buttons.r2) {
                        if (modes->motorsArmed == MOTORS_DISARMED) {
                            this->setMotorsArmed(MOTORS_ARMING_IN_PROGRESS);
                            this->_lock = BUTTON_TIMEOUT;
                            continue;
                        } else if (modes->motorsArmed == MOTORS_ARMED) {
                            this->setMotorsArmed(MOTORS_DISARMING_IN_PROGRESS);
                            this->_lock = BUTTON_TIMEOUT;
                            continue;
                        }
                    }
                }
            }
        } else {
            if (this->_arduino) {
                delete this->_arduino;
            }

            this->_arduino = new QTcpSocket(this);
            this->_arduino->connectToHost("192.168.4.1", 23);
            char * c = new char;
            this->_arduino->read(c, 1);
            char _c = *c;
            if (_c == 'C') {
                this->_arduino->write("M 0003");
                this->_arduino->write("T");
                this->_sending_data.mode = MODE_ARDUINO_CONNECTED;
                this->_sending_data.service = this->_arduino;
                emit signalSendingDataChanged(this->_sending_data);
                QThread::msleep(50);
            }
        }
    }
}

void ThreadBoxConnect::slotSendingsDataChanged(QHash<QString, SendingData> data) {
    if (data.contains("arduino0")) {
        qDebug() << "ThreadBoxConnect::slotSendingsDataChanged";
        this->_sending_data = data["arduino0"];
    }
}

void ThreadBoxConnect::timeout() {
    qDebug() << "ThreadBoxConnect::timeout";
    if (this->_sending_data.name.compare("arduino0") == 0) {
        this->_sending_data.mode = MODE_ARDUINO_DISCONNECTED;
        delete this->_sending_data.service;
        this->_sending_data.service = nullptr;
        this->_arduino = nullptr;
        emit signalSendingDataChanged(this->_sending_data);
    }
}

SteeringGamepadButtons ThreadBoxConnect::getButtons(QString type, int index) {
    int counter = 0;

    for (int i = 0; i < this->_steerings_data.size(); i += 1) {
        if (this->_steerings_data.at(i).type.compare(type) == 0 && counter == index) {
            return this->_steerings_data.at(i).buttons;
        }

        counter++;
    }

    return SteeringGamepadButtons();
}

bool ThreadBoxConnect::hasButtons(QString type, int index) {
    int counter = 0;

    for (int i = 0; i < this->_steerings_data.size(); i += 1) {
        if (this->_steerings_data.at(i).type.compare(type) == 0 && counter == index) {
            return true;
        }

        counter++;
    }

    return false;
}

void ThreadBoxConnect::radioSend() {
    Modes * modes = this->_drone->getModes();
    SteeringGamepadButtons buttons = this->getButtons("gamepad", 0);

    if (modes->throttleModeActive) {
        this->setRadioValues(
                    this->_profile->getLeftX(buttons.leftX),
                    this->_stepThrottle,
                    this->_profile->getRightX(buttons.rightX, modes->buttons),
                    this->_profile->getRightY(buttons.rightY, modes->buttons));
    } else {
        this->setRadioValues(
                    this->_profile->getLeftX(buttons.leftX),
                    std::max(this->_profile->getLeftY(buttons.leftY), this->_profile->getMinLeftY()),
                    this->_profile->getRightX(buttons.rightX, modes->buttons),
                    this->_profile->getRightY(buttons.rightY, modes->buttons));
    }
}

QString ThreadBoxConnect::createAxisBuffer(double leftX, double leftY, double rightX, double rightY) {
    Modes * modes = this->_drone->getModes();
    return this->createAxisBuffer(
                this->_profile->getLeftX(leftX),
                this->_profile->getLeftY(leftY),
                this->_profile->getRightX(rightX, modes->buttons),
                this->_profile->getRightY(rightY, modes->buttons));
}

QString ThreadBoxConnect::createAxisBuffer(int leftX, int leftY, int rightX, int rightY) {
    QString buffer = "";

    if (leftX != this->_leftX) {
        this->_leftX = leftX;
        buffer.append("^" + this->_profile->getChannelNumberOf("yaw") + "#");
        buffer.append(QString::number(leftX));
        buffer.append("$");
    }

    if (leftY != this->_leftY) {
        this->_leftY = leftY;
        buffer.append("^" + this->_profile->getChannelNumberOf("throttle") + "#");
        buffer.append(QString::number(leftY));
        buffer.append("$");
    }

    if (rightX != this->_rightX) {
        this->_rightX = rightX;
        buffer.append("^" + this->_profile->getChannelNumberOf("roll") + "#");
        buffer.append(QString::number(rightX));
        buffer.append("$");
    }

    if (rightY != this->_rightY) {
        this->_rightY = rightY;
        buffer.append("^" + this->_profile->getChannelNumberOf("pitch") + "#");
        buffer.append(QString::number(rightY));
        buffer.append("$");
    }

    return buffer;
}

void ThreadBoxConnect::setRadioSending(bool value) {
    Modes * modes = this->_drone->getModes();
    if (modes->radioSending != value) {
        modes->radioSending = value;
        this->_drone->setModes(modes);
    }
}

void ThreadBoxConnect::setMotorsArmed(int value) {
    Modes * modes = this->_drone->getModes();
    if (modes->motorsArmed != value) {
        modes->motorsArmed = value;
        this->_drone->setModes(modes);
        if (value == MOTORS_ARMING_IN_PROGRESS || value == MOTORS_DISARMING_IN_PROGRESS) {
            this->_sequenceInProgress = true;
            this->_sequenceTime = -1;
        }
    }
}

void ThreadBoxConnect::setThrottleMode(bool value) {
    Modes * modes = this->_drone->getModes();
    if (modes->throttleModeActive != value) {
        modes->throttleModeActive = value;
        this->_drone->setModes(modes);
    }
}

void ThreadBoxConnect::setRadioValues(int leftX, int leftY, int rightX, int rightY) {
    Modes * modes = this->_drone->getModes();
    modes->leftX = leftX;
    modes->leftY = leftY;
    modes->rightX = rightX;
    modes->rightY = rightY;

    this->_drone->setModes(modes);

    this->_arduino->write(this->createAxisBuffer(leftX, leftY, rightX, rightY).toStdString().c_str());
}

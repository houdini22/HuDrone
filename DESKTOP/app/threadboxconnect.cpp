#include "include.h"

ThreadBoxConnect::ThreadBoxConnect(): QThread() {}

ThreadBoxConnect::ThreadBoxConnect(Drone * drone, SendingRegistry * registry, SteeringRegistry * steeringRegistry, Profile * profile): QThread() {
    this->_drone = drone;
    this->_sending_registry = registry;
    this->_steering_registry = steeringRegistry;
    this->_profile = profile;

    connect(this->_sending_registry,
            SIGNAL(signalSendingDataChanged(SendingData*)),
            this,
            SLOT(slotSendingDataChanged(SendingData *)));

    connect(this->_steering_registry,
            SIGNAL(signalSteeringsDataChanged(QHash<QString, SteeringData *> *)),
            this,
            SLOT(slotSteeringsDataChanged(QHash<QString, SteeringData *> *)));
}

ThreadBoxConnect::~ThreadBoxConnect() {
    disconnect(this->_sending_registry,
            SIGNAL(signalSendingDataChanged(SendingData*)),
            this,
            SLOT(slotSendingDataChanged(SendingData *)));
    disconnect(this->_steering_registry,
            SIGNAL(signalSteeringsDataChanged(QHash<QString, SteeringData *> * steeringsData)),
            this,
            SLOT(slotSteeringsDataChanged(QHash<QString, SteeringData *> * steeringsData)));
}

void ThreadBoxConnect::start() {
    this->_is_running = true;
    QThread::start();
}

void ThreadBoxConnect::terminate() {
    this->_is_running = false;
    QThread::terminate();
}

void ThreadBoxConnect::send(QString buffer) {
    this->_arduino->write(buffer.toStdString().c_str(), buffer.length());
    if (!this->_arduino->waitForBytesWritten(1000)) {
        this->disconnect();
    }
}

QString ThreadBoxConnect::createAxisBuffer(double leftX, double leftY, double rightX, double rightY) {
    return this->createAxisBuffer(
                this->_profile->getLeftX(leftX),
                this->_profile->getLeftY(leftY),
                this->_profile->getRightX(rightX),
                this->_profile->getRightY(rightY));
}

QString ThreadBoxConnect::createAxisBuffer(int leftX, int leftY, int rightX, int rightY) {
    QString buffer = "";

    if (leftX != this->_leftX) {
        this->_leftX = leftX;
        buffer.append("^3#");
        buffer.append(QString::number(leftX));
        buffer.append("$");
    }

    if (leftY != this->_leftY) {
        this->_leftY = leftY;
        buffer.append("^2#");
        buffer.append(QString::number(leftY));
        buffer.append("$");
    }

    if (rightX != this->_rightX) {
        this->_rightX = rightX;
        buffer.append("^0#");
        buffer.append(QString::number(rightX));
        buffer.append("$");
    }

    if (rightY != this->_rightY) {
        this->_rightY = rightY;
        buffer.append("^1#");
        buffer.append(QString::number(rightY));
        buffer.append("$");
    }

    if (buffer.length() == 0) {
        buffer.append("z");
    }

    return buffer;
}

void ThreadBoxConnect::timeout() {
    qDebug() << "Timeout.";
    if (this->_sending_registry != nullptr) {
        this->_sending_data->mode = MODE_ARDUINO_DISCONNECTED;
        this->_arduino->close();
        emit signalSendingDataChanged(this->_sending_data);
    }
}

void ThreadBoxConnect::setRadioSending(bool value) {
    Modes * modes = this->_drone->getModes();
    if (modes->radioSending != value) {
        modes->radioSending = value;
        this->_drone->setModes(modes);
    }
}

void ThreadBoxConnect::setMotorsArmed(bool value) {
    Modes * modes = this->_drone->getModes();
    if (modes->motorsArmed != value) {
        modes->motorsArmed = value;
        this->_drone->setModes(modes);
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
}

void ThreadBoxConnect::run() {
    while (this->_is_running) {
        if (this->_sending_registry != nullptr) {
            if (this->_sending_data->mode == MODE_ARDUINO_CONNECTED) {
                QThread::msleep(4000);
                continue;
            }
        }

        QList<QSerialPortInfo> ports = SerialPortUtilities::getAvailablePorts();

        for (int i = 0; i < ports.size(); i += 1) {
            qDebug() << ports.at(i).portName();

            if (this->_arduino != nullptr) {
                this->_arduino->close();
                delete this->_arduino;
            }

            this->_arduino = new QSerialPort();
            this->_arduino->open(QIODevice::ReadWrite);
            this->_arduino->setPort(ports.at(i));
            this->_arduino->setBaudRate(QSerialPort::Baud115200);
            this->_arduino->setDataBits(QSerialPort::Data8);
            this->_arduino->setParity(QSerialPort::NoParity);
            this->_arduino->setStopBits(QSerialPort::OneStop);
            this->_arduino->setFlowControl(QSerialPort::NoFlowControl);

            while (!this->_arduino->isOpen()) {
                this->_arduino->open(QIODevice::ReadWrite);
                if (this->_arduino->isOpen()) {
                    break;
                }
                QThread::msleep(50);
            }

            if (this->_sending_registry != nullptr) {
                this->_sending_data->service = this->_arduino;
                this->_sending_data->mode = MODE_ARDUINO_DETECTED;
                emit signalSendingDataChanged(this->_sending_data);
            }

            qDebug() << "Opened.";
            qDebug() << "Writing hello message...";

            this->_arduino->write("h", 1);
            if (this->_arduino->waitForBytesWritten(1000)) {
                qDebug() << "Sent.";

                if (this->_arduino->waitForReadyRead(1000)) {
                    qDebug() << "Received.";

                    char d;
                    this->_arduino->read(&d, 1);
                    if (d == 'h') {
                        qDebug() << "Connected.";
                        if (this->_sending_registry != nullptr) {
                            this->_sending_data->service = this->_arduino;
                            this->_sending_data->mode = MODE_ARDUINO_CONNECTED;
                            emit signalSendingDataChanged(this->_sending_data);
                        }
                        emit arduinoConnected(this->_arduino);

                        // send thread begin
                        unsigned long long step = 0;
                        bool startMode = false;
                        int sendingStart = 0;
                        bool armingMode = false;
                        int sendingArm = 0;
                        bool throttleMode = false;
                        int sendingThrottle = 0;
                        int leftY = this->_profile->getMinLeftY();
                        int sendingLeftY = 0;
                        int sendingThrustUp = 0;
                        int sendingThrustDown = 0;

                        while (this->_is_running) {
                            if (step % 5 == 0) {
                                // ping
                                this->_arduino->write("p", 1);
                                if (!this->_arduino->waitForBytesWritten(1000)) {
                                    this->timeout();
                                    break;
                                }
                            }

                            Modes * modes = this->_drone->getModes();
                            ButtonsPressed buttons = this->_steering_data->buttonsPressed;

                            if (sendingArm == 0 && sendingThrottle == 0 && sendingStart == 0 && sendingLeftY == 0 && sendingThrustUp == 0) {
                                if (throttleMode) {
                                    this->setRadioValues(
                                                this->_profile->getLeftX(buttons.leftX),
                                                leftY,
                                                this->_profile->getRightX(buttons.rightX),
                                                this->_profile->getRightY(buttons.rightY));
                                    this->send(this->createAxisBuffer(this->_leftX, this->_leftY, this->_rightX, this->_rightY));
                                } else {
                                    this->setRadioValues(
                                                this->_profile->getLeftX(buttons.leftX),
                                                leftY,
                                                this->_profile->getRightX(buttons.rightX),
                                                this->_profile->getRightY(buttons.rightY));
                                    this->send(this->createAxisBuffer(this->_leftX, this->_leftY, this->_rightX, this->_rightY));
                                }
                            }

                            if (sendingArm == 0 && sendingThrottle == 0 && sendingStart == 0 && sendingLeftY == 0 && sendingThrustUp == 0) { // listening buttons
                                if (buttons.down) { // toggle Throttle mode
                                    sendingThrottle = 4;
                                    continue;
                                }

                                if (buttons.left) {
                                    sendingThrustDown = 4;
                                    continue;
                                }

                                if (buttons.right) {
                                    sendingThrustUp = 4;
                                }

                                if (buttons.start && !armingMode) { // toggle sending
                                    sendingStart = 4;
                                    continue;
                                }

                                if (startMode) { // if toggled sendinf true
                                    if (buttons.l1 && buttons.l2) { // if arming
                                        sendingArm = 40 * 5;
                                        continue;
                                    }
                                }

                                if (throttleMode) { // a on
                                    if (buttons.l2) {
                                        sendingLeftY = 2;

                                        leftY -= 10;
                                        if (leftY < this->_profile->getMinLeftY()) {
                                            leftY = this->_profile->getMinLeftY();
                                        }
                                    } else if (buttons.r2) {
                                        sendingLeftY = 2;

                                        leftY += 10;
                                        if (leftY > this->_profile->getMaxLeftY()) {
                                            leftY = this->_profile->getMaxLeftY();
                                        }
                                    }
                                    continue;
                                }
                            }

                            if (sendingStart > 0) {
                                sendingStart--;
                                if (sendingStart == 0) {
                                    startMode = !startMode;
                                    if (startMode) {
                                        this->send("n"); // on
                                        this->setRadioSending(true);
                                    } else {
                                        this->send("f"); // off
                                        this->setRadioSending(false);
                                    }
                                }

                                continue;
                            }

                            if (sendingArm > 0) {
                                if (!armingMode) {

                                } else {

                                }

                                sendingArm--;
                                if (sendingArm == 0) {
                                    if (!armingMode) {
                                        this->setMotorsArmed(true);
                                    } else {
                                        this->setMotorsArmed(false);
                                    }
                                    armingMode = !armingMode;
                                }

                                continue;
                            }

                            if (sendingThrottle > 0) {
                                sendingThrottle--;

                                if (sendingThrottle == 0) {
                                    throttleMode = !throttleMode;
                                    this->setThrottleMode(throttleMode);
                                }

                                continue;
                            }

                            if (sendingLeftY > 0) {
                                sendingLeftY--;

                                continue;
                            }

                            if (sendingThrustUp > 0) {
                                sendingThrustUp--;

                                if (sendingThrustUp == 0) {
                                    modes->thrust += 0.1;
                                    if (modes->thrust > 1.0) {
                                        modes->thrust = 0.1;
                                    }
                                    this->_drone->setModes(modes);
                                }
                            }

                            if (sendingThrustDown > 0) {
                                sendingThrustDown--;

                                if (sendingThrustDown == 0) {
                                    modes->thrust -= 0.1;
                                    if (modes->thrust == 0.0) {
                                        modes->thrust = 0.1;
                                    }
                                    this->_drone->setModes(modes);
                                }
                            }

                            step++;
                            QThread::msleep(40);
                        }
                    }
                } else {
                    qDebug() << "Connect failed.";
                    if (this->_sending_registry != nullptr) {
                        this->_sending_data->mode = MODE_ARDUINO_DISCONNECTED;
                        this->_arduino->close();
                        emit signalSendingDataChanged(this->_sending_data);
                    }
                }
            } else {
                qDebug() << "Connect failed.";
                if (this->_sending_registry != nullptr) {
                    this->_sending_data->mode = MODE_ARDUINO_DISCONNECTED;
                    this->_arduino->close();
                    emit signalSendingDataChanged(this->_sending_data);
                }
            }
        }

        QThread::msleep(2000);
    }
}

void ThreadBoxConnect::slotSendingDataChanged(SendingData * sendingData) {
    if (sendingData->name.compare("arduino0") == 0) {
        this->_sending_data = sendingData;
    }
}

void ThreadBoxConnect::slotSteeringsDataChanged(QHash<QString, SteeringData *> * steeringsData) {
    this->_steerings_data = steeringsData;
    this->_steering_data = steeringsData->take("gamepad0");
}

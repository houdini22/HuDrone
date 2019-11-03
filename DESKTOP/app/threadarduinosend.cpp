#include "QThread"
#include "include.h"

ThreadArduinoSend::ThreadArduinoSend(Drone * drone, SendingRegistry * registry): QThread()
{
    this->drone = drone;
    this->registry = registry;
    connect(this->registry, SIGNAL(signalSendingDataChanged(SendingData *)), this, SLOT(slotSendingDataChanged(SendingData *)));
    connect(this->drone, SIGNAL(signalSteeringDataChanged(SteeringData *)), this, SLOT(slotSteeringDataChanged(SteeringData *)));
}

void ThreadArduinoSend::send(QString buffer) {
    try {
        this->sendingData->service->Write(buffer.toStdString());
    } catch(std::runtime_error ex) {

    }
}

int ThreadArduinoSend::axisValueFromDouble(double value) {
    return (int) ((((double) MAX_SEND_VALUE_FORCE + (double) MIN_SEND_VALUE_FORCE) / 2.0) +
                           (value * ((double) MAX_SEND_VALUE_FORCE - (double) MIN_SEND_VALUE_FORCE) / 2.0));
}

QString ThreadArduinoSend::createAxisBuffer(double leftX, double leftY, double rightX, double rightY) {
    return this->createAxisBuffer(
                this->axisValueFromDouble(leftX),
                this->axisValueFromDouble(leftY),
                this->axisValueFromDouble(rightX),
                this->axisValueFromDouble(rightY));
}

QString ThreadArduinoSend::createAxisBuffer(int leftX, int leftY, int rightX, int rightY) {
    QString buffer = "";

    if (leftX != this->leftX) {
        this->leftX = leftX;
        buffer.append("^3#");
        buffer.append(QString::number(leftX));
        buffer.append("$");
    }

    if (leftY != this->leftY) {
        this->leftY = leftY;
        buffer.append("^2#");
        buffer.append(QString::number(leftY));
        buffer.append("$");
    }

    if (rightX != this->rightX) {
        this->rightX = rightX;
        buffer.append("^0#");
        buffer.append(QString::number(rightX));
        buffer.append("$");
    }

    if (rightY != this->rightY) {
        this->rightY = rightY;
        buffer.append("^1#");
        buffer.append(QString::number(rightY));
        buffer.append("$");
    }

    if (buffer.length() == 0) {
        buffer.append("z");
    }

    return buffer;
}

void ThreadArduinoSend::run() {
    nlohmann::json data;// = Storage::getInstance().getData();

    bool startMode = false;
    int sendingStart = 0;
    bool armingMode = false;
    int sendingArm = 0;
    bool throttleMode = false;
    int sendingThrottle = 0;
    int leftY = data["radio"]["leftY"]["min"].get<int>();
    int sendingLeftY = 0;
    int sendingThrustUp = 0;
    int sendingThrustDown = 0;

    int timeSleep = 40;

    while (1) {
        QThread::msleep(timeSleep);

        Modes * modes = this->drone->getModes();
        ButtonsPressed buttons = this->steeringData->buttonsPressed;
        nlohmann::json data;// = Storage::getInstance().getData();

        if (this->sendingData->mode == MODE_ARDUINO_CONNECTED) {
            if (modes->mouseSteering) {
                if (modes->radioSending && !startMode) {
                    sendingStart = 26; // 26 * 40 ms
                    this->send("n"); // on
                    continue;
                }

                if (!modes->radioSending && startMode) {
                    sendingStart = 26; // 26 * 40 ms
                    this->send("f"); // off
                    continue;
                }

                if (!sendingStart) {
                    this->setRadioValues(modes->leftX, modes->leftY, modes->rightX, modes->rightY);
                    this->send(this->createAxisBuffer(modes->leftX, modes->leftY, modes->rightX, modes->rightY));
                }

                if (sendingStart > 0) {
                    sendingStart--;
                    if (sendingStart == 0) {
                        startMode = !startMode;
                    }

                    continue;
                }
            } else {
                // send
                if (sendingArm == 0 && sendingThrottle == 0 && sendingStart == 0 && sendingLeftY == 0 && sendingThrustUp == 0) {
                    if (throttleMode) {
                        this->setRadioValues(buttons.leftX, leftY, buttons.rightX, buttons.rightY);
                        this->send(this->createAxisBuffer(buttons.leftX, leftY, buttons.rightX, buttons.rightY));
                    } else {
                        this->setRadioValues(buttons.leftX, buttons.leftY, buttons.rightX, buttons.rightY);
                        this->send(this->createAxisBuffer(buttons.leftX, buttons.leftY, buttons.rightX, buttons.rightY));
                    }
                }

                if (sendingArm == 0 && sendingThrottle == 0 && sendingStart == 0 && sendingLeftY == 0 && sendingThrustUp == 0) { // listening buttons
                    if (buttons.dPadDown) { // toggle Throttle mode
                        sendingThrottle = 4;
                        continue;
                    }

                    if (buttons.dPadLeft) {
                        sendingThrustDown = 4;
                        continue;
                    }

                    if (buttons.dPadRight) {
                        sendingThrustUp = 4;
                    }

                    if (buttons.start && !armingMode) { // toggle sending
                        sendingStart = 4;
                        continue;
                    }

                    if (startMode) { // if toggled sendinf true
                        if (buttons.arming) { // if arming
                            sendingArm = (double) data["arming"]["time"].get<int>() / (double) timeSleep + 1.0;
                            continue;
                        }
                    }

                    if (throttleMode) { // a on
                        if (buttons.leftShoulder) {
                            sendingLeftY = 2;

                            leftY -= data["throttleMode"]["step"].get<int>();
                            if (leftY < data["radio"]["leftY"]["min"].get<int>()) {
                                leftY = data["radio"]["leftY"]["min"].get<int>();
                            }
                        } else if (buttons.rightShoulder) {
                            sendingLeftY = 2;

                            leftY += data["throttleMode"]["step"].get<int>();
                            if (leftY > data["radio"]["leftY"]["max"].get<int>()) {
                                leftY = data["radio"]["leftY"]["max"].get<int>();
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
                        this->setRadioValues(data["arming"]["leftX"].get<int>(), data["arming"]["leftY"].get<int>(), data["arming"]["rightX"].get<int>(), data["arming"]["rightY"].get<int>());
                        this->send(this->createAxisBuffer(data["arming"]["leftX"].get<int>(), data["arming"]["leftY"].get<int>(), data["arming"]["rightX"].get<int>(), data["arming"]["rightY"].get<int>()));
                    } else {
                        this->setRadioValues(data["disarming"]["leftX"].get<int>(), data["disarming"]["leftY"].get<int>(), data["disarming"]["rightX"].get<int>(), data["disarming"]["rightY"].get<int>());
                        this->send(this->createAxisBuffer(data["disarming"]["leftX"].get<int>(), data["disarming"]["leftY"].get<int>(), data["disarming"]["rightX"].get<int>(), data["disarming"]["rightY"].get<int>()));
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
                        this->drone->setModes(modes);
                    }
                }

                if (sendingThrustDown > 0) {
                    sendingThrustDown--;

                    if (sendingThrustDown == 0) {
                        modes->thrust -= 0.1;
                        if (modes->thrust == 0.0) {
                            modes->thrust = 0.1;
                        }
                        this->drone->setModes(modes);
                    }
                }
            }
        }
        /*
        else if (this->drone->isArduinoDetected() && this->drone->isArduinoConnected()) {
            if (sendingArm == 0 && sendingStart == 0) {
                if (handPosition.fist && !startMode) { // toggle sending
                    if (startMode) {
                        sendingStart = 26; // 26 * 40 ms

                        this->send("f"); // off
                        this->setRadioSending(false);
                    } else {
                        sendingStart = 26; // 26 * 40 ms

                        this->send("n"); // on
                        this->setRadioSending(true);
                    }

                    continue;
                } else if (handPosition.fist && startMode) {
                    if (!armingMode) {
                        sendingArm = 28; // 28 * 40 ms

                        emit motorsArmedChanged(true);
                    } else if (startMode) {
                        sendingArm = 28; // 28 * 40 ms

                        emit motorsArmedChanged(false);
                    }

                    continue;
                }
            }
            if (sendingArm > 0) {
                if (!armingMode) {
                    this->setRadioValues(this->axisValueFromDouble(1), this->axisValueFromDouble(-1), this->axisValueFromDouble(0), this->axisValueFromDouble(0));
                    this->send(this->createAxisBuffer(this->axisValueFromDouble(1), this->axisValueFromDouble(-1), this->axisValueFromDouble(0), this->axisValueFromDouble(0)));
                } else {
                    this->setRadioValues(this->axisValueFromDouble(-1), this->axisValueFromDouble(-1), this->axisValueFromDouble(0), this->axisValueFromDouble(0));
                    this->send(this->createAxisBuffer(this->axisValueFromDouble(-1), this->axisValueFromDouble(-1), this->axisValueFromDouble(0), this->axisValueFromDouble(0)));
                }

                sendingArm--;
                if (sendingArm == 0) {
                    if (!armingMode) {
                        emit motorsArmedChanged(true);
                    } else {
                        emit motorsArmedChanged(false);
                    }
                    armingMode = !armingMode;
                }

                continue;
            }
            if (sendingStart > 0) {
                sendingStart--;
                if (sendingStart == 0) {
                    startMode = !startMode;
                }

                continue;
            }

            this->setRadioValues(this->axisValueFromDouble(0), this->axisValueFromDouble(handPosition.y), this->axisValueFromDouble(handPosition.x), this->axisValueFromDouble(handPosition.z));
            this->send(this->createAxisBuffer(this->axisValueFromDouble(0.0), this->axisValueFromDouble(handPosition.y), this->axisValueFromDouble(handPosition.x), this->axisValueFromDouble(handPosition.z)));
        }
        */
    }
}


void ThreadArduinoSend::setRadioSending(bool value) {
    Modes * modes = this->drone->getModes();
    if (modes->radioSending != value) {
        modes->radioSending = value;
        this->drone->setModes(modes);
    }
}

void ThreadArduinoSend::setMotorsArmed(bool value) {
    Modes * modes = this->drone->getModes();
    if (modes->motorsArmed != value) {
        modes->motorsArmed = value;
        this->drone->setModes(modes);
    }
}

void ThreadArduinoSend::setThrottleMode(bool value) {
    Modes * modes = this->drone->getModes();
    if (modes->throttleModeActive != value) {
        modes->throttleModeActive = value;
        this->drone->setModes(modes);
    }
}

void ThreadArduinoSend::setRadioValues(int leftX, int leftY, int rightX, int rightY) {
    Modes * modes = this->drone->getModes();
    modes->leftX = leftX;
    modes->leftY = leftY;
    modes->rightX = rightX;
    modes->rightY = rightY;
    this->drone->setModes(modes);
}


void ThreadArduinoSend::slotSendingDataChanged(SendingData * sendingData) {
    if (sendingData->name.compare("arduino0") == 0) {
        this->sendingData = sendingData;
    }
}

void ThreadArduinoSend::slotSteeringDataChanged(SteeringData * steeringData) {
    if (steeringData->name.compare("gamepad0") == 0) {
        this->steeringData = steeringData;
    }
}

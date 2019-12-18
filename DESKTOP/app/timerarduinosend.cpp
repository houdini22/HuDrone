#include "include.h"

#define EXECUTE_TIMEOUT 1
#define BUTTON_TIMEOUT 200

TimerArduinoSend::TimerArduinoSend(TimersArduino * timers, Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile)
    : TimerArduinoAbstract(timers, drone, sendingRegistry, steeringRegistry, profile) {
    connect(this->_timer, SIGNAL(timeout()), this, SLOT(execute()), Qt::DirectConnection);
    connect(this->_drone, SIGNAL(signalSendingsDataChanged(QHash<QString, SendingData>)), this, SLOT(slotSendingsDataChanged(QHash<QString, SendingData>)));
    connect(this->_drone, SIGNAL(signalSteeringsDataChanged(QHash<QString, SteeringData>)), this, SLOT(slotSteeringsDataChanged(QHash<QString, SteeringData>)));

    this->_stepThrottle = this->_profile->getMinLeftY();
}

int TimerArduinoSend::getMiliseconds() {
    return EXECUTE_TIMEOUT;
}

void TimerArduinoSend::radioSend() {
    Modes * modes = this->_drone->getModes();
    SteeringGamepadButtons buttons = this->_steerings_data["gamepad0"].buttons;

    if (modes->throttleModeActive) {
        this->setRadioValues(
                    this->_profile->getLeftX(buttons.leftX),
                    this->_stepThrottle,
                    this->_profile->getRightX(buttons.rightX),
                    this->_profile->getRightY(buttons.rightY));
    } else {
        this->setRadioValues(
                    this->_profile->getLeftX(buttons.leftX),
                    std::max(this->_profile->getLeftY(buttons.leftY), this->_profile->getMinLeftY()),
                    this->_profile->getRightX(buttons.rightX),
                    this->_profile->getRightY(buttons.rightY));
    }
}

void TimerArduinoSend::execute() {
    if (this->_steerings_data.contains("gamepad0")) {
        if (this->_lock > 0) {
            this->_lock--;
        }

        this->_miliseconds++;

        if (this->_sequenceInProgress) {
            this->_sequenceTime++;
        }

        Modes * modes = this->_drone->getModes();
        SteeringGamepadButtons buttons = this->_steerings_data["gamepad0"].buttons;

        if (this->_sequenceInProgress) {
            QMap<QString, int> values = this->_profile->getArmingSeqenceValueInTime(modes->motorsArmed, this->_sequenceTime);
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
                    this->setMotorsArmed(MOTORS_ARMING_IN_PROGRESS);
                    this->setMotorsArmed(MOTORS_ARMED);
                    return;
                } else if (modes->motorsArmed == MOTORS_DISARMING_IN_PROGRESS) {
                    this->setMotorsArmed(MOTORS_DISARMED);
                    return;
                }

                if (this->_miliseconds % 40 == 0) {
                    this->radioSend();
                    return;
                }
            } else {
                this->setRadioValues(
                            values["roll"] != -1 ? values["roll"] : this->_profile->getLeftX(buttons.leftX),
                            values["throttle"] != -1 ? values["throttle"] : this->_profile->getLeftY(buttons.leftY),
                            values["pitch"] != -1 ? values["pitch"] : this->_profile->getRightX(buttons.rightX),
                            values["yaw"] != -1 ? values["yaw"] : this->_profile->getRightY(buttons.rightY));
            }
        } else {
            if (this->_miliseconds % 40 == 0) {
                this->radioSend();
            }
        }

        if (this->_lock > 0) {
            return;
        }

        if (buttons.down) {
            if (!modes->throttleModeActive) {
                this->setThrottleMode(true);
            } else {
                this->setThrottleMode(false);
            }
            this->_lock = BUTTON_TIMEOUT;
            return;
        }

        if (buttons.left) {
            modes->thrust -= (double) (((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY()) / (double) this->_profile->getThrottleSteps()) / ((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY());
            if (modes->thrust < 0.0) {
                modes->thrust = 0.0;
            }
            this->_stepThrottle = this->_profile->getMinLeftY() + ((double) (this->_profile->getMaxLeftY() - this->_profile->getMinLeftY()) * modes->thrust);
            this->_drone->setModes(modes);
            this->_lock = BUTTON_TIMEOUT;
            return;
        }

        if (buttons.right) {
            modes->thrust += (double) (((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY()) / (double) this->_profile->getThrottleSteps()) / ((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY());
            if (modes->thrust > 1.0) {
                modes->thrust = 1.0;
            }
            this->_stepThrottle = this->_profile->getMinLeftY() + ((double) (this->_profile->getMaxLeftY() - this->_profile->getMinLeftY()) * modes->thrust);
            this->_drone->setModes(modes);
            this->_lock = BUTTON_TIMEOUT;
            return;
        }

        if (buttons.start) {
            if (!modes->radioSending) {
                this->send("n", false, false);
                this->setRadioSending(true);
            } else {
                this->send("f", false, false);
                this->setRadioSending(false);
            }
            this->_lock = BUTTON_TIMEOUT;
            return;
        }

        if (modes->radioSending) {
            if (buttons.l2 && buttons.r2) {
                if (modes->motorsArmed == MOTORS_DISARMED) {
                    this->setMotorsArmed(MOTORS_ARMING_IN_PROGRESS);
                    this->_lock = BUTTON_TIMEOUT;
                    return;
                } else if (modes->motorsArmed == MOTORS_ARMED) {
                    this->setMotorsArmed(MOTORS_DISARMING_IN_PROGRESS);
                    this->_lock = BUTTON_TIMEOUT;
                    return;
                }
            }
        }
    }
}

QString TimerArduinoSend::createAxisBuffer(double leftX, double leftY, double rightX, double rightY) {
    return this->createAxisBuffer(
                this->_profile->getLeftX(leftX),
                this->_profile->getLeftY(leftY),
                this->_profile->getRightX(rightX),
                this->_profile->getRightY(rightY));
}

QString TimerArduinoSend::createAxisBuffer(int leftX, int leftY, int rightX, int rightY) {
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

void TimerArduinoSend::setRadioSending(bool value) {
    Modes * modes = this->_drone->getModes();
    if (modes->radioSending != value) {
        modes->radioSending = value;
        this->_drone->setModes(modes);
    }
}

void TimerArduinoSend::setMotorsArmed(int value) {
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

void TimerArduinoSend::setThrottleMode(bool value) {
    Modes * modes = this->_drone->getModes();
    if (modes->throttleModeActive != value) {
        modes->throttleModeActive = value;
        this->_drone->setModes(modes);
    }
}

void TimerArduinoSend::setRadioValues(int leftX, int leftY, int rightX, int rightY) {
    Modes * modes = this->_drone->getModes();
    modes->leftX = leftX;
    modes->leftY = leftY;
    modes->rightX = rightX;
    modes->rightY = rightY;

    this->_drone->setModes(modes);

    this->send(this->createAxisBuffer(leftX,
                                      leftY,
                                      rightX,
                                      rightY), false, false);
}

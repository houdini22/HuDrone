#include "include.h"

#define BUTTON_TIMEOUT 8

TimerArduinoSend::TimerArduinoSend(TimersArduino * timers, Drone * drone, SendingRegistry * sendingRegistry, SteeringRegistry * steeringRegistry, Profile * profile)
    : TimerArduinoAbstract(timers, drone, sendingRegistry, steeringRegistry, profile) {
    connect(this->_timer, SIGNAL(timeout()), this, SLOT(execute()), Qt::DirectConnection);
}

int TimerArduinoSend::getMiliseconds() {
    return 20;
}

void TimerArduinoSend::execute() {
    if (this->_steerings_data.contains("gamepad0")) {
        if (this->_lock > 0) {
            this->_lock--;
        }

        Modes * modes = this->_drone->getModes();
        SteeringGamepadButtons buttons = this->_steerings_data.take("gamepad0").buttons;

        if (modes->throttleModeActive) {
            this->setRadioValues(
                        this->_profile->getLeftX(buttons.leftX),
                        this->_leftYthrottle,
                        this->_profile->getRightX(buttons.rightX),
                        this->_profile->getRightY(buttons.rightY));

            this->send(this->createAxisBuffer(this->_profile->getLeftX(buttons.leftX),
                                              this->_leftYthrottle,
                                              this->_profile->getRightX(buttons.rightX),
                                              this->_profile->getRightY(buttons.rightY)), false);
        } else {
            this->setRadioValues(
                        this->_profile->getLeftX(buttons.leftX),
                        this->_profile->getLeftY(buttons.leftY),
                        this->_profile->getRightX(buttons.rightX),
                        this->_profile->getRightY(buttons.rightY));

            this->send(this->createAxisBuffer(this->_profile->getLeftX(buttons.leftX),
                                              this->_profile->getLeftY(buttons.leftY),
                                              this->_profile->getRightX(buttons.rightX),
                                              this->_profile->getRightY(buttons.rightY)), false);
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
            modes->thrust += (double) (((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY()) / (double) this->_profile->getThrottleSteps()) / ((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY());
            if (modes->thrust > 1.0) {
                modes->thrust = 1.0;
            }
            this->_leftYthrottle = this->_profile->getMinLeftY() + ((double) (this->_profile->getMaxLeftY() - this->_profile->getMinLeftY()) * modes->thrust);
            this->_drone->setModes(modes);
            this->_lock = BUTTON_TIMEOUT;
            return;
        }

        if (buttons.right) {
            modes->thrust -= (double) (((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY()) / (double) this->_profile->getThrottleSteps()) / ((double) this->_profile->getMaxLeftY() - (double) this->_profile->getMinLeftY());
            if (modes->thrust < 0.0) {
                modes->thrust = 0.0;
            }
            this->_leftYthrottle = this->_profile->getMinLeftY() + ((double) (this->_profile->getMaxLeftY() - this->_profile->getMinLeftY()) * modes->thrust);
            this->_drone->setModes(modes);
            this->_lock = BUTTON_TIMEOUT;
            return;
        }

        if (buttons.start) {
            if (!modes->radioSending) {
                this->send("n", false);
                this->setRadioSending(true);
            } else {
                this->send("f", false);
                this->setRadioSending(false);
            }
            this->_lock = BUTTON_TIMEOUT;
            return;
        }

        if (modes->radioSending) {
            if (buttons.l2 && buttons.r2) {
                if (!modes->motorsArmed) {
                    // send
                    this->setMotorsArmed(true);
                } else {
                    this->setMotorsArmed(false);
                }
                this->_lock = BUTTON_TIMEOUT;
                return;
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

void TimerArduinoSend::setMotorsArmed(bool value) {
    Modes * modes = this->_drone->getModes();
    if (modes->motorsArmed != value) {
        modes->motorsArmed = value;
        this->_drone->setModes(modes);
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
}

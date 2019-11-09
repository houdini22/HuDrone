#include "include.h"

ThreadGamepadUpdate::ThreadGamepadUpdate(SteeringRegistry * registry, Drone * drone): QThread() {
    this->registry = registry;
    this->drone = drone;
    connect(this->registry, SIGNAL(signalSteeringDataChanged(SteeringData *)), this, SLOT(slotSteeringDataChanged(SteeringData *)));
}

void ThreadGamepadUpdate::run() {
    return;
    while (1) {
        QThread::msleep(40);

        nlohmann::json data;// = Storage::getInstance().getData();
        SteeringData * steeringData = this->steeringData;
        Modes * modes = this->drone->getModes();
/*
        if (steeringData->isConnected) {
            GamepadUpdate();

            double _leftX = GamepadStickLength(this->gamepad, STICK_LEFT) * cos(GamepadStickAngle(this->gamepad, STICK_LEFT));
            double _leftY = GamepadStickLength(this->gamepad, STICK_LEFT) * sin(GamepadStickAngle(this->gamepad, STICK_LEFT));
            double _rightX = GamepadStickLength(this->gamepad, STICK_RIGHT) * cos(GamepadStickAngle(this->gamepad, STICK_RIGHT));
            double _rightY = GamepadStickLength(this->gamepad, STICK_RIGHT) * sin(GamepadStickAngle(this->gamepad, STICK_RIGHT));

            if (GamepadButtonDown(this->gamepad, BUTTON_A)) {
                _rightY = -1.0;
            }
            if (GamepadButtonDown(this->gamepad, BUTTON_B)) {
                _rightX = 1.0;
            }
            if (GamepadButtonDown(this->gamepad, BUTTON_X)) {
                _rightX = -1.0;
            }
            if (GamepadButtonDown(this->gamepad, BUTTON_Y)) {
                _rightY = 1.0;
            }

            _leftX *= modes->thrust;
            _rightX *= modes->thrust;
            _rightY *= modes->thrust;

            if (_leftX < 0) {
                double area = data["radio"]["leftX"]["middle"].get<int>() - data["radio"]["leftX"]["min"].get<int>();
                _leftX = data["radio"]["leftX"]["middle"].get<int>() + (area * _leftX);
            } else {
                double area = data["radio"]["leftX"]["max"].get<int>() - data["radio"]["leftX"]["middle"].get<int>();
                _leftX = data["radio"]["leftX"]["middle"].get<int>() + (area * _leftX);
            }

            if (_rightX < 0) {
                double area = data["radio"]["rightX"]["middle"].get<int>() - data["radio"]["rightX"]["min"].get<int>();
                _rightX = data["radio"]["rightX"]["middle"].get<int>() + (area * _rightX);
            } else {
                double area = data["radio"]["rightX"]["max"].get<int>() - data["radio"]["rightX"]["middle"].get<int>();
                _rightX = data["radio"]["rightX"]["middle"].get<int>() + (area * _rightX);
            }

            if (_rightY < 0) {
                double area = data["radio"]["rightY"]["middle"].get<int>() - data["radio"]["rightY"]["min"].get<int>();
                _rightY = data["radio"]["rightY"]["middle"].get<int>() + (area * _rightY);
            } else {
                double area = data["radio"]["rightY"]["max"].get<int>() - data["radio"]["rightY"]["middle"].get<int>();
                _rightY = data["radio"]["rightY"]["middle"].get<int>() + (area * _rightY);
            }

            _leftY = std::max((double) data["radio"]["leftY"]["min"].get<int>(), data["radio"]["leftY"]["min"].get<int>() + (_leftY * (data["radio"]["leftY"]["max"].get<int>() - data["radio"]["leftY"]["min"].get<int>())));

            ButtonsPressed buttons;

            buttons.leftX = ((int) _leftX);
            buttons.leftY = ((int) _leftY);
            buttons.rightX = ((int) _rightX);
            buttons.rightY = ((int) _rightY);
            buttons.start = ((GamepadButtonDown(this->gamepad, BUTTON_START) ? true : false));
            buttons.arming = ((GamepadTriggerDown(this->gamepad, TRIGGER_LEFT) && GamepadTriggerDown(this->gamepad, TRIGGER_RIGHT)) ? true : false);
            buttons.a = (GamepadButtonDown(this->gamepad, BUTTON_A) ? true : false);
            buttons.b = (GamepadButtonDown(this->gamepad, BUTTON_B) ? true : false);
            buttons.x = (GamepadButtonDown(this->gamepad, BUTTON_X) ? true : false);
            buttons.y = (GamepadButtonDown(this->gamepad, BUTTON_Y) ? true : false);
            buttons.leftShoulder = (GamepadButtonDown(this->gamepad, BUTTON_LEFT_SHOULDER) ? true : false);
            buttons.rightShoulder = (GamepadButtonDown(this->gamepad, BUTTON_RIGHT_SHOULDER) ? true : false);
            buttons.dPadLeft = (GamepadButtonDown(this->gamepad, BUTTON_DPAD_LEFT) ? true : false);
            buttons.dPadRight = (GamepadButtonDown(this->gamepad, BUTTON_DPAD_RIGHT) ? true : false);
            buttons.dPadUp = (GamepadButtonDown(this->gamepad, BUTTON_DPAD_UP) ? true : false);
            buttons.dPadDown = (GamepadButtonDown(this->gamepad, BUTTON_DPAD_DOWN) ? true : false);

            emit signalButtonsChanged(buttons);
        }
        */
    }
}

void ThreadGamepadUpdate::slotSteeringDataChanged(SteeringData * steeringData) {
    if (steeringData->name.compare("gamepad0") == 0) {
        this->steeringData = steeringData;
    }
}

ThreadGamepad0Update::ThreadGamepad0Update(SteeringRegistry * registry, Drone * drone) : ThreadGamepadUpdate(registry, drone) {

}

ThreadGamepad1Update::ThreadGamepad1Update(SteeringRegistry * registry, Drone * drone) : ThreadGamepadUpdate(registry, drone) {

}

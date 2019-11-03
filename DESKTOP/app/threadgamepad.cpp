#include "include.h"

ThreadGamepad0::ThreadGamepad0() : QThread() {

}

void ThreadGamepad0::run() {
    while (1) {
        if (GamepadIsConnected(GAMEPAD_0)) {
            emit signalGamepadIsConnected(true);
        } else {
            emit signalGamepadIsConnected(false);
            GamepadInit();
        }

        QThread::msleep(1000);
    }
}

ThreadGamepad1::ThreadGamepad1() : QThread() {

}

void ThreadGamepad1::run() {
    while (1) {
        if (GamepadIsConnected(GAMEPAD_1)) {
            emit signalGamepadIsConnected(true);
        } else {

            emit signalGamepadIsConnected(false);
            GamepadInit();
        }

        QThread::msleep(1000);
    }
}

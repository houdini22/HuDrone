#pragma once
#include "include.h"

class SerialPortUtilities {
public:
    static QList<QSerialPortInfo> getAvailablePorts() {
        return QSerialPortInfo::availablePorts();
    }
};

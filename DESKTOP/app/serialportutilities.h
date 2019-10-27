#ifndef SERIALPORTUTILITIES_H
#define SERIALPORTUTILITIES_H

#include "include.h"

class SerialPortUtilities {
public:
    static QList<QSerialPortInfo> getAvailablePorts() {
        return QSerialPortInfo::availablePorts();
    }
};

#endif // SERIALPORTUTILITIES_H

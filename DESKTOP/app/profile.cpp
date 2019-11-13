#include "include.h"

Profile::Profile(T_JSON configuration) {
    this->_configuration = configuration;
}

int Profile::getLeftX(double value) {
    return this->getValueToSend(this->getFunction("roll"), value, false);
}

int Profile::getLeftY(double value) {
    return this->getValueToSend(this->getFunction("throttle"), value, true, true);
}

int Profile::getRightX(double value) {
    return this->getValueToSend(this->getFunction("pitch"), value, false);
}

int Profile::getRightY(double value) {
    return this->getValueToSend(this->getFunction("yaw"), value, true);
}

T_JSON Profile::getFunction(QString name) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        if (this->_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["function"].get<T_String>().compare(name.toStdString()) == 0) {
            return this->_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()];
        }
    }
}

int Profile::getValueToSend(T_JSON data, double value, bool invert, bool fromMin) {
    int min = QString(data["min"].get<T_String>().c_str()).toInt();
    int max = QString(data["max"].get<T_String>().c_str()).toInt();
    int middle = QString(data["middle"].get<T_String>().c_str()).toInt();
    int area = 0;
    int result = 0;

    if (invert) {
        value = value * -1.0;
    }

    if (fromMin) {
        area = max - min;
        result = (double) min + ((double) area * value);
        return result;
    }

    if (value < 0) {
        area = middle - min;
    } else {
        area = max - middle;
    }

    result = (double) middle + ((double) area * (double) value);
    return result;
}

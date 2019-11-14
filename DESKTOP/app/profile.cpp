#include "include.h"

Profile::Profile(T_JSON configuration) {
    this->_configuration = configuration;
}

Profile * Profile::byName(QString name) {
    T_JSON configProfiles = Config::getInstance().getData()["profiles"];

    for (T_JSON::iterator it = configProfiles.begin(); it != configProfiles.end(); ++it) {
        T_JSON val = it.value();
        if (val["name"].get<T_String>().compare(name.toStdString()) == 0) {
            return new Profile(val);
        }
    }

    return nullptr;
}

int Profile::getMinLeftY() {
    return this->getLeftY(0.0);
}

int Profile::getMaxLeftY() {
    return this->getLeftY(1.0);
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

int Profile::getThrottleSteps() {
    return this->_configuration["radio"]["throttleSteps"].get<int>();
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

    if (invert) {
        value = value * -1.0;
    }

    if (fromMin) {
        area = max - min;
        return (int) (double) min + ((double) area * value);
    }

    if (value < 0) {
        area = middle - min;
    } else {
        area = max - middle;
    }

    return (int) ((double) middle + ((double) area * (double) value));
}

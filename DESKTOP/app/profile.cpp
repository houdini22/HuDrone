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
    return this->getLeftY(-1.0);
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
    if (this->_throttleSteps == 0) {
        this->_throttleSteps = this->_configuration["radio"]["throttleSteps"].get<int>();
    }

    return this->_throttleSteps;
}

QString Profile::getChannelNumberOf(QString function) {
    if (!this->_channelNumbers.contains(function)) {
        for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
            if (this->_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["function"].get<T_String>().compare(function.toStdString()) == 0) {
                this->_channelNumbers[function] = QString::number(channelNumber);
            }
        }
    }

    if (!this->_channelNumbers.contains(function)) {
        return "";
    }

    return this->_channelNumbers[function];
}

QMap<QString, QString> Profile::getFunction(QString name) {
    if (!this->_channelFunctions.contains(name)) {
        for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
            if (this->_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["function"].get<T_String>().compare(name.toStdString()) == 0) {
                this->_channelFunctions[name] = QMap<QString, QString>();
                this->_channelFunctions[name]["min"] = QString(this->_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["min"].get<T_String>().c_str());
                this->_channelFunctions[name]["middle"] = QString(this->_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["middle"].get<T_String>().c_str());
                this->_channelFunctions[name]["max"] = QString(this->_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["max"].get<T_String>().c_str());
                break;
            }
        }
    }

    if (!this->_channelFunctions.contains(name)) {
        return QMap<QString, QString>();
    }

    return this->_channelFunctions[name];
}

int Profile::getValueToSend(QMap<QString, QString> data, double value, bool invert, bool fromMin) {
    int min = data["min"].toInt();
    int max = data["max"].toInt();
    int middle = data["middle"].toInt();
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

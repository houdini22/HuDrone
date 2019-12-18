#include "include.h"

Profile::Profile(T_JSON configuration, QString name) {
    this->_configuration = configuration;
    this->_name = name;

    this->loadArmingDisarmingValues();
}

Profile * Profile::byName(QString name) {
    T_JSON configProfiles = Config::getInstance().getData()["profiles"];

    for (T_JSON::iterator it = configProfiles.begin(); it != configProfiles.end(); ++it) {
        T_JSON val = it.value();
        if (val["name"].get<T_String>().compare(name.toStdString()) == 0) {
            return new Profile(val, name);
        }
    }

    return nullptr;
}

void Profile::loadArmingDisarmingValues() {
    T_JSON radio = this->_configuration["radio"];
    QMap<QString, int> sumsArming;
    QMap<QString, int> sumsDisarming;

    for (int i = 1; i < 9; i += 1) {
        T_JSON channel = radio[QString("channel").append(QString::number(i)).toStdString()];
        T_JSON arming = channel["arming"];
        T_JSON disarming = channel["disarming"];
        auto _function = QString(channel["function"].get<T_String>().c_str());

        sumsArming[_function] = 0;
        sumsDisarming[_function] = 0;

        for (T_JSON::iterator it = arming.begin(); it != arming.end(); ++it) {
            T_JSON val = it.value();

            QVector<int> vecArming;
            vecArming.push_back(sumsArming[_function]);
            vecArming.push_back(sumsArming[_function] + val["time"].get<int>());
            vecArming.push_back(val["value"].get<int>());

            this->_armingValues[_function].push_back(vecArming);

            sumsArming[_function] += val["time"].get<int>();
        }

        for (T_JSON::iterator it = disarming.begin(); it != disarming.end(); ++it) {
            T_JSON val = it.value();

            QVector<int> vecDisarming;
            vecDisarming.push_back(sumsDisarming[_function]);
            vecDisarming.push_back(sumsDisarming[_function] + val["time"].get<int>());
            vecDisarming.push_back(val["value"].get<int>());

            this->_disarmingValues[_function].push_back(vecDisarming);

            sumsDisarming[_function] += val["time"].get<int>();
        }

        std::reverse(this->_armingValues[_function].begin(), this->_armingValues[_function].end());
        std::reverse(this->_disarmingValues[_function].begin(), this->_disarmingValues[_function].end());
    }
}

QVector<QString> Profile::getFunctions() {
    QVector<QString> result {"pitch", "roll", "yaw", "throttle", "other_1", "other_2", "other_3", "other_4"};
    return result;
}

QMap<QString, int> Profile::getArmingSeqenceValueInTime(int motorMode, int time) {
    QVector<QString> _functions = this->getFunctions();
    QMap<QString, int> result;
    QMap<QString, QVector<QVector<int>>> values = motorMode == MOTORS_ARMING_IN_PROGRESS ? this->_armingValues : this->_disarmingValues;

    for (int i = 0; i < _functions.size(); i += 1) {
        result[_functions.at(i)] = -1;

        for (int j = 0; j < values[_functions.at(i)].size(); j += 1) {
            QVector<int> vec = values[_functions.at(i)].at(j);
            for (auto it = vec.begin(); it != vec.end(); ++it) {
                if (it[0] <= time && it[1] >= time) {
                    result[_functions.at(i)] = it[2];
                }
            }
        }
    }

    return result;
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

T_JSON Profile::getArmingValuesForChannel(int channelNumber) {
    return this->_configuration["radio"][QString("channel").append(QString::number(channelNumber)).toStdString()]["arming"];
}

T_JSON Profile::getDisarmingValuesForChannel(int channelNumber) {
    return this->_configuration["radio"][QString("channel").append(QString::number(channelNumber)).toStdString()]["disarming"];
}

void Profile::saveArmingDisarmingValueForChannel(int channel, QString action, T_JSON obj) {
    this->_configuration["radio"][QString("channel").append(QString::number(channel)).toStdString()][action.toStdString()].push_back(obj);
    this->save();
}

void Profile::addArmingDisarmingValueForChannel(QString channel, QString action, QString at, QString valueType, QString value) {
    this->_configuration["radio"][channel.toStdString()][action.toStdString()].at((unsigned long long) at.toInt())[valueType.toStdString()] = value.toInt();
    this->save();
}

void Profile::saveValueForChannel(QString channelNumber, QString valueName, QString value) {
    this->_configuration["radio"][channelNumber.toStdString()][valueName.toStdString()] = value.toStdString();
    this->save();
}

void Profile::removeArmingDisarmingPosition(QString channel, QString action, QString at) {
    this->_configuration["radio"][channel.toStdString()][action.toStdString()].erase((unsigned long long) at.toInt());
    this->save();
}

void Profile::save() {
    T_JSON data = Config::getInstance().getData();

    unsigned long long i = 0;
    for (T_JSON::iterator it = data["profiles"].begin(); it != data["profiles"].end(); ++it) {
        T_JSON profile = it.value();
        T_String _profileName = profile["name"].get<T_String>();
        if (_profileName.compare(this->_name.toStdString()) == 0) {
            data["profiles"].at(i) = this->_configuration;
            break;
        }
        i += 1;
    }

    Config::getInstance().setData(data)->save();
}

int Profile::getValueFromChannel(int channelNumber, T_String value) {
    return QString(this->_configuration["radio"][QString("channel").append(QString::number(channelNumber)).toStdString()][value].get<T_String>().c_str()).toInt();
}

QString Profile::getStringValueFromChannel(int channelNumber, T_String value) {
    return QString(this->_configuration["radio"][QString("channel").append(QString::number(channelNumber)).toStdString()][value].get<T_String>().c_str());
}

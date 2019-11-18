#pragma once
#include "include.h"

typedef std::vector<QString> T_ReceiversNamesList;

class Receivers {
public:
    static Receivers * fromConfig() {
        Receivers * instance = new Receivers(Config::createInstance("receivers.json"));
        return instance;
    }

    Receivers(Config * config) {
        this->_config = config;
    }

    T_ReceiversNamesList getNames() {
        T_ReceiversNamesList result;
        T_JSON _data = this->_config->getData();
        T_JSON _receivers = _data["receivers"];

        for (T_JSON::iterator it = _receivers.begin(); it != _receivers.end(); ++it) {
            T_JSON _value = it.value();
            T_String _name = _value["name"].get<T_String>();

            QString name(_name.c_str());

            result.push_back(name);
        }

        return result;
    }

    int getValueFromChannel(T_String receiverName, int channelNumber, T_String value) {
        T_JSON _data = this->_config->getData();
        T_JSON _receivers = _data["receivers"];

        for (T_JSON::iterator it = _receivers.begin(); it != _receivers.end(); ++it) {
            T_JSON _value = it.value();
            T_String _name = _value["name"].get<T_String>();

            if (_name.compare(receiverName) == 0) {
                return _value["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()][value].get<int>();
            }
        }

        return -1;
    }
private:
    Config * _config;
};

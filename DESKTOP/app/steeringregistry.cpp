#include "include.h"

SteeringRegistry::SteeringRegistry(Drone * drone) {
    this->_drone = drone;

    connect(this, SIGNAL(signalSteeringsDataChanged(QVector<SteeringData>)), this->_drone, SLOT(slotSteeringsDataChanged(QVector<SteeringData>)));

    this->_gamepads = QGamepadManager::instance();
    connect(this->_gamepads, SIGNAL(gamepadConnected(int)), this, SLOT(slotGamepadConnected(int)));
    connect(this->_gamepads, SIGNAL(gamepadDisconnected(int)), this, SLOT(slotGamepadDisconnected(int)));
}

SteeringRegistry::~SteeringRegistry() {
    this->_steerings_data.clear();
}

void SteeringRegistry::slotGamepadConnected(int deviceId) {
    SteeringInterface * _h = new SteeringGamepad(this->_drone, this, deviceId);
    this->add(_h);
}

void SteeringRegistry::slotGamepadDisconnected(int deviceId) {
    for (int i = 0; i < this->_registry.size(); i += 1) {
        if (this->_registry.at(i)->getType().compare("gamepad") == 0) {
            auto * _h = (SteeringGamepad *) this->_registry.at(i);
            if (_h->getDeviceId() == deviceId) {
                QString name = _h->getData().name;

                _h->stop();
                delete _h;
                this->_registry.removeAt(i);

                for (int j = 0; j < this->_steerings_data.size(); j += 1) {
                    if (this->_steerings_data.at(j).name.compare(name) == 0) {
                        this->_steerings_data.removeAt(j);
                        break;
                    }
                }

                emit signalSteeringsDataChanged(this->_steerings_data);

                break;
            }
        }
    }
}

void SteeringRegistry::add(SteeringInterface * handler) {
    this->_registry.append(handler);

    connect(handler,
            SIGNAL(signalSteeringDataChanged(SteeringData)),
            this,
            SLOT(slotSteeringDataChanged(SteeringData)));

    this->_steerings_data.push_back(handler->getData());
}

void SteeringRegistry::slotSteeringDataChanged(SteeringData data) {
    for (int j = 0; j < this->_steerings_data.size(); j += 1) {
        if (this->_steerings_data.at(j).name.compare(data.name) == 0) {
            this->_steerings_data.removeAt(j);
            this->_steerings_data.push_back(data);
            break;
        }
    }
    emit signalSteeringsDataChanged(this->_steerings_data);
}

void SteeringRegistry::start() {
    emit signalSteeringsDataChanged(this->_steerings_data);
    this->startThreads();
}

void SteeringRegistry::stop() {
    this->stopThreads();
}

void SteeringRegistry::startThreads() {
    for (int i = 0; i < this->_registry.size(); i += 1) {
        this->_registry.at(i)->start();
    }
}

void SteeringRegistry::stopThreads() {
    for (int i = 0; i < this->_registry.size(); i += 1) {
        this->_registry.at(i)->stop();
    }
}

QVector<SteeringData> SteeringRegistry::getData() {
    return this->_steerings_data;
}

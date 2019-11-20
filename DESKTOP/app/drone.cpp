#include "include.h"
#include "mainwindow.h"

Drone::Drone(MainWindow * window) {
    this->_window = window;
    this->_modes = new Modes;

    if (Config::getInstance().getArray({"profiles"}).size() == 0) {
        this->openWizardAddProfile();
    }

    QMenu * menu = this->_window->menuBar()->findChild<QMenu*>(QString("menuHuDrone"));

    foreach (QAction *action, menu->actions()) {
        if (action->objectName().compare("actionSettings") == 0) {
            connect(action, SIGNAL(triggered(bool)), this, SLOT(handleMenuActionsSettingsTriggered(bool)));
        } else if (action->objectName().compare("actionExit") == 0) {
            connect(action, SIGNAL(triggered(bool)), this, SLOT(handleMenuActionsExitTriggered(bool)));
        }
    }
}

void Drone::openDialogFly(QString name) {
    if (this->_dialog_fly) {
        delete this->_dialog_fly;
        this->_dialog_fly = nullptr;
    }

    this->_dialog_fly = new DialogFly(this->_window, this, name);
    this->_dialog_fly->show();
    this->_dialog_fly->stackUnder(this->_window);
}

void Drone::openWizardAddProfile() {
    this->_wizard_add_profile = new WizardAddProfile(this->_window, this);
    this->_wizard_add_profile->show();
    this->_wizard_add_profile->stackUnder(this->_window);
    connect(this->_wizard_add_profile, SIGNAL(close()), this, SLOT(handleWizardAddProfileClosed()));
}

void Drone::handleWizardAddProfileClosed() {
    if (this->_wizard_add_profile) {
        this->_wizard_add_profile->close();
        disconnect(this->_wizard_add_profile, SIGNAL(close()), this, SLOT(handleWizardAddProfileClosed()));
        delete this->_wizard_add_profile;
        this->_wizard_add_profile = nullptr;
    }
}

void Drone::openWizardUpload() {
    this->_wizard_upload = new WizardUpload(this->_window, this);
    this->_wizard_upload->show();
    this->_wizard_upload->stackUnder(this->_window);
    connect(this->_wizard_upload, SIGNAL(close()), this, SLOT(handleWizardUploadClosed()));
}

void Drone::handleWizardUploadClosed() {
    if (this->_wizard_upload) {
        this->_wizard_upload->close();
        disconnect(this->_wizard_upload, SIGNAL(close()), this, SLOT(handleWizardUploadClosed()));
        delete this->_wizard_upload;
        this->_wizard_upload = nullptr;
    }
}

void Drone::openDialogEditProfile(QString name) {
    this->_dialog_edit_profile = new DialogEditProfile(this->_window, name);
    this->_dialog_edit_profile->show();
    this->_dialog_edit_profile->stackUnder(this->_window);
}

void Drone::handleDialogEditProfileClosed() {
    if (this->_dialog_edit_profile) {
        this->_dialog_edit_profile->close();
        disconnect(this->_dialog_edit_profile, SIGNAL(close()), this, SLOT(handleDialogEditProfileClosed()));
        delete this->_dialog_edit_profile;
        this->_dialog_edit_profile = nullptr;
    }
}

void Drone::handleMenuActionsSettingsTriggered(bool) {
    this->openWizardAddProfile();
}

void Drone::handleMenuActionsExitTriggered(bool) {
    QApplication::quit();
}

void Drone::notifyConfigurationChanged() {
    emit configurationChanged();
}

void Drone::slotSteeringDataChanged(SteeringData data) {
    emit signalSteeringDataChanged(data);
}

void Drone::slotSendingsDataChanged(QHash<QString, SendingData > data) {
    qDebug() << "Drone::slotSendingsDataChanged" << data.size();
    emit signalSendingsDataChanged(data);
}

void Drone::slotSteeringsDataChanged(QHash<QString, SteeringData> data) {
    emit signalSteeringsDataChanged(data);
}

void Drone::setModes(Modes * modes) {
    this->_modes = modes;
    emit signalModesChanged(modes);
}

Modes * Drone::getModes() {
    return this->_modes;
}

void Drone::slotArduinoConnected(QSerialPort * arduino) {
    this->setArduino(arduino);
}

void Drone::setArduino(QSerialPort * arduino) {
    this->_arduino = arduino;
    this->_has_arduino = true;
}

bool Drone::hasArduino() {
    return this->_has_arduino;
}

void Drone::deleteArduino() {
    if (this->_has_arduino) {
        this->_has_arduino = false;
        this->_arduino->close();
        delete this->_arduino;
        this->_arduino = nullptr;
    }
}

void Drone::start(Profile * profile) {
    this->_steering_registry = new SteeringRegistry(this);
    this->_sending_registry = new SendingRegistry(this);

    this->startSendingTimers(profile);

    this->_steering_registry->add(new SteeringGamepad0(this, this->_steering_registry));
    this->_sending_registry->add(new SendingArduino(this, this->_sending_registry, this->_steering_registry, profile));

    emit signalModesChanged(this->_modes);

    this->_steering_registry->start();
    this->_sending_registry->start();
}

void Drone::stop() {
    this->_sending_registry->stop();
    this->_steering_registry->stop();

    this->stopSendingTimers();
    this->deleteArduino();

    delete this->_steering_registry;
    delete this->_sending_registry;
}

void Drone::stopSendingTimers() {
    if (this->_timers != nullptr) {
        this->_timers->stop();
        delete this->_timers;
        this->_timers = nullptr;
    }
}

void Drone::startSendingTimers(Profile * profile) {
    this->_timers = new TimersArduino(this, this->_sending_registry, this->_steering_registry, profile);
    this->_timers->start();
}

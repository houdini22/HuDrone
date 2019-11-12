#include "include.h"
#include "mainwindow.h"

Drone::Drone(MainWindow * window) {
    this->_window = window;
    this->modes = new Modes;

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

void Drone::openDialogFly() {
    if (this->_dialog_fly) {
        delete this->_dialog_fly;
        this->_dialog_fly = nullptr;
    }

    this->_dialog_fly = new DialogFly(this->_window, this);
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

void Drone::slotSteeringDataChanged(SteeringData * data) {
    emit signalSteeringDataChanged(data);
}

void Drone::slotSendingsDataChanged(QHash<QString,SendingData*> * data) {
    emit signalSendingsDataChanged(data);
}

void Drone::slotSteeringsDataChanged(QHash<QString,SteeringData*> * data) {
    emit signalSteeringsDataChanged(data);
}

void Drone::setModes(Modes * modes) {
    this->modes = modes;
    emit signalModesChanged(modes);
}

Modes * Drone::getModes() {
    return this->modes;
}

SteeringGamepad0 * Drone::getGamepad0() {
    return this->gamepad0;
}

SteeringGamepad1 * Drone::getGamepad1() {
    return this->gamepad1;
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

void Drone::start() {
    this->steeringRegistry = new SteeringRegistry(this);
    this->gamepad0 = new SteeringGamepad0(this, this->steeringRegistry);
    this->steeringRegistry->add(this->gamepad0);
    connect(this->steeringRegistry,
            SIGNAL(signalSteeringDataChanged(SteeringData*)),
            this,
            SLOT(slotSteeringDataChanged(SteeringData*)));
    connect(this->steeringRegistry,
            SIGNAL(signalSteeringsDataChanged(QHash<QString, SteeringData *> *)),
            this,
            SLOT(slotSteeringsDataChanged(QHash<QString, SteeringData *> *)));

    this->sendingRegistry = new SendingRegistry(this);

    this->_sending_arduino = new SendingArduino(this, this->sendingRegistry);
    this->sendingRegistry->add(this->_sending_arduino);
    connect(this->_sending_arduino,
            SIGNAL(signalArduinoConnected(QSerialPort *)),
            this,
            SLOT(slotArduinoConnected(QSerialPort *)));

    connect(this->sendingRegistry,
            SIGNAL(signalSendingsDataChanged(QHash<QString,SendingData*>*)),
            this,
            SLOT(slotSendingsDataChanged(QHash<QString,SendingData*>*)));

    this->sendingRegistry->start();
    this->steeringRegistry->start();

    this->sendingRegistry->startThreads();
    this->steeringRegistry->startThreads();
}

void Drone::stop() {
    disconnect(this->_sending_arduino,
            SIGNAL(signalArduinoConnected(QSerialPort *)),
            this,
            SLOT(slotArduinoConnected(QSerialPort *)));

    disconnect(this->steeringRegistry,
               SIGNAL(signalSteeringDataChanged(SteeringData*)),
               this,
               SLOT(slotSteeringDataChanged(SteeringData*)));

    disconnect(this->sendingRegistry,
               SIGNAL(signalSendingsDataChanged(QHash<QString,SendingData*>*)),
               this,
               SLOT(slotSendingsDataChanged(QHash<QString,SendingData*>*)));

    this->deleteArduino();

    this->sendingRegistry->stopThreads();
    this->steeringRegistry->stopThreads();

    delete this->steeringRegistry;
    delete this->sendingRegistry;
}

#include "include.h"
#include "mainwindow.h"

Drone::Drone(MainWindow * window) {
    this->_window = window;
    this->_wizard_add_profile = nullptr;

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

void Drone::openWizardAddProfile() {
    if (this->_wizard_add_profile) {
        this->_wizard_add_profile->close();
        delete this->_wizard_add_profile;
        this->_wizard_add_profile = nullptr;
    }

    this->_wizard_add_profile = new WizardAddProfile(this->_window, this);
    this->_wizard_add_profile->show();
    this->_wizard_add_profile->stackUnder(this->_window);
}

void Drone::handleMenuActionsSettingsTriggered(bool triggered) {
    this->openWizardAddProfile();
}

void Drone::handleMenuActionsExitTriggered(bool triggered) {
    QApplication::quit();
}

void Drone::start() {

}

void Drone::notifyConfigurationChanged() {
    emit configurationChanged();
}

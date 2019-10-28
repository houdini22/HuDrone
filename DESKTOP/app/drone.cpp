#include "include.h"
#include "mainwindow.h"

Drone::Drone(MainWindow * window) {
    this->_window = window;
    this->_wizard_config = nullptr;

    if (Config::getInstance().getArray({"profiles"}).size() == 0) {
        this->openWizardConfig();
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

void Drone::openWizardConfig() {
    if (this->_wizard_config) {
        this->_wizard_config->close();
        delete this->_wizard_config;
        this->_wizard_config = nullptr;
    }

    this->_wizard_config = new WizardConfig(this->_window, this);
    this->_wizard_config->show();
    this->_wizard_config->stackUnder(this->_window);
}

void Drone::handleMenuActionsSettingsTriggered(bool triggered) {
    this->openWizardConfig();
}

void Drone::handleMenuActionsExitTriggered(bool triggered) {
    QApplication::quit();
}

void Drone::start() {

}

void Drone::notifyConfigurationChanged() {
    emit configurationChanged();
}

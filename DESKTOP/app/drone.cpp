#include "include.h"
#include "mainwindow.h"

Drone::Drone(MainWindow * window) {
    this->_window = window;

    if (!Config::getInstance().getBool({"configurationWizard", "firstConfiguration"})) {
        this->_wizard_config = new WizardConfig(this->_window);
        this->_wizard_config->show();
        this->_wizard_config->stackUnder(this->_window);
    }
}

void Drone::start() {

}

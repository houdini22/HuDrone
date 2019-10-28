#include "include.h"

WizardConfig::WizardConfig(QWidget *parent, Drone * drone) : QWizard(parent) {
    this->_drone = drone;

    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    this->_configuration = Config::createInstance();
    this->_receivers = Receivers::fromConfig();

    addPage(new WizardConfigPage1);
    addPage(new WizardConfigPage2(this->_configuration));
    addPage(new WizardConfigPage5(this->_configuration, this->_receivers));
    addPage(new WizardConfigPage6(this->_configuration, this->_receivers));
    addPage(new WizardConfigPage7(this->_configuration, this->_receivers));
    addPage(new WizardConfigPage8(this->_configuration, this->_receivers));
    addPage(new WizardConfigPage9(this->_configuration, this->_receivers));

    setWindowTitle("Configuration Wizard");

    connect(this, SIGNAL(finished(int)), this, SLOT(onFinish()));
}

void WizardConfig::accept() {
    QDialog::accept();
}

void WizardConfig::onFinish() {
    this->saveConfiguration();
    this->_drone->notifyConfigurationChanged();
}

void WizardConfig::saveConfiguration() {
    T_JSON data = Config::getInstance().getData();
    data["profiles"].push_back(this->getConfiguration()->getData());
    Config::getInstance().setData(data)->save();
}

Config * WizardConfig::getConfiguration() {
    return this->_configuration;
}

Receivers * WizardConfig::getReceivers() {
    return this->_receivers;
}

#include "include.h"

WizardAddProfile::WizardAddProfile(QWidget *parent, Drone * drone) : QWizard(parent) {
    this->_drone = drone;

    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    this->_configuration = Config::createInstance();
    this->_receivers = Receivers::fromConfig();

    addPage(new WizardAddProfilePage1);
    addPage(new WizardAddProfilePage2(this->_configuration));
    addPage(new WizardAddProfilePage3(this->_configuration, this->_receivers));
    addPage(new WizardAddProfilePage4(this->_configuration, this->_receivers));
    addPage(new WizardAddProfilePage5(this->_configuration, this->_receivers));
    addPage(new WizardAddProfilePage6(this->_configuration, this->_receivers));
    addPage(new WizardAddProfilePage7(this->_configuration, this->_receivers));
    addPage(new WizardAddProfilePage8(this->_configuration, this->_receivers));

    setWindowTitle("Configuration Wizard");

    connect(this, SIGNAL(finished(int)), this, SLOT(onFinish()));
}

void WizardAddProfile::accept() {
    this->saveConfiguration();
    this->_drone->notifyConfigurationChanged();

    QDialog::accept();
}

void WizardAddProfile::onFinish() {
    delete this->_receivers;
    delete this->_configuration;
}

void WizardAddProfile::saveConfiguration() {
    T_JSON data = Config::getInstance().getData();
    data["profiles"].push_back(this->getConfiguration()->getData());
    Config::getInstance().setData(data)->save();
}

Config * WizardAddProfile::getConfiguration() {
    return this->_configuration;
}

Receivers * WizardAddProfile::getReceivers() {
    return this->_receivers;
}

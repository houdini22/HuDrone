#include "include.h"

WizardConfig::WizardConfig(QWidget *parent) : QWizard(parent) {
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    addPage(new WizardConfigPage1);
    addPage(new WizardConfigPage2);
    addPage(new WizardConfigPage3);
    addPage(new WizardConfigPage4);
    addPage(new WizardConfigPage5);
    addPage(new WizardConfigPage6);
    addPage(new WizardConfigPage7);
    addPage(new WizardConfigPage8);

    setWindowTitle("Configuration Wizard");

    this->_configuration = Config::createInstance();

    connect(this, SIGNAL(finished(int)), this, SLOT(onFinish()));
}

void WizardConfig::accept() {
    QDialog::accept();
}

void WizardConfig::onFinish() {
    this->saveConfiguration();
}

void WizardConfig::saveConfiguration() {
    std::cout << this->_configuration->getData().dump();
    T_JSON data = Config::getInstance().getData();
    data["profiles"].push_back(this->getConfiguration()->getData());
    Config::getInstance().setData(data)->save();
}

Config * WizardConfig::getConfiguration() {
    return this->_configuration;
}

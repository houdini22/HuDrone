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

    setWindowTitle("Configuration Wizard");
}

void WizardConfig::accept() {
   QDialog::accept();
}

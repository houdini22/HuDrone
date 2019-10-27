#include "include.h"

WizardConfig::WizardConfig(QWidget *parent) : QWizard(parent) {
    addPage(new WizardConfigPage1);
    addPage(new WizardConfigPage2);
    addPage(new WizardConfigPage3);
    addPage(new WizardConfigPage4);
    setWindowTitle("Configuration Wizard");
}

void WizardConfig::accept() {
   QDialog::accept();
}

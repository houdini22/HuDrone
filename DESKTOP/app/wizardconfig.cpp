#include "include.h"

WizardConfig::WizardConfig(QWidget *parent) : QWizard(parent) {
    addPage(new WizardConfigIntroPage);
    setWindowTitle("Configuration Wizard");
}

void WizardConfig::accept() {
   QDialog::accept();
}

#include "include.h"

WizardConfigPage6::WizardConfigPage6(QWidget *parent) : QWizardPage(parent) {
    setTitle("Choose your drone receiver from list below.");

    _layout = new QVBoxLayout;

    setLayout(_layout);
}

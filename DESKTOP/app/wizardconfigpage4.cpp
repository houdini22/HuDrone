#include "include.h"

WizardConfigPage4::WizardConfigPage4(QWidget *parent) : QWizardPage(parent) {
    setTitle("Your are ready to program your HuDrone Box.");

    _label = new QLabel("Leave your HuDrone Box connected and click Next.");
    _label->setWordWrap(true);

    _layout = new QVBoxLayout;
    _layout->addWidget(_label);

    setLayout(_layout);
}

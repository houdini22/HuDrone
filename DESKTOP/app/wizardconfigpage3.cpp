#include "include.h"

WizardConfigPage3::WizardConfigPage3(QWidget *parent) : QWizardPage(parent) {
    setTitle("Connect your HuDrone Box to the computer with USB cable.");

    _label = new QLabel("Status:");
    _label->setWordWrap(true);

    _label_status = new QLabel("not connected.");
    _label_status->setStyleSheet("QLabel { color: red }");

    _layout = new QVBoxLayout;
    _layout->addWidget(_label);
    _layout->addWidget(_label_status);

    setLayout(_layout);
}

#include "include.h"

WizardConfigPage1::WizardConfigPage1(QWidget *parent) : QWizardPage(parent) {
    setTitle("Hello, world!");

    _label = new QLabel("This wizard will setup HuDrone Software and HuDrone Box.");
    _label->setWordWrap(true);

    _layout = new QVBoxLayout;
    _layout->addWidget(_label);

    setLayout(_layout);
}

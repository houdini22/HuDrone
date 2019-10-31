#include "include.h"

WizardAddProfilePage1::WizardAddProfilePage1(QWidget *parent) : QWizardPage(parent) {
    setTitle("Create your configuration profile.");

    _label = new QLabel("This wizard will setup new profile for HuDrone™ Box.");
    _label->setWordWrap(true);

    _layout = new QVBoxLayout;
    _layout->addWidget(_label);

    setLayout(_layout);
}

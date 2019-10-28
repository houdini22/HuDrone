#include "include.h"

WizardUploadPage1::WizardUploadPage1(QWidget *parent) : QWizardPage(parent) {
    setTitle("Introduction");

    _label = new QLabel("This wizard will upload HuDrone™ Software to HuDrone™ Box.");
    _label->setWordWrap(true);

    _layout = new QVBoxLayout;
    _layout->addWidget(_label);

    setLayout(_layout);
}

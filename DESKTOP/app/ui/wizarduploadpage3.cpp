#include "include.h"

WizardUploadPage3::WizardUploadPage3(QWidget *parent) : QWizardPage(parent) {
    setTitle("Your are ready to upload HuDrone™ Sofware into your HuDrone™ Box.");

    _layout = new QVBoxLayout;

    QLabel * label = new QLabel("Leave HuDrone™ Box connected.");
    _layout->addWidget(label);

    setLayout(_layout);
}

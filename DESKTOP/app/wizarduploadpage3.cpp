#include "include.h"

WizardUploadPage3::WizardUploadPage3(QWidget *parent) : QWizardPage(parent) {
    setTitle("Summary HuDrone™ Sofware to upload.");

    _label = new QLabel("Leave your HuDrone™ Box connected and click Next.");
    _label->setWordWrap(true);

    _layout = new QVBoxLayout;
    _layout->addWidget(_label);

    setLayout(_layout);
}

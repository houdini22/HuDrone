#include "include.h"

WizardUpload::WizardUpload(QWidget *parent, Drone * drone) : QWizard(parent) {
    this->_drone = drone;

    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    addPage(new WizardUploadPage1);
    addPage(new WizardUploadPage2(this->_drone));
    addPage(new WizardUploadPage3);
    addPage(new WizardUploadPage4);

    setWindowTitle("Upload wizard");

    connect(this, SIGNAL(finished(int)), this, SLOT(onFinish()));
}

void WizardUpload::accept() {
    QDialog::accept();
}

void WizardUpload::onFinish() {
    //this->_drone->deleteArduino();
}

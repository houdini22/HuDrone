#include "include.h"

WizardAddProfilePage7::WizardAddProfilePage7(Config * configuration, Receivers * receivers) : QWizardPage(0) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Other settings.");

    _layout = new QHBoxLayout;

    _group_box_throttle_steps = new QGroupBox();
    _group_box_throttle_stepsBox->setTitle("Number of Trottle steps");

    _input_throttle_steps = new MyLineEdit();
    _input_throttle_steps->setText("10");
    _group_box_throttle_steps->addWidget(_input_throttle_steps);

    _layout->addWidget(_group_box_throttle_steps);

    setLayout(_layout);
}

void WizardAddProfilePage7::showEvent(QShowEvent *) {

}

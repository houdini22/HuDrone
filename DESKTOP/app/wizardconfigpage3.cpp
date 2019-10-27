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

void WizardConfigPage3::showEvent(QShowEvent *) {
    this->wizard()->button(QWizard::NextButton)->setEnabled(false);

    _thread_box_connect = new ThreadBoxConnect();
    connect(_thread_box_connect, SIGNAL(arduinoConnected(SerialPort *)), this, SLOT(handleArduinoConnected(SerialPort *)));
    _thread_box_connect->start();
}

void WizardConfigPage3::handleArduinoConnected(SerialPort * arduino) {
    _label_status->setStyleSheet("QLabel { color: green}");
    _label_status->setText("connected.");

    emit(arduinoConnected(arduino));

    this->wizard()->button(QWizard::NextButton)->setEnabled(true);
}

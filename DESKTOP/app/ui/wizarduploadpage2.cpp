#include "include.h"

WizardUploadPage2::WizardUploadPage2(Drone * drone) : QWizardPage() {
    this->_drone = drone;

    setTitle("Connect your HuDrone™ Box to the computer with USB cable.");

    _label = new QLabel("Status:");
    _label->setWordWrap(true);

    _label_status = new QLabel("not detected");
    _label_status->setStyleSheet("QLabel { color: red; font-size: 20px; }");

    _layout = new QVBoxLayout;
    _layout->addWidget(_label);
    _layout->addWidget(_label_status);

    setLayout(_layout);
}

void WizardUploadPage2::onWizardClose() {
    if (_thread_box_connect != nullptr) {
        if (_thread_box_connect->isRunning()) {
            _thread_box_connect->terminate();
            _thread_box_connect->wait();
        }

        disconnect(_thread_box_connect, SIGNAL(arduinoConnected(QSerialPort *)), this, SLOT(handleArduinoConnected(QSerialPort *)));
        disconnect(this->wizard()->button(QWizard::CancelButton), SIGNAL(clicked()), this, SLOT(onWizardClose()));

        delete _thread_box_connect;
        _thread_box_connect = nullptr;
    }
}

void WizardUploadPage2::showEvent(QShowEvent *) {
    disconnect(this->wizard()->button(QWizard::CancelButton), SIGNAL(clicked()), this, SLOT(onWizardClose()));
    connect(this->wizard()->button(QWizard::CancelButton), SIGNAL(clicked()), this, SLOT(onWizardClose()));

    this->wizard()->button(QWizard::NextButton)->setEnabled(false);

    if (_thread_box_connect == nullptr) {
        _thread_box_connect = new ThreadBoxConnect();
        connect(_thread_box_connect, SIGNAL(arduinoConnected(QSerialPort *)), this, SLOT(handleArduinoConnected(QSerialPort *)));
        _thread_box_connect->start();
    }
}

void WizardUploadPage2::handleArduinoConnected() {
    _label_status->setStyleSheet("QLabel { color: green; font-size: 20px; }");
    _label_status->setText("detected");

    _thread_box_connect->terminate();
    _thread_box_connect->wait();
    delete _thread_box_connect;
    _thread_box_connect = nullptr;

    this->wizard()->button(QWizard::NextButton)->setEnabled(true);
}

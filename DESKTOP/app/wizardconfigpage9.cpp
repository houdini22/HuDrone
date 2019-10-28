#include "include.h"

WizardConfigPage9::WizardConfigPage9(Config * configuration, Receivers * receivers) : QWizardPage(0) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Name your Profile");

    _layout = new QHBoxLayout;

    QLabel * label = new QLabel();
    label->setText("Name");

    this->_name_input = new QLineEdit;
    connect(this->_name_input, SIGNAL(textEdited(const QString &)), this, SLOT(nameInputTextEdited(const QString &)));

    _layout->addWidget(label);
    _layout->addWidget(this->_name_input);

    setLayout(_layout);
}

void WizardConfigPage9::showEvent(QShowEvent *) {
    QString name = "Device: ";
    name += QString(this->_configuration->getString({"device"}).c_str());
    name += ". Receiver: ";
    name += QString(this->_configuration->getString({"receiver"}).c_str());
    name += ".";

    this->_name_input->setText(name);
    this->_configuration->modify("add", "/name", name);
}

void WizardConfigPage9::nameInputTextEdited(const QString & text) {
    this->_configuration->modify("replace", "/name", text);
}

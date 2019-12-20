#include "include.h"

WizardAddProfilePage8::WizardAddProfilePage8(Config * configuration, Receivers * receivers) : QWizardPage(nullptr) {
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

void WizardAddProfilePage8::showEvent(QShowEvent *) {
    QString name = QString(this->_configuration->getString({"receiver"}).c_str());
    name += " - ";
    name += QString(this->_configuration->getString({"device"}).c_str());

    this->_name_input->setText(name);
    this->_configuration->modify("add", "/name", name);
    this->_configuration->modify("add", "/id", generate_random_string(32));
}

void WizardAddProfilePage8::nameInputTextEdited(const QString & text) {
    this->_configuration->modify("replace", "/name", text);
}

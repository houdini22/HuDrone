#include "include.h"

WizardConfigPage2::WizardConfigPage2(Config * configuration) : QWizardPage(0) {
    this->_configuration = configuration;

    setTitle("Choose your steering feature.");

    _button_glove = new QPushButton();
    _button_glove->setText("Glove");
    _button_glove->setMinimumHeight(75);

    QFont font_buttonGlove = _button_glove->font();
    font_buttonGlove.setPointSize(18);
    _button_glove->setFont(font_buttonGlove);


    _button_gamepad = new QPushButton();
    _button_gamepad->setText("GamePad");
    _button_gamepad->setMinimumHeight(75);

    QFont font_buttonGamePad = _button_gamepad->font();
    font_buttonGamePad.setPointSize(18);
    _button_gamepad->setFont(font_buttonGamePad);


    _layout = new QHBoxLayout;
    _layout->addWidget(_button_glove);
    _layout->addWidget(_button_gamepad);

    connect(_button_glove, SIGNAL(released()), this, SLOT(handleButtonGlove()));
    connect(_button_gamepad, SIGNAL(released()), this, SLOT(handleButtonGamepad()));

    setLayout(_layout);
}

void WizardConfigPage2::showEvent(QShowEvent *) {
    this->wizard()->button(QWizard::NextButton)->setEnabled(false);
}

void WizardConfigPage2::handleButtonGlove() {
    this->_configuration->modify("add", "/device", "glove");
    this->wizard()->next();
}

void WizardConfigPage2::handleButtonGamepad() {
    this->_configuration->modify("add", "/device", "gamepad");
    this->wizard()->next();
}

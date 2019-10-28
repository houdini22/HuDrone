#include "include.h"

WizardConfigPage7::WizardConfigPage7(Config * configuration, Receivers * receivers) : QWizardPage(0) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Verify or correct ARMING engine values.");

    _layout = new QHBoxLayout;

    _tabs = new WizardConfigChannelTabs();
    _layout->addWidget(_tabs->getTabWidget(), 1);
    _layout->addStretch(0);

    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {

    }

    setLayout(_layout);
}

T_JSON WizardConfigPage7::getValueFromChannel(int channelNumber, T_String value) {
    T_String receiverName = this->_configuration->getString({"receiver"});
    return T_JSON();
}

void WizardConfigPage7::showEvent(QShowEvent *) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {

    }
}

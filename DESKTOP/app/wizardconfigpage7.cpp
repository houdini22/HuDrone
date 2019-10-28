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

void WizardConfigPage7::showEvent(QShowEvent *) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {

    }
}

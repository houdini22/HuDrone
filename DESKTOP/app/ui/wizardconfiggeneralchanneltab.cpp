#include "include.h"

WizardConfigGeneralChannelTab::WizardConfigGeneralChannelTab(QWidget *parent) : QWidget(parent) {
    setLayout(new QGridLayout());
}

QGridLayout * WizardConfigGeneralChannelTab::getLayout() {
    return (QGridLayout *) this->layout();
}

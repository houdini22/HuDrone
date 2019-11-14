#include "include.h"

WizardConfigGeneralChannelTab::WizardConfigGeneralChannelTab(QWidget *parent) : QWidget(parent) {
    QGridLayout * _main_layout = new QGridLayout();

    setLayout(_main_layout);
}

QGridLayout * WizardConfigGeneralChannelTab::getLayout() {
    return _main_layout;
}

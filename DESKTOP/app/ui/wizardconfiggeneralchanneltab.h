#pragma once
#include "include.h"

class WizardConfigGeneralChannelTab : public QWidget {
    Q_OBJECT
public:
    explicit WizardConfigGeneralChannelTab(QWidget *parent = nullptr);
    QGridLayout * getLayout();
private:
    QGridLayout * _main_layout = nullptr;
};

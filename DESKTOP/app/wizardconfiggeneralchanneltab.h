#ifndef WIZARDCONFIGGENERALCHANNELTAB_H
#define WIZARDCONFIGGENERALCHANNELTAB_H

#include "include.h"

class WizardConfigGeneralChannelTab : public QWidget {
    Q_OBJECT
public:
    explicit WizardConfigGeneralChannelTab(QWidget *parent = 0);
    QGridLayout * getLayout();
private:
    QGridLayout * _main_layout;
};

#endif // WIZARDCONFIGGENERALCHANNELTAB_H

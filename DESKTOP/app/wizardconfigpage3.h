#ifndef WIZARDCONFIGINTROPAGE3_H
#define WIZARDCONFIGINTROPAGE3_H

#include "include.h"

class WizardConfigPage3 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage3(QWidget *parent = 0);
private:
    QLabel * _label;
    QLabel * _label_status;
    QVBoxLayout * _layout;
};

#endif // WIZARDCONFIGINTROPAGE3_H

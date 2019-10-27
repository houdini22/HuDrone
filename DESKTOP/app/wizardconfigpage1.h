#ifndef WIZARDCONFIGINTROPAGE1_H
#define WIZARDCONFIGINTROPAGE1_H

#include "include.h"

class WizardConfigPage1 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage1(QWidget *parent = 0);
private:
    QLabel * _label;
    QVBoxLayout * _layout;
};

#endif // WIZARDCONFIGINTROPAGE1_H

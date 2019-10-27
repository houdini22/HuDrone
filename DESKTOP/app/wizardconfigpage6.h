#ifndef WIZARDCONFIGINTROPAGE6_H
#define WIZARDCONFIGINTROPAGE6_H

#include "include.h"

class WizardConfigPage6 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage6(QWidget * parent = 0);
private:
    QLabel * _label;
    QVBoxLayout * _layout;
};

#endif // WIZARDCONFIGINTROPAGE6_H

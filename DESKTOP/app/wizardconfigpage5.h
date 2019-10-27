#ifndef WIZARDCONFIGINTROPAGE5_H
#define WIZARDCONFIGINTROPAGE5_H

#include "include.h"

class WizardConfigPage5 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage5(QWidget * parent = 0);
private:
    QLabel * _label;
    QVBoxLayout * _layout;
};

#endif // WIZARDCONFIGINTROPAGE4_H

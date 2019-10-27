#ifndef WIZARDCONFIGINTROPAGE4_H
#define WIZARDCONFIGINTROPAGE4_H

#include "include.h"

class WizardConfigPage4 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage4(QWidget * parent = 0);
private:
    QLabel * _label;
    QVBoxLayout * _layout;
};

#endif // WIZARDCONFIGINTROPAGE4_H

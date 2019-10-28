#ifndef WIZARDADDPROFILEPAGE1_H
#define WIZARDADDPROFILEPAGE1_H

#include "include.h"

class WizardAddProfilePage1 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage1(QWidget *parent = 0);
private:
    QLabel * _label;
    QVBoxLayout * _layout;
};

#endif // WIZARDADDPROFILEPAGE1_H

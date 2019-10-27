#ifndef WIZARDCONFIGINTROPAGE_H
#define WIZARDCONFIGINTROPAGE_H

#include "include.h"

class WizardConfigIntroPage : public QWizardPage
{
    Q_OBJECT

public:
    WizardConfigIntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};

#endif // WIZARDCONFIGINTROPAGE_H

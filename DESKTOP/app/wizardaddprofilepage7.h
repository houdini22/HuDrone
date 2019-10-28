#ifndef WIZARDADDPROFILEPAGE7_H
#define WIZARDADDPROFILEPAGE7_H

#include "include.h"

class WizardAddProfilePage7 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage7(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *);
private:
    QHBoxLayout * _layout;
    Config * _configuration;
    Receivers * _receivers;
    QLineEdit * _name_input;
private slots:
    void nameInputTextEdited(const QString &);
};

#endif // WIZARDADDPROFILEPAGE7_H

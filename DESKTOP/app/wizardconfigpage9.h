#ifndef WIZARDCONFIGINTROPAGE9_H
#define WIZARDCONFIGINTROPAGE9_H

#include "include.h"

class WizardConfigPage9 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage9(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *);
private:
    QHBoxLayout * _layout;
    Config * _configuration;
    Receivers * _receivers;
    QLineEdit * _name_input;
private slots:
    void nameInputTextEdited(const QString &);
};

#endif // WIZARDCONFIGINTROPAGE9_H

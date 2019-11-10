#ifndef WizardAddProfilePage8_H
#define WizardAddProfilePage8_H

#include "include.h"

class WizardAddProfilePage8 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage8(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *);
private:
    QHBoxLayout * _layout;
    Config * _configuration;
    Receivers * _receivers;
    QLineEdit * _name_input;
private slots:
    void nameInputTextEdited(const QString &);
};

#endif // WizardAddProfilePage8_H

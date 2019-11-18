#pragma once
#include "include.h"

class WizardAddProfilePage8 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage8(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *) override;
private:
    QHBoxLayout * _layout = nullptr;
    Config * _configuration = nullptr;
    Receivers * _receivers = nullptr;
    QLineEdit * _name_input = nullptr;
private slots:
    void nameInputTextEdited(const QString &);
};

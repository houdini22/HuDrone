#ifndef WIZARDADDPROFILEPAGE4_H
#define WIZARDADDPROFILEPAGE4_H

#include "include.h"

class WizardConfigChannelTabs;
class MyLineEdit;

class WizardAddProfilePage4 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage4(Config * configuration, Receivers * receivers);
private:
    int getValueFromChannel(int channelNumber, T_String value);
    void showEvent(QShowEvent *) override;
    QHBoxLayout * _layout = nullptr;
    Config * _configuration = nullptr;
    Receivers * _receivers = nullptr;
    WizardConfigChannelTabs * _tabs = nullptr;
    std::map<int, std::map<T_String, MyLineEdit *>> _inputs;
    std::map<int, MyComboBox *> _combos;
    QString getStringValueFromChannel(int, T_String);
    void validate();
public slots:
    void textEdited(QString, QString);
    void myComboBoxTextChanged(QString, int);
};

#endif // WIZARDADDPROFILEPAGE4_H

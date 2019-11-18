#pragma once
#include "include.h"

class TabsEditProfile;
class MyLineEdit;
class MyComboBox;

class DialogEditProfile : public QDialog {
    Q_OBJECT
public:
    DialogEditProfile(QWidget *parent, QString name);
private:
    QString _profile_name = nullptr;
    QHBoxLayout * _layout = nullptr;
    TabsEditProfile * _tabs = nullptr;
    std::map<int, std::map<T_String, MyLineEdit *>> _inputs;
    std::map<int, MyComboBox *> _combos;
    T_JSON _profile_configuration;
    int getValueFromChannel(int, T_String);
    QString getStringValueFromChannel(int, T_String);
    void setValueForChannel(QString, QString, QString);
    void setFunctionValueForChannel(int, QString);
    void showEvent(QShowEvent *) override;
public slots:
    void textEdited(QString, QString);
    void myComboBoxTextChanged(QString, int);
};

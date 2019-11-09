#ifndef DIALOGEDITPROFILE_H
#define DIALOGEDITPROFILE_H

#include "include.h"

class TabsEditProfile;
class MyLineEdit;
class MyComboBox;

class DialogEditProfile : public QDialog {
    Q_OBJECT
public:
    DialogEditProfile(QWidget *parent, QString name);
private:
    QString _profile_name;
    QHBoxLayout * _layout;
    TabsEditProfile * _tabs;
    std::map<int, std::map<T_String, MyLineEdit *>> _inputs;
    std::map<int, MyComboBox *> _combos;
    T_JSON _profile_configuration;
    int getValueFromChannel(int channelNumber, T_String value);
    QString getStringValueFromChannel(int, T_String);
    void setValueForChannel(QString channelNumber, QString valueName, QString value);
    void setFunctionValueForChannel(int, QString);
    void showEvent(QShowEvent *event);
public slots:
    void textEdited(QString, QString);
    void myComboBoxTextChanged(QString, int);
};

#endif // DIALOGEDITPROFILE_H

#ifndef DIALOGEDITPROFILE_H
#define DIALOGEDITPROFILE_H

#include "include.h"

class TabsEditProfile;
class MyLineEdit;

typedef std::map<int, std::map<T_String, MyLineEdit *>> T_InputMap;

class DialogEditProfile : public QDialog {
    Q_OBJECT
public:
    DialogEditProfile(QWidget *parent, QString name);
private:
    QString _profile_name;
    QHBoxLayout * _layout;
    TabsEditProfile * _tabs;
    T_InputMap _inputs;
    T_JSON _profile_configuration;
    int getValueFromChannel(int channelNumber, T_String value);
    void setValueForChannel(QString channelNumber, QString valueName, QString value);
    void showEvent(QShowEvent *event);
public slots:
    void textEdited(QString, QString);
};

#endif // DIALOGEDITPROFILE_H
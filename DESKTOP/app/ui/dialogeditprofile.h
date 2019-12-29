#pragma once
#include "include.h"

class TabsEditProfile;
class MyLineEdit;
class MyComboBox;
class MyPushButton;
class ArmingDisarmingSettings;

class DialogEditProfile : public QDialog {
    Q_OBJECT
public:
    DialogEditProfile(QWidget *parent, QString name);
private:
    QHBoxLayout * _layout = nullptr;
    TabsEditProfile * _tabs = nullptr;
    std::map<int, std::map<T_String, MyLineEdit *>> _inputs;
    std::map<int, MyComboBox *> _combos;
    Profile * _profile = nullptr;
    MyLineEdit * _input_throttle_steps = nullptr;
    QGroupBox * _group_box_throttle_steps = nullptr;
    QLabel * _label_throttle_label = nullptr;
    QLabel * _label_throttle_value = nullptr;
    int getValueFromChannel(int, T_String);
    QString getStringValueFromChannel(int, T_String);
    void setValueForChannel(QString, QString, QString);
    void setFunctionValueForChannel(int, QString);
    void showEvent(QShowEvent *) override;
    void renderChannels();
    void renderArming();
    void renderDisarming();
    void renderOther();

    ArmingDisarmingSettings * _armingSettings = nullptr;
    ArmingDisarmingSettings * _disarmingSettings = nullptr;
public slots:
    void textEdited(QString, QString);
    void myComboBoxTextChanged(QString, int);
    int slotThrottleStepsEdited(const QString &, QString);
};

#pragma once

#include <include.h>

class TabsEditProfileGeneralTab;

class ArmingDisarmingSettings : public QWidget {
    Q_OBJECT
public:
    explicit ArmingDisarmingSettings(QWidget *, TabsEditProfileGeneralTab *, Profile *, QString action);
private:
    Profile * _profile = nullptr;
    TabsEditProfileGeneralTab * _tab = nullptr;
    void render();
    void addArmingDisarmingRow(QString, QString, bool, int, int);
    std::map<int, int> _data;
    QString _action = "";
    T_JSON getValues(int);
private slots:
    void slotMyPushButton(MyPushButton *);
    void slotMyPushButtonDelete(MyPushButton *);
    void slotMyTextEdited(MyLineEdit *);
};

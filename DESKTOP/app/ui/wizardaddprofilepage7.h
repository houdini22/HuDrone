#ifndef WIZARDADDPROFILEPAGE7_H
#define WIZARDADDPROFILEPAGE7_H

#include "include.h"

class WizardAddProfilePage7 : public QWizardPage {
    Q_OBJECT
public:
    WizardAddProfilePage7(Config * configuration, Receivers * receivers);
    void showEvent(QShowEvent *) override;
private:
    QVBoxLayout * _layout = nullptr;
    Config * _configuration = nullptr;
    Receivers * _receivers = nullptr;
    WizardConfigChannelTabs * _tabs = nullptr;
    MyLineEdit * _input_throttle_steps = nullptr;
    QGroupBox * _group_box_throttle_steps = nullptr;
    QLabel * _label_throttle_label = nullptr;
    QLabel * _label_throttle_value = nullptr;
private slots:
    int myTextEdited(const QString &, QString);
};

#endif // WIZARDADDPROFILEPAGE7_H

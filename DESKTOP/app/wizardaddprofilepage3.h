#ifndef WIZARDADDPROFILEPAGE3_H
#define WIZARDADDPROFILEPAGE3_H

#include "include.h"

class WizardAddProfilePage3 : public QWizardPage
{
    Q_OBJECT
public:
    WizardAddProfilePage3(Config * configuration, Receivers * receivers);
private:
    QVBoxLayout * _layout = nullptr;
    QListWidget * _list_widget = nullptr;
    Config * _configuration = nullptr;
    Receivers * _receivers = nullptr;
public slots:
    void onListItemClicked(QListWidgetItem *);
    void showEvent(QShowEvent *);
};

#endif // WIZARDADDPROFILEPAGE3_H

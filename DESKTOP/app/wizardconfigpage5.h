#ifndef WIZARDCONFIGINTROPAGE5_H
#define WIZARDCONFIGINTROPAGE5_H

#include "include.h"

class WizardConfigPage5 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage5(Config * configuration, Receivers * receivers);
private:
    QVBoxLayout * _layout;
    QListWidget * _list_widget;
    Config * _configuration;
    Receivers * _receivers;
public slots:
    void onListItemClicked(QListWidgetItem *);
    void showEvent(QShowEvent *);
};

#endif // WIZARDCONFIGINTROPAGE5_H

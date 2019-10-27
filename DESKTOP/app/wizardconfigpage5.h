#ifndef WIZARDCONFIGINTROPAGE5_H
#define WIZARDCONFIGINTROPAGE5_H

#include "include.h"

class WizardConfigPage5 : public QWizardPage
{
    Q_OBJECT
public:
    WizardConfigPage5(QWidget * parent = 0);
private:
    QVBoxLayout * _layout;
    QListWidget * _list_widget;
public slots:
    void onListItemClicked(QListWidgetItem *);
    void showEvent(QShowEvent *);
};

#endif // WIZARDCONFIGINTROPAGE5_H

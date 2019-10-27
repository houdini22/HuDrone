#include "include.h"

WizardConfigPage5::WizardConfigPage5(QWidget *parent) : QWizardPage(parent) {
    setTitle("Choose your drone receiver from list below.");

    _layout = new QVBoxLayout;

    _list_widget = new QListWidget(this);

    QListWidgetItem * newItem = new QListWidgetItem;
    newItem->setText("FlySky FS-IA6B");
    _list_widget->insertItem(0, newItem);

    _layout->addWidget(_list_widget);

    setLayout(_layout);
}

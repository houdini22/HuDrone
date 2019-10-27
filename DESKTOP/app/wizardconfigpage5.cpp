#include "include.h"

WizardConfigPage5::WizardConfigPage5(QWidget *parent) : QWizardPage(parent) {
    setTitle("Choose your drone receiver from list below.");

    _layout = new QVBoxLayout;

    _list_widget = new QListWidget(this);

    T_JSON receivers = Config::getInstance().getArray({"receivers"});

    int i = 0;
    for (T_JSON::iterator it = receivers.begin(); it != receivers.end(); ++it, i += 1) {
        T_JSON value = it.value();
        T_String label1 = value["label"].get<std::string>();
        QString label2(label1.c_str());

        QListWidgetItem * newItem = new QListWidgetItem();
        newItem->setText(label2);
        _list_widget->insertItem(i, newItem);
    }

    connect(_list_widget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onListItemClicked(QListWidgetItem*)));

    _layout->addWidget(_list_widget);

    setLayout(_layout);
}


void WizardConfigPage5::onListItemClicked(QListWidgetItem *) {
    this->wizard()->button(QWizard::NextButton)->setEnabled(true);
}

void WizardConfigPage5::showEvent(QShowEvent *) {
    this->wizard()->button(QWizard::NextButton)->setEnabled(false);
}

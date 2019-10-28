#include "include.h"

WizardConfigPage5::WizardConfigPage5(Config * configuration, Receivers * receivers) : QWizardPage(0) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Choose your drone receiver from list below.");

    _layout = new QVBoxLayout;
    _list_widget = new QListWidget(this);

    T_ReceiversNamesList receiverNames = this->_receivers->getNames();
    for (unsigned long long i = 0; i < receiverNames.size(); i += 1) {
        QString _label = receiverNames.at(i);

        QListWidgetItem * newItem = new QListWidgetItem();
        newItem->setText(_label);

        _list_widget->insertItem((int) i, newItem);
    }

    connect(_list_widget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onListItemClicked(QListWidgetItem*)));

    _layout->addWidget(_list_widget);

    setLayout(_layout);
}


void WizardConfigPage5::onListItemClicked(QListWidgetItem * item) {
    this->_configuration->modify("add", "/receiver", item->text());
    this->_configuration->modify("add", "/radio", "{}");
    this->wizard()->button(QWizard::NextButton)->setEnabled(item->isSelected());
}

void WizardConfigPage5::showEvent(QShowEvent * ) {
    this->wizard()->button(QWizard::NextButton)->setEnabled(false);
}

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

    T_JSON radio = T_JSON::object();
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        T_JSON _v = T_JSON::object();
        _v["min"] = 0;
        _v["middle"] = 0;
        _v["max"] = 0;
        _v["default"] = 0;
        _v["arming"] = T_JSON::array();
        _v["disarming"] = T_JSON::array();

        radio[QString("channel" + QString::number(channelNumber)).toStdString()] = _v;
    }

    T_JSON data = this->_configuration->getData();
    data["radio"] = radio;
    this->_configuration->setData(data);

    this->wizard()->button(QWizard::NextButton)->setEnabled(item->isSelected());
}

void WizardConfigPage5::showEvent(QShowEvent * ) {
    this->wizard()->button(QWizard::NextButton)->setEnabled(false);
}

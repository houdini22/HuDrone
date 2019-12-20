#include "include.h"

WizardAddProfilePage5::WizardAddProfilePage5(Config * configuration, Receivers * receivers) : QWizardPage(nullptr) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Enter ARMING engine values.");

    _layout = new QHBoxLayout;

    _tabs = new WizardConfigChannelTabs();
    _layout->addWidget(_tabs->getTabWidget(), 1);
    _layout->addStretch(0);

    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        MyPushButton * addButton = MyPushButton::factory(this)
                ->setText("Add send action")
                ->setParameter("tab", QString::number(i))
                ->setParameter("action", "disarming");

        connect(addButton, SIGNAL(myReleased(MyPushButton *)), this, SLOT(slotMyPushButton(MyPushButton *)));

        _tabs
                ->getTabWidget()
                ->setTabText(i,
                             QString(this->_configuration->getData()["radio"][QString("channel").append(QString::number((channelNumber))).toStdString()]["function"].get<T_String>().c_str()));

        WizardConfigGeneralChannelTab * tab = (WizardConfigGeneralChannelTab *) _tabs
                ->getTab(i);

        tab->getLayout()->addWidget(addButton, 0, 0, 0, 6, Qt::AlignTop);

        this->_add_buttons[2][i] = 0;
    }

    setLayout(_layout);
}

void WizardAddProfilePage5::showEvent(QShowEvent *) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {

    }
}

void WizardAddProfilePage5::slotMyPushButton(MyPushButton *) {

}

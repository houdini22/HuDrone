#include "include.h"

WizardAddProfilePage5::WizardAddProfilePage5(Config * configuration, Receivers * receivers) : QWizardPage(nullptr) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Enter ARMING engine radio values.");

    _layout = new QHBoxLayout;

    _tabs = new WizardConfigChannelTabs();
    _layout->addWidget(_tabs->getTabWidget(), 1);
    _layout->addStretch(0);

    this->renderArming();

    setLayout(_layout);
}

void WizardAddProfilePage5::renderArming() {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        MyPushButton * addButton = MyPushButton::factory(this)
                ->setText("Add send action")
                ->setParameter("tab", QString::number(i))
                ->setParameter("action", "arming");

        connect(addButton, SIGNAL(myReleased(MyPushButton *)), this, SLOT(slotMyPushButton(MyPushButton *)));

        WizardConfigGeneralChannelTab * tab = (WizardConfigGeneralChannelTab *) _tabs
                ->getTab(i);

        tab->getLayout()->addWidget(addButton, 0, 0, 0, 6, Qt::AlignTop);

        this->_add_buttons[2][i] = 0;
    }
}

void WizardAddProfilePage5::showEvent(QShowEvent *) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        _tabs
                ->getTabWidget()
                ->setTabText(i,
                             QString(this->_configuration->getData()["radio"][QString("channel").append(QString::number((channelNumber))).toStdString()]["function"].get<T_String>().c_str()));
    }
}

void WizardAddProfilePage5::slotMyPushButton(MyPushButton * button) {
    this->addArmingDisarmingRow(button->getParameter("action"), button->getParameter("tab"), true, 0, 0);
}

void WizardAddProfilePage5::addArmingDisarmingRow(QString action, QString tabNum, bool addToConfig, int timeValue, int value) {
    this->_add_buttons[action.compare("arming") == 0 ? 1 : 2][tabNum.toInt()]++;
    int row = this->_add_buttons[action.compare("arming") == 0 ? 1 : 2][tabNum.toInt()];

    auto inputLength = new MyLineEdit(this);
    inputLength->setValidator(new QIntValidator(1, 10000, this));
    inputLength->setText(QString::number(timeValue));
    inputLength->setParameter("action", action)
            ->setParameter("valueType", "time")
            ->setParameter("row", QString::number(row - 1))
            ->setParameter("channel", QString("channel").append(QString::number(tabNum.toInt() + 1)));

    connect(inputLength, SIGNAL(myTextEdited(MyLineEdit *)), this, SLOT(slotMyTextEdited(MyLineEdit *)));

    auto inputValue = new MyLineEdit(this);
    inputValue->setValidator(new QIntValidator(0, 2000, this));
    inputValue->setText(QString::number(value));
    inputValue->setParameter("action", action)
            ->setParameter("valueType", "value")
            ->setParameter("row", QString::number(row - 1))
            ->setParameter("channel", QString("channel").append(QString::number(tabNum.toInt() + 1)));

    connect(inputValue, SIGNAL(myTextEdited(MyLineEdit *)), this, SLOT(slotMyTextEdited(MyLineEdit *)));

    auto deleteButton = MyPushButton::factory(this)
            ->setParameter("tab", tabNum)
            ->setParameter("action", action)
            ->setParameter("channel", QString("channel").append(QString::number(tabNum.toInt() + 1)))
            ->setParameter("at", QString::number(row - 1))
            ->setText("Delete");

    connect(deleteButton, SIGNAL(myReleased(MyPushButton *)), this, SLOT(slotMyPushButtonDelete(MyPushButton *)));

    WizardConfigGeneralChannelTab * tab =(WizardConfigGeneralChannelTab *) _tabs
            ->getTab(tabNum.toInt());

    auto labelLength = new QLabel(this);
    labelLength->setText("Time: (0 - 10000)");

    auto labelValue = new QLabel(this);
    labelValue->setText("Value: (0 - 2000)");

    auto label = new QLabel(this);
    label->setText(QString::number(row).append("."));

    tab->getLayout()->addWidget(label, row, 0, Qt::AlignTop);
    tab->getLayout()->addWidget(labelLength, row, 1, Qt::AlignTop);
    tab->getLayout()->addWidget(inputLength, row, 2, Qt::AlignTop);
    tab->getLayout()->addWidget(labelValue, row, 3, Qt::AlignTop);
    tab->getLayout()->addWidget(inputValue, row, 4, Qt::AlignTop);
    tab->getLayout()->addWidget(deleteButton, row, 5, Qt::AlignTop);

    if (addToConfig) {
        T_JSON obj = T_JSON::object();
        obj["time"] = 0;
        obj["value"] = 0;

        T_JSON data = this->_configuration->getData();
        data["radio"][QString("channel").append(QString::number(tabNum.toInt() + 1)).toStdString()]["arming"].push_back(obj);
        this->_configuration->setData(data);
    }
}

void WizardAddProfilePage5::slotMyPushButtonDelete(MyPushButton * button) {
    QString channel = button->getParameter("channel");
    QString action = button->getParameter("action");
    QString at = button->getParameter("at");

    //this->_profile->removeArmingDisarmingPosition(channel, action, at);

    for (int j = 0; j < 8; j += 1) {
        WizardConfigGeneralChannelTab * tab = (WizardConfigGeneralChannelTab *) _tabs
                ->getTab(j);

        for (int k = 1; k <= this->_add_buttons[1][j]; k += 1) {
            GridLayoutUtil::removeRow(tab->getLayout(), k, true);
        }

        this->_add_buttons[1][j] = 0;
    }

    this->renderArming();
}

void WizardAddProfilePage5::slotMyTextEdited(MyLineEdit * input) {
    //this->_profile->addArmingDisarmingValueForChannel(input->getParameter("channel"), input->getParameter("action"), input->getParameter("row"), input->getParameter("valueType"), input->text());
}

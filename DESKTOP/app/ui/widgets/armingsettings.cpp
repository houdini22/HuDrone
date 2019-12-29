#include "include.h"

ArmingDisarmingSettings::ArmingDisarmingSettings(QWidget * parent, TabsEditProfileGeneralTab * tab, Profile * profile, QString action) : QWidget(parent) {
    this->_tab = tab;
    this->_profile = profile;
    this->_action = action;
    this->render();
}

void ArmingDisarmingSettings::slotMyPushButton(MyPushButton * button) {
    this->addArmingDisarmingRow(button->getParameter("action"), button->getParameter("tab"), true, 0, 0);
}

void ArmingDisarmingSettings::slotMyTextEdited(MyLineEdit * input) {
    this->_profile->addArmingDisarmingValueForChannel(input->getParameter("channel"), input->getParameter("action"), input->getParameter("row"), input->getParameter("valueType"), input->text());
}

void ArmingDisarmingSettings::addArmingDisarmingRow(QString action, QString tabNum, bool addToConfig, int timeValue, int value) {
    this->_data[tabNum.toInt()]++;
    int row = this->_data[tabNum.toInt()];

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

    WizardConfigGeneralChannelTab * tab = _tab
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
        this->_profile->saveArmingDisarmingValueForChannel(tabNum.toInt() + 1, action, obj);
    }
}

void ArmingDisarmingSettings::slotMyPushButtonDelete(MyPushButton * button) {
    QString channel = button->getParameter("channel");
    QString action = button->getParameter("action");
    QString at = button->getParameter("at");

    this->_profile->removeArmingDisarmingPosition(channel, action, at);

    for (int j = 0; j < 8; j += 1) {
        WizardConfigGeneralChannelTab * tab = _tab
                ->getTab(j);

        for (int k = 1; k <= this->_data[j]; k += 1) {
            GridLayoutUtil::removeRow(tab->getLayout(), k, true);
        }

        this->_data[j] = 0;
    }

    this->render();
}

T_JSON ArmingDisarmingSettings::getValues(int channelNumber) {
    return this->_action.compare("arming") == 0 ?
                this->_profile->getArmingValuesForChannel(channelNumber) : this->_profile->getDisarmingValuesForChannel(channelNumber);
}

void ArmingDisarmingSettings::render() {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
         MyPushButton * addButton = MyPushButton::factory(this)
                 ->setText("Add send action")
                 ->setParameter("tab", QString::number(i))
                 ->setParameter("action", this->_action);

         connect(addButton, SIGNAL(myReleased(MyPushButton *)), this, SLOT(slotMyPushButton(MyPushButton *)));

         _tab
                 ->getTabWidget()
                 ->setTabText(i, this->_profile->getFunctionNameFromChannel(channelNumber));

         WizardConfigGeneralChannelTab * tab = _tab
                 ->getTab(i);

         tab->getLayout()->addWidget(addButton, 0, 0, 0, 6, Qt::AlignTop);

         this->_data[i] = 0;

         T_JSON values = this->getValues(channelNumber);

         if (values.size() > 0) {
             int j = 0;
             for (T_JSON::iterator it = values.begin(); it != values.end(); ++it) {
                 T_JSON value = it.value();
                 this->addArmingDisarmingRow(
                              this->_action,
                              QString::number(i),
                              false,
                              value["time"].get<int>(),
                              value["value"].get<int>()
                              );
                 j++;
             }
         }
    }
}

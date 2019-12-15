#include "include.h"

DialogEditProfile::DialogEditProfile(QWidget *parent, QString profileName) : QDialog(parent) {
    this->_profile = Profile::byName(profileName);

    setWindowTitle(QString("Edit profile: '" + profileName + "'"));
    setFixedSize(500, 309);

    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    _layout = new QHBoxLayout;

    _tabs = new TabsEditProfile();
    _layout->addWidget(_tabs->getTabWidget(), 1);
    _layout->addStretch(0);

    this->renderChannels();
    this->renderArming();
    this->renderDisarming();

    setLayout(_layout);
}

void DialogEditProfile::renderArming() {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
         MyPushButton * addButton = MyPushButton::factory(this)
                 ->setText("Add send action")
                 ->setParameter("tab", QString::number(i))
                 ->setParameter("action", "arming");

         connect(addButton, SIGNAL(myReleased(MyPushButton *)), this, SLOT(slotMyPushButton(MyPushButton *)));

         WizardConfigGeneralChannelTab * tab = _tabs
                 ->getTab(1)
                 ->getTab(i);

         tab->getLayout()->addWidget(addButton, 0, 0, 0, 6, Qt::AlignTop);

         this->_add_buttons[1][i] = 0;

         T_JSON armingValues = this->_profile->getArmingValuesForChannel(channelNumber);
         if (armingValues.size() > 0) {
             int j = 0;
             for (T_JSON::iterator it = armingValues.begin(); it != armingValues.end(); ++it) {
                 T_JSON value = it.value();
                 this->addArmingDisarmingRow(
                              "arming",
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

void DialogEditProfile::renderDisarming() {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        MyPushButton * addButton = MyPushButton::factory(this)
                ->setText("Add send action")
                ->setParameter("tab", QString::number(i))
                ->setParameter("action", "disarming");

        connect(addButton, SIGNAL(myReleased(MyPushButton *)), this, SLOT(slotMyPushButton(MyPushButton *)));

        WizardConfigGeneralChannelTab * tab = _tabs
                ->getTab(2)
                ->getTab(i);

        tab->getLayout()->addWidget(addButton, 0, 0, 0, 6, Qt::AlignTop);

        this->_add_buttons[2][i] = 0;

        T_JSON disarmingValues = this->_profile->getDisarmingValuesForChannel(channelNumber);
        if (disarmingValues.size() > 0) {
            int j = 0;
            for (T_JSON::iterator it = disarmingValues.begin(); it != disarmingValues.end(); ++it) {
                T_JSON value = it.value();
                this->addArmingDisarmingRow(
                             "disarming",
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

void DialogEditProfile::renderChannels() {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        this->_combos[channelNumber] = MyComboBox::factory({"---", "throttle", "pitch", "roll", "yaw", "other_1", "other_2", "other_3", "other_4"}, channelNumber);
        this->_combos[channelNumber]->setValue(this->_profile->getStringValueFromChannel(channelNumber, "function"));
        connect(this->_combos[channelNumber], SIGNAL(myTextChanged(QString, int)), this, SLOT(myComboBoxTextChanged(QString, int)));

        MyLineEdit * minInput = new MyLineEdit();
        MyLineEdit * middleInput = new MyLineEdit();
        MyLineEdit * maxInput = new MyLineEdit();
        MyLineEdit * defaultInput = new MyLineEdit();

        minInput->setID("channel" + QString::number(channelNumber) + "/min");
        middleInput->setID("channel" + QString::number(channelNumber) + "/middle");
        maxInput->setID("channel" + QString::number(channelNumber) + "/max");
        defaultInput->setID("channel" + QString::number(channelNumber) + "/default");

        minInput->setValidator(new QIntValidator(0, 2000));
        middleInput->setValidator(new QIntValidator(0, 2000));
        maxInput->setValidator(new QIntValidator(0, 2000));
        defaultInput->setValidator(new QIntValidator(0, 2000));

        connect(minInput, SIGNAL(myTextEdited(QString, QString)), this, SLOT(textEdited(QString, QString)));
        connect(middleInput, SIGNAL(myTextEdited(QString, QString)), this, SLOT(textEdited(QString, QString)));
        connect(maxInput, SIGNAL(myTextEdited(QString, QString)), this, SLOT(textEdited(QString, QString)));
        connect(defaultInput, SIGNAL(myTextEdited(QString, QString)), this, SLOT(textEdited(QString, QString)));

        this->_inputs[i]["min"] = minInput;
        this->_inputs[i]["middle"] = middleInput;
        this->_inputs[i]["max"] = maxInput;
        this->_inputs[i]["default"] = defaultInput;

        QLabel * functionLabel = new QLabel;
        QLabel * minLabel = new QLabel;
        QLabel * middleLabel = new QLabel;
        QLabel * maxLabel = new QLabel;
        QLabel * defaultLabel = new QLabel;

        functionLabel->setText("Function");
        minLabel->setText("Minimum sent value");
        middleLabel->setText("Middle sent value");
        maxLabel->setText("Maximum sent value");
        defaultLabel->setText("Initial sent value");

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(minLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(minInput);

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(middleLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(middleInput);

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(maxLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(maxInput);

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(defaultLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(defaultInput);

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(functionLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(this->_combos[channelNumber]);
    }
}

void DialogEditProfile::addArmingDisarmingRow(QString action, QString tabNum, bool addToConfig, int timeValue, int value) {
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

    WizardConfigGeneralChannelTab * tab = _tabs
            ->getTab(action.compare("arming") == 0 ? 1 : 2)
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

void DialogEditProfile::slotMyPushButton(MyPushButton * button) {
    this->addArmingDisarmingRow(button->getParameter("action"), button->getParameter("tab"), true, 0, 0);
}

int DialogEditProfile::getValueFromChannel(int channelNumber, T_String value) {
    return this->_profile->getValueFromChannel(channelNumber, value);
}

QString DialogEditProfile::getStringValueFromChannel(int channelNumber, T_String value) {
    return QString::number(this->_profile->getValueFromChannel(channelNumber, value));
}

void DialogEditProfile::setValueForChannel(QString channelNumber, QString valueName, QString value) {
    if (value.length() == 0) {
        if (valueName.compare("min") == 0) {
            value = "1100";
            this->_inputs[channelNumber.toInt()]["min"]->setText(value);
        } else if (valueName.compare("max") == 0) {
            value = "1900";
            this->_inputs[channelNumber.toInt()]["max"]->setText(value);
        } else if (valueName.compare("middle") == 0) {
            value = "1500";
            this->_inputs[channelNumber.toInt()]["middle"]->setText(value);
        } else if (valueName.compare("default") == 0) {
            value = "1500";
            this->_inputs[channelNumber.toInt()]["default"]->setText(value);
        }
    }

    this->_profile->saveValueForChannel(channelNumber, valueName, value);
}

void DialogEditProfile::setFunctionValueForChannel(int channelNumber, QString value) {
    this->_profile->saveValueForChannel(QString("channel").append(QString::number(channelNumber)), "function", value);
}

void DialogEditProfile::showEvent(QShowEvent *) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        MyLineEdit * minInput = this->_inputs[i]["min"];
        MyLineEdit * middleInput = this->_inputs[i]["middle"];
        MyLineEdit * maxInput = this->_inputs[i]["max"];
        MyLineEdit * defaultInput = this->_inputs[i]["default"];

        QString minValue = QString::number(this->getValueFromChannel(channelNumber, "min"));
        QString middleValue = QString::number(this->getValueFromChannel(channelNumber, "middle"));
        QString maxValue = QString::number(this->getValueFromChannel(channelNumber, "max"));
        QString defaultValue = QString::number(this->getValueFromChannel(channelNumber, "default"));
        QString functionValue = this->getStringValueFromChannel(channelNumber, "function");

        minInput->setText(minValue);
        middleInput->setText(middleValue);
        maxInput->setText(maxValue);
        defaultInput->setText(defaultValue);

        this->_combos[channelNumber]->setCurrentText(functionValue);
    }
}

void DialogEditProfile::textEdited(QString text, QString id) {
    QStringList split = id.split("/");
    this->setValueForChannel(split.at(0), split.at(1), text);
}

void DialogEditProfile::myComboBoxTextChanged(QString value, int _channelNumber) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        if (value.compare("---") != 0) {
            if (this->_combos[channelNumber]->currentText().compare(value) == 0 && _channelNumber != channelNumber) {
                this->_combos[channelNumber]->setCurrentText("---");
                this->setFunctionValueForChannel(channelNumber, "");
            } else if (channelNumber == _channelNumber) {
                this->setFunctionValueForChannel(channelNumber, value);
            }
        }
    }
}

void DialogEditProfile::slotMyPushButtonDelete(MyPushButton * button) {
    QString channel = button->getParameter("channel");
    QString action = button->getParameter("action");
    QString at = button->getParameter("at");

    this->_profile->removeArmingDisarmingPosition(channel, action, at);

    for (int i = 1; i <= 2; i += 1) {
        for (int j = 0; j < 8; j += 1) {
            WizardConfigGeneralChannelTab * tab = _tabs
                    ->getTab(i)
                    ->getTab(j);

            for (int k = 1; k <= this->_add_buttons[i][j]; k += 1) {
                GridLayoutUtil::removeRow(tab->getLayout(), k, true);
            }

            this->_add_buttons[i][j] = 0;
        }
    }

    this->renderArming();
    this->renderDisarming();
}

void DialogEditProfile::slotMyTextEdited(MyLineEdit * input) {
    this->_profile->addArmingDisarmingValueForChannel(input->getParameter("channel"), input->getParameter("action"), input->getParameter("row"), input->getParameter("valueType"), input->text());
}

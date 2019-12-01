#include "include.h"

DialogEditProfile::DialogEditProfile(QWidget *parent, QString profileName) : QDialog(parent) {
    this->_profile_name = profileName;

    setWindowTitle(QString("Edit profile: '" + profileName + "'"));
    setFixedSize(500, 309);

    this->setWindowFlag(Qt::WindowSystemMenuHint, false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    T_JSON profiles = Config::getInstance().getObject({"profiles"});
    for (T_JSON::iterator it = profiles.begin(); it != profiles.end(); ++it) {
        T_JSON profile = it.value();
        T_String _profileName = profile["name"].get<T_String>();
        if (_profileName.compare(profileName.toStdString()) == 0) {
            this->_profile_configuration = profile;
            break;
        }
    }

    _layout = new QHBoxLayout;

    _tabs = new TabsEditProfile();
    _layout->addWidget(_tabs->getTabWidget(), 1);
    _layout->addStretch(0);

    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        this->_combos[channelNumber] = MyComboBox::factory({"---", "throttle", "pitch", "roll", "yaw", "other_1", "other_2", "other_3", "other_4"}, channelNumber);
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

    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
         MyPushButton * addButton = MyPushButton::factory(this)
                 ->setText("Add send action")
                 ->setParameter("tab", QString::number(i))
                 ->setParameter("action", "arming");

         connect(addButton, SIGNAL(myReleased(MyPushButton *)), this, SLOT(slotMyPushButton(MyPushButton *)));

         WizardConfigGeneralChannelTab * tab = _tabs
                 ->getTab(1)
                 ->getTab(i);

         tab->getLayout()->addWidget(addButton, 0, 0);

         this->_add_buttons[1][i] = 0;
    }

    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        MyPushButton * addButton = MyPushButton::factory(this)
                ->setText("Add send action")
                ->setParameter("tab", QString::number(i))
                ->setParameter("action", "disarming");

        connect(addButton, SIGNAL(myReleased(MyPushButton *)), this, SLOT(slotMyPushButton(MyPushButton *)));

        WizardConfigGeneralChannelTab * tab = _tabs
                ->getTab(2)
                ->getTab(i);

        tab->getLayout()->addWidget(addButton, 0, 0);

        this->_add_buttons[2][i] = 0;
    }

    setLayout(_layout);
}

void DialogEditProfile::slotMyPushButton(MyPushButton * button) {
    this->_add_buttons[button->getParameter("action").compare("arming") == 0 ? 1 : 2][button->getParameter("tab").toInt()]++;
    int row = this->_add_buttons[button->getParameter("action").compare("arming") == 0 ? 1 : 2][button->getParameter("tab").toInt()];

    auto inputLength = new MyLineEdit(this);
    inputLength->setValidator(new QIntValidator(1, 10000, this));

    auto inputValue = new MyLineEdit(this);
    inputValue->setValidator(new QIntValidator(0, 2000, this));

    auto deleteButton = MyPushButton::factory(this)
            ->setParameter("tab", button->getParameter("tab"))
            ->setParameter("action", button->getParameter("button"))
            ->setParameter("row", QString::number(this->_add_buttons[button->getParameter("action").compare("arming") == 0 ? 1 : 2][button->getParameter("tab").toInt()]))
            ->setText("Delete");

    WizardConfigGeneralChannelTab * tab = _tabs
            ->getTab(button->getParameter("action").compare("arming") == 0 ? 1 : 2)
            ->getTab(button->getParameter("tab").toInt());

    auto labelLength = new QLabel(this);
    labelLength->setText("Time: (0 - 10000)");

    auto labelValue = new QLabel(this);
    labelValue->setText("Value: (0 - 2000)");

    tab->getLayout()->addWidget(labelLength, row, 0);
    tab->getLayout()->addWidget(inputLength, row, 1);
    tab->getLayout()->addWidget(labelValue, row, 2);
    tab->getLayout()->addWidget(inputValue, row, 3);
    tab->getLayout()->addWidget(deleteButton, row, 4);

    setLayout(_layout);
}

int DialogEditProfile::getValueFromChannel(int channelNumber, T_String value) {
    T_String ret = this->_profile_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()][value].get<T_String>();
    return QString(ret.c_str()).toInt();
}

QString DialogEditProfile::getStringValueFromChannel(int channelNumber, T_String value) {
    T_String ret = this->_profile_configuration["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()][value].get<T_String>();
    return QString(ret.c_str());
}

void DialogEditProfile::setValueForChannel(QString channelNumber, QString valueName, QString value) {
    this->_profile_configuration["radio"][channelNumber.toStdString()][valueName.toStdString()] = value.toStdString();

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

    T_JSON data = Config::getInstance().getData();
    unsigned long long i = 0;
    for (T_JSON::iterator it = data["profiles"].begin(); it != data["profiles"].end(); ++it) {
        T_JSON profile = it.value();
        T_String _profileName = profile["name"].get<T_String>();
        if (_profileName.compare(this->_profile_name.toStdString()) == 0) {
            data["profiles"].at(i)["radio"][channelNumber.toStdString()][valueName.toStdString()] = value.toStdString();
            break;
        }
        i += 1;
    }

    Config::getInstance().setData(data)->save();
}

void DialogEditProfile::setFunctionValueForChannel(int channelNumber, QString value) {
    T_String _channel = "channel" + QString::number(channelNumber).toStdString();

    this->_profile_configuration["radio"][_channel]["function"] = value.toStdString();

    T_JSON data = Config::getInstance().getData();
    unsigned long long i = 0;
    for (T_JSON::iterator it = data["profiles"].begin(); it != data["profiles"].end(); ++it) {
        T_JSON profile = it.value();
        T_String _profileName = profile["name"].get<T_String>();
        if (_profileName.compare(this->_profile_name.toStdString()) == 0) {
            data["profiles"].at(i)["radio"][_channel]["function"] = value.toStdString();
            break;
        }
        i += 1;
    }

    Config::getInstance().setData(data)->save();
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

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
    this->renderOther();

    setLayout(_layout);
}

void DialogEditProfile::renderArming() {
    if (this->_armingSettings != nullptr) {
        delete this->_armingSettings;
    }
    this->_armingSettings = new ArmingDisarmingSettings(this, this->_tabs->getTab(1), this->_profile, "arming");
}

void DialogEditProfile::renderDisarming() {
    if (this->_disarmingSettings != nullptr) {
        delete this->_disarmingSettings;
    }
    this->_disarmingSettings = new ArmingDisarmingSettings(this, this->_tabs->getTab(2), this->_profile, "disarming");
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

        this->_inputs[i]["min"] = minInput;
        this->_inputs[i]["middle"] = middleInput;
        this->_inputs[i]["max"] = maxInput;

        QLabel * functionLabel = new QLabel;
        QLabel * minLabel = new QLabel;
        QLabel * middleLabel = new QLabel;
        QLabel * maxLabel = new QLabel;

        functionLabel->setText("Function");
        minLabel->setText("Minimum sent value");
        middleLabel->setText("Middle sent value");
        maxLabel->setText("Maximum sent value");

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(minLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(minInput);

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(middleLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(middleInput);

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(maxLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(maxInput);

        _tabs->getTab(0)->getTab(i)->layout()->addWidget(functionLabel);
        _tabs->getTab(0)->getTab(i)->layout()->addWidget(this->_combos[channelNumber]);
    }
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

        QString minValue = QString::number(this->getValueFromChannel(channelNumber, "min"));
        QString middleValue = QString::number(this->getValueFromChannel(channelNumber, "middle"));
        QString maxValue = QString::number(this->getValueFromChannel(channelNumber, "max"));
        QString functionValue = this->getStringValueFromChannel(channelNumber, "function");

        minInput->setText(minValue);
        middleInput->setText(middleValue);
        maxInput->setText(maxValue);

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

void DialogEditProfile::renderOther() {
    _group_box_throttle_steps = new QGroupBox();
    _group_box_throttle_steps->setTitle("Number of Throttle steps");

    _input_throttle_steps = new MyLineEdit();
    _input_throttle_steps->setValidator(new QIntValidator(0, 250));
    _input_throttle_steps->setText(QString::number(this->_profile->getThrottleSteps()));
    _input_throttle_steps->setID("throttleSteps");

    connect(_input_throttle_steps,
            SIGNAL(myTextEdited(QString, QString)),
            this,
            SLOT(slotThrottleStepsEdited(QString, QString)));

    QVBoxLayout * _group_box_layout = new QVBoxLayout();
    _group_box_layout->addStretch(0);
    _group_box_throttle_steps->setLayout(_group_box_layout);
    _group_box_throttle_steps->layout()->addWidget(_input_throttle_steps);

    _label_throttle_label = new QLabel();
    _label_throttle_label->setText("Throttle radio value:");

    _label_throttle_value = new QLabel();
    _label_throttle_value->setStyleSheet("QLabel { font-size: 20px; }");

    TabsEditProfileOtherTab * tab = (TabsEditProfileOtherTab *) _tabs
            ->getTabWidget()
            ->widget(3);

    tab->getLayout()->addWidget(_group_box_throttle_steps);
    tab->getLayout()->addWidget(_label_throttle_label);
    tab->getLayout()->addWidget(_label_throttle_value);
    tab->getLayout()->addStretch(0);

    this->slotThrottleStepsEdited(QString::number(this->_profile->getThrottleSteps()), "");
}

int DialogEditProfile::slotThrottleStepsEdited(const QString & text, QString) {
    if (text.toInt() == 0 || text.length() == 0) return 0;

    this->_profile->setThrottleSteps(text.toInt());

    int throttleRange = this->_profile->getThrottleRange();
    int result = throttleRange / text.toInt();
    _label_throttle_value->setText(QString::number(result));
}

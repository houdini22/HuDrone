#include "include.h"

WizardAddProfilePage4::WizardAddProfilePage4(Config * configuration, Receivers * receivers) : QWizardPage(nullptr) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Verify or correct values for radio channels.");

    _layout = new QHBoxLayout;

    _tabs = new WizardConfigChannelTabs();
    _layout->addWidget(_tabs->getTabWidget(), 1);
    _layout->addStretch(0);

    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        this->_combos[channelNumber] = MyComboBox::factory({"---", "throttle", "pitch", "roll", "yaw", "other_1", "other_2", "other_3", "other_4"}, channelNumber);
        connect(this->_combos[channelNumber], SIGNAL(myTextChanged(QString, int)), this, SLOT(myComboBoxTextChanged(QString, int)));

        MyLineEdit * minInput = new MyLineEdit();
        MyLineEdit * middleInput = new MyLineEdit();
        MyLineEdit * maxInput = new MyLineEdit();

        minInput->setID("channel" + QString::number(channelNumber) + "/min");
        middleInput->setID("channel" + QString::number(channelNumber) + "/middle");
        maxInput->setID("channel" + QString::number(channelNumber) + "/max");

        minInput->setValidator(new QIntValidator(0, 2000));
        middleInput->setValidator(new QIntValidator(0, 2000));
        maxInput->setValidator(new QIntValidator(0, 2000));

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

        _tabs->getTab(i)->layout()->addWidget(minLabel);
        _tabs->getTab(i)->layout()->addWidget(minInput);

        _tabs->getTab(i)->layout()->addWidget(middleLabel);
        _tabs->getTab(i)->layout()->addWidget(middleInput);

        _tabs->getTab(i)->layout()->addWidget(maxLabel);
        _tabs->getTab(i)->layout()->addWidget(maxInput);

        _tabs->getTab(i)->layout()->addWidget(functionLabel);
        _tabs->getTab(i)->layout()->addWidget(this->_combos[channelNumber]);
    }

    setLayout(_layout);
}

int WizardAddProfilePage4::getValueFromChannel(int channelNumber, T_String value) {
    T_String receiverName = this->_configuration->getString({"receiver"});
    return this->_receivers->getValueFromChannel(receiverName, channelNumber, value);
}

void WizardAddProfilePage4::showEvent(QShowEvent *) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        MyLineEdit * minInput = this->_inputs[i]["min"];
        MyLineEdit * middleInput = this->_inputs[i]["middle"];
        MyLineEdit * maxInput = this->_inputs[i]["max"];

        QString minValue = QString::number(this->getValueFromChannel(channelNumber, "min"));
        QString middleValue = QString::number(this->getValueFromChannel(channelNumber, "middle"));
        QString maxValue = QString::number(this->getValueFromChannel(channelNumber, "max"));

        minInput->setText(minValue);
        middleInput->setText(middleValue);
        maxInput->setText(maxValue);

        this->_configuration->modify("add", "/radio/" + minInput->getID(), minValue);
        this->_configuration->modify("add", "/radio/" + middleInput->getID(), middleValue);
        this->_configuration->modify("add", "/radio/" + maxInput->getID(), maxValue);
    }

    this->validate();
}

void WizardAddProfilePage4::textEdited(QString text, QString id) {
    QStringList split = id.split("/");
    this->_configuration->modify("replace", "/radio/" + id, text);

    this->validate();
}

void WizardAddProfilePage4::myComboBoxTextChanged(QString value, int _channelNumber) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        if (value.compare("---") != 0) {
            if (this->_combos[channelNumber]->currentText().compare(value) == 0 && _channelNumber != channelNumber) {
                this->_combos[channelNumber]->setCurrentText("---");
                this->_configuration->modify("add", "/radio/channel" + QString::number(channelNumber) + "/function", "---");
            } else if (channelNumber == _channelNumber) {
                this->_configuration->modify("add", "/radio/channel" + QString::number(channelNumber) + "/function", value);
            }
        }
    }

    this->validate();
}

void WizardAddProfilePage4::validate() {
    bool enabled = true;
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        if (this->_configuration->getData()["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["function"].get<T_String>().length() == 0) {
            enabled = false;
            break;
        }
        if (this->_configuration->getData()["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["min"].get<T_String>().length() == 0) {
            enabled = false;
            break;
        }
        if (this->_configuration->getData()["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["max"].get<T_String>().length() == 0) {
            enabled = false;
            break;
        }
        if (this->_configuration->getData()["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["middle"].get<T_String>().length() == 0) {
            enabled = false;
            break;
        }
    }
    this->wizard()->button(QWizard::NextButton)->setEnabled(enabled);
}

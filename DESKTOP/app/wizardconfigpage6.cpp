#include "include.h"

WizardConfigPage6::WizardConfigPage6(Config * configuration, Receivers * receivers) : QWizardPage(0) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Verify or correct values for radio channels.");

    _layout = new QHBoxLayout;

    _tabs = new WizardConfigChannelTabs();
    _layout->addWidget(_tabs->getTabWidget(), 1);
    _layout->addStretch(0);

    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
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

        QLabel * minLabel = new QLabel;
        QLabel * middleLabel = new QLabel;
        QLabel * maxLabel = new QLabel;
        QLabel * defaultLabel = new QLabel;

        minLabel->setText("Minimum sent value");
        middleLabel->setText("Middle sent value");
        maxLabel->setText("Maximum sent value");
        defaultLabel->setText("Initial sent value");

        _tabs->getTab(i)->layout()->addWidget(minLabel);
        _tabs->getTab(i)->layout()->addWidget(minInput);

        _tabs->getTab(i)->layout()->addWidget(middleLabel);
        _tabs->getTab(i)->layout()->addWidget(middleInput);

        _tabs->getTab(i)->layout()->addWidget(maxLabel);
        _tabs->getTab(i)->layout()->addWidget(maxInput);

        _tabs->getTab(i)->layout()->addWidget(defaultLabel);
        _tabs->getTab(i)->layout()->addWidget(defaultInput);
    }

    setLayout(_layout);
}

int WizardConfigPage6::getValueFromChannel(int channelNumber, T_String value) {
    T_String receiverName = this->_configuration->getString({"receiver"});
    return this->_receivers->getValueFromChannel(receiverName, channelNumber, value);
}

void WizardConfigPage6::showEvent(QShowEvent *) {
    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        MyLineEdit * minInput = this->_inputs[i]["min"];
        MyLineEdit * middleInput = this->_inputs[i]["middle"];
        MyLineEdit * maxInput = this->_inputs[i]["max"];
        MyLineEdit * defaultInput = this->_inputs[i]["default"];

        QString minValue = QString::number(this->getValueFromChannel(channelNumber, "min"));
        QString middleValue = QString::number(this->getValueFromChannel(channelNumber, "middle"));
        QString maxValue = QString::number(this->getValueFromChannel(channelNumber, "max"));
        QString defaultValue = QString::number(this->getValueFromChannel(channelNumber, "default"));

        minInput->setText(minValue);
        middleInput->setText(middleValue);
        maxInput->setText(maxValue);
        defaultInput->setText(defaultValue);

        this->_configuration->modify("add", "/radio/" + minInput->getID(), minValue);
        this->_configuration->modify("add", "/radio/" + middleInput->getID(), middleValue);
        this->_configuration->modify("add", "/radio/" + maxInput->getID(), maxValue);
        this->_configuration->modify("add", "/radio/" + defaultInput->getID(), defaultValue);
    }
}

void WizardConfigPage6::textEdited(QString text, QString id) {
    QStringList split = id.split("/");
    this->_configuration->modify("replace", "/radio/" + id, text);
}
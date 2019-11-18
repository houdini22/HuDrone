#include "include.h"

WizardAddProfilePage7::WizardAddProfilePage7(Config * configuration, Receivers * receivers) : QWizardPage(nullptr) {
    this->_configuration = configuration;
    this->_receivers = receivers;

    setTitle("Other settings.");

    _layout = new QVBoxLayout();

    _group_box_throttle_steps = new QGroupBox();
    _group_box_throttle_steps->setTitle("Number of Trottle steps");

    _input_throttle_steps = new MyLineEdit();
    _input_throttle_steps->setValidator(new QIntValidator(0, 250));
    _input_throttle_steps->setText("10");
    _input_throttle_steps->setID("throttleSteps");

    connect(_input_throttle_steps,
            SIGNAL(myTextEdited(QString, QString)),
            this,
            SLOT(myTextEdited(QString, QString)));

    QVBoxLayout * _group_box_layout = new QVBoxLayout();
    _group_box_layout->addStretch(0);
    _group_box_throttle_steps->setLayout(_group_box_layout);
    _group_box_throttle_steps->layout()->addWidget(_input_throttle_steps);

    _label_throttle_label = new QLabel();
    _label_throttle_label->setText("Throttle value:");

    _label_throttle_value = new QLabel();
    _label_throttle_value->setStyleSheet("QLabel { font-size: 20px; }");

    _layout->addWidget(_group_box_throttle_steps);
    _layout->addWidget(_label_throttle_label);
    _layout->addWidget(_label_throttle_value);
    _layout->addStretch(0);

    setLayout(_layout);
}

void WizardAddProfilePage7::showEvent(QShowEvent *) {
    _label_throttle_value->setText(QString::number(this->myTextEdited("10", "")));
}

int WizardAddProfilePage7::myTextEdited(QString text, QString) {
    T_JSON data = this->_configuration->getData();
    int result = 0;

    if (text.length() == 0) {
        return result;
    }

    for (int i = 0, channelNumber = 1; i < 8; i += 1, channelNumber += 1) {
        try {
            T_String _function = data["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["function"].get<T_String>();
            if (_function.compare("throttle") == 0) {
                T_String min = data["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["min"].get<T_String>();
                T_String max = data["radio"][(QString("channel") + QString::number(channelNumber)).toStdString()]["max"].get<T_String>();

                if (text.toInt() != 0) {
                    result = (QString(max.c_str()).toInt() - QString(min.c_str()).toInt()) / text.toInt();
                    _label_throttle_value->setText(QString::number(result));

                    data["radio"]["throttleSteps"] = text.toInt();
                    this->_configuration->setData(data);
                }
                break;
            }
        } catch(std::domain_error) {
            qDebug() << "Key not exists.";
        }
    }

    return result;
}

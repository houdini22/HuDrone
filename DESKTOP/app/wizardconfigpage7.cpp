#include "include.h"

WizardConfigPage7::WizardConfigPage7(QWidget *parent) : QWizardPage(parent) {
    setTitle("Verify or correct ARMING engine values.");

    _layout = new QHBoxLayout;

    for (int i = 1, row = 0; i <= 8; i += 2, row += 1) {
        QGridLayout * layout2 = new QGridLayout;

        for (int j = i, k = 0; j <= i + 1; j += 1, k += 1) {
            QGridLayout * layout3 = new QGridLayout;

            QLabel * label = new QLabel;
            label->setText("Channel " + QString::number((i + k)));
            label->setStyleSheet("font-weight: bold");

            QLineEdit * value = new QLineEdit(QString("armingValueChannel" + QString(i + k)));
            value->setText(QString::number((int) 1100));
            value->setValidator(new QIntValidator(0, 2000, _layout));

            QLineEdit * time = new QLineEdit(QString("armingValueTimeChannel" + QString(i + k)));
            time->setText(QString::number((int) 1000));
            time->setValidator(new QIntValidator(0, 5000, _layout));

            QLabel * valueLabel = new QLabel;
            valueLabel->setText("value");

            QLabel * timeLabel = new QLabel;
            timeLabel->setText("time (ms)");

            layout3->addWidget(label, 0, 0, Qt::AlignCenter);
            layout3->addWidget(valueLabel, 1, 0);
            layout3->addWidget(value, 1, 1);
            layout3->addWidget(timeLabel, 2, 0);
            layout3->addWidget(time, 2, 1);

            layout2->addLayout(layout3, k, row);
        }

        _layout->addLayout(layout2);
    }

    setLayout(_layout);
}

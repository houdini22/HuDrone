#include "include.h"

WizardConfigPage6::WizardConfigPage6(QWidget *parent) : QWizardPage(parent) {
    setTitle("Verify or correct 'min' and 'max' values for radio channels.");

    _layout = new QHBoxLayout;

    for (int i = 1, row = 0; i <= 8; i += 2, row += 1) {
        QGridLayout * layout2 = new QGridLayout;

        for (int j = i, k = 0; j <= i + 1; j += 1, k += 1) {
            QGridLayout * layout3 = new QGridLayout;

            QLabel * label = new QLabel;
            label->setText("Channel " + QString::number((i + k)));
            label->setStyleSheet("font-weight: bold");

            QLineEdit * min = new QLineEdit(QString("channel" + QString(i + k) + "min"));
            min->setText(QString::number((int) 1100));

            QLineEdit * middle = new QLineEdit(QString("channel" + QString(i + k) + "middle"));
            middle->setText(QString::number((int) 1500));

            QLineEdit * max = new QLineEdit(QString("channel" + QString(i + k) + "max"));
            max->setText(QString::number((int) 1900));

            min->setValidator(new QIntValidator(0, 2000, _layout));
            middle->setValidator(new QIntValidator(0, 2000, _layout));
            max->setValidator(new QIntValidator(0, 2000, _layout));

            QLabel * minLabel = new QLabel;
            minLabel->setText("min");

            QLabel * middleLabel = new QLabel;
            middleLabel->setText("middle");

            QLabel * maxLabel = new QLabel;
            maxLabel->setText("max");


            layout3->addWidget(label, 0, 0, Qt::AlignCenter);

            layout3->addWidget(minLabel, 1, 0);
            layout3->addWidget(min, 1, 1);

            layout3->addWidget(middleLabel, 2, 0);
            layout3->addWidget(middle, 2, 1);

            layout3->addWidget(maxLabel, 3, 0);
            layout3->addWidget(max, 3, 1);

            layout2->addLayout(layout3, k, row);
        }

        _layout->addLayout(layout2);
    }

    setLayout(_layout);
}

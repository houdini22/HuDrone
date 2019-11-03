#ifndef DIALOGTHROTTLEMODESETTINGS_H
#define DIALOGTHROTTLEMODESETTINGS_H

#include <QDialog>

namespace Ui {
class DialogThrottleModeSettings;
}

class DialogThrottleModeSettings : public QDialog
{
    Q_OBJECT
public:
    explicit DialogThrottleModeSettings(QWidget *parent = 0);
    ~DialogThrottleModeSettings();
private:
    Ui::DialogThrottleModeSettings *ui;
private slots:
    void signalAccepted();
};

#endif // DIALOGTHROTTLEMODESETTINGS_H

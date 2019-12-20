#pragma once

#include <QThread>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QMap>
#include <QHash>
#include <QLineEdit>
#include <QEvent>
#include <QAbstractButton>
#include <QDesktopWidget>
#include <QRect>
#include <QGroupBox>
#include <QMouseEvent>
#include <QRadioButton>
#include <QWizard>
#include <QWizardPage>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QApplication>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QSerialPort>
#include <QComboBox>
#include <QGamepadManager>
#include <QGamepad>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <chrono>
#include <future>
#include <math.h>
#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <stdio.h>
#include <set>

#ifdef WIN32
#include <windows.h>
#include <fileapi.h>
#include <winbase.h>
#endif

#ifndef WIN32
#include <sys/stat.h>
#include "experimental/filesystem"
#endif

#include "json.hpp"
#include "utils.h"

#include "mymenuaction.h"
#include "mylineedit.h"
#include "mycombobox.h"
#include "mypushbutton.h"

typedef bool T_Bool;
typedef std::string T_String;
typedef nlohmann::json T_JSON;

#include "gridlayoututils.h"
#include "myserialport.h"
#include "timerarduinoabstract.h"
#include "timerthread.h"
#include "timersarduino.h"
#include "profile.h"
#include "threadgamepad.h"
#include "buttons.h"
#include "dronemodes.h"
#include "steeringregistry.h"
#include "steering.h"
#include "sendinginterface.h"
#include "sendingregistry.h"
#include "sendingarduino.h"
#include "threadgamepadupdate.h"
#include "steering.h"
#include "ui/dialogeditprofile.h"
#include "serialportutilities.h"
#include "threadboxconnect.h"
#include "filesystem.h"
#include "config.h"
#include "receivers.h"
#include "ui/dialogfly.h"
#include "drone.h"
#include "tabseditprofilegeneraltab.h"
#include "tabseditprofile.h"
#include "ui/wizardconfiggeneralchanneltab.h"
#include "ui/wizardconfigchanneltabs.h"
#include "ui/wizardaddprofilepage1.h"
#include "ui/wizardaddprofilepage2.h"
#include "ui/wizardaddprofilepage3.h"
#include "ui/wizardaddprofilepage4.h"
#include "ui/wizardaddprofilepage5.h"
#include "ui/wizardaddprofilepage6.h"
#include "ui/wizardaddprofilepage7.h"
#include "ui/wizardaddprofilepage8.h"
#include "ui/wizardaddprofile.h"
#include "ui/wizarduploadpage1.h"
#include "ui/wizarduploadpage2.h"
#include "ui/wizarduploadpage3.h"
#include "ui/wizarduploadpage4.h"
#include "ui/wizardupload.h"

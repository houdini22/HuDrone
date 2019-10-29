#ifndef INCLUDE_H
#define INCLUDE_H

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
#include <windows.h>
#include <fileapi.h>
#include <stdio.h>
#include <set>
#include <winbase.h>

#include "json.hpp"

typedef bool T_Bool;
typedef std::string T_String;
typedef nlohmann::json T_JSON;

#include "mymenuaction.h"
#include "mylineedit.h"

#include "dialogeditprofile.h"
#include "serialportutilities.h"
#include "SerialPort.h"
#include "threadboxconnect.h"
#include "filesystem.h"
#include "config.h"
#include "receivers.h"
#include "drone.h"
#include "tabseditprofilegeneraltab.h"
#include "tabseditprofile.h"
#include "wizardconfiggeneralchanneltab.h"
#include "wizardconfigchanneltabs.h"
#include "wizardaddprofilepage1.h"
#include "wizardaddprofilepage2.h"
#include "wizardaddprofilepage3.h"
#include "wizardaddprofilepage4.h"
#include "wizardaddprofilepage5.h"
#include "wizardaddprofilepage6.h"
#include "wizardaddprofilepage7.h"
#include "wizardaddprofile.h"
#include "wizarduploadpage1.h"
#include "wizarduploadpage2.h"
#include "wizarduploadpage3.h"
#include "wizarduploadpage4.h"
#include "wizardupload.h"

#endif // INCLUDE_H

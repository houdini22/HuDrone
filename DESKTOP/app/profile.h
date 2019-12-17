#pragma once
#include "include.h"

class Profile {
public:
    Profile(T_JSON, QString);
    static Profile * byName(QString);
    int getLeftX(double);
    int getLeftY(double);
    int getMinLeftY();
    int getMaxLeftY();
    int getRightX(double);
    int getRightY(double);
    int getThrottleSteps();
    QString getChannelNumberOf(QString);
    T_JSON getArmingValuesForChannel(int);
    T_JSON getDisarmingValuesForChannel(int);
    void saveArmingDisarmingValueForChannel(int, QString, T_JSON);
    int getValueFromChannel(int, T_String);
    QString getStringValueFromChannel(int, T_String);
    void save();
    void saveValueForChannel(QString, QString, QString);
    void removeArmingDisarmingPosition(QString, QString, QString);
    void addArmingDisarmingValueForChannel(QString, QString, QString, QString, QString);
    int getArmingSeqenceValueInTime(QString, int);
    QVector<QString> getFunctions();
private:
    T_JSON _configuration;
    QMap<QString, QString> getFunction(QString);
    int getValueToSend(QMap<QString, QString>, double, bool, bool fromMin = false);
    QMap<QString, QString> _channelNumbers;
    QMap<QString, QMap<QString, QString>> _channelFunctions;
    QMap<QString, QVector<QVector<int>>> _armingValues;
    int _throttleSteps = 0;
    QString _name = "";
    void loadArmingValues();
};

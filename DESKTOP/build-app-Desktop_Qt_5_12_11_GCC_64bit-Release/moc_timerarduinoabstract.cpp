/****************************************************************************
** Meta object code from reading C++ file 'timerarduinoabstract.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../app/timerarduinoabstract.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timerarduinoabstract.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TimerArduinoAbstract_t {
    QByteArrayData data[7];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimerArduinoAbstract_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimerArduinoAbstract_t qt_meta_stringdata_TimerArduinoAbstract = {
    {
QT_MOC_LITERAL(0, 0, 20), // "TimerArduinoAbstract"
QT_MOC_LITERAL(1, 21, 7), // "execute"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 23), // "slotSendingsDataChanged"
QT_MOC_LITERAL(4, 54, 26), // "QHash<QString,SendingData>"
QT_MOC_LITERAL(5, 81, 24), // "slotSteeringsDataChanged"
QT_MOC_LITERAL(6, 106, 21) // "QVector<SteeringData>"

    },
    "TimerArduinoAbstract\0execute\0\0"
    "slotSendingsDataChanged\0"
    "QHash<QString,SendingData>\0"
    "slotSteeringsDataChanged\0QVector<SteeringData>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimerArduinoAbstract[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    1,   30,    2, 0x0a /* Public */,
       5,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void TimerArduinoAbstract::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimerArduinoAbstract *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->execute(); break;
        case 1: _t->slotSendingsDataChanged((*reinterpret_cast< QHash<QString,SendingData>(*)>(_a[1]))); break;
        case 2: _t->slotSteeringsDataChanged((*reinterpret_cast< QVector<SteeringData>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TimerArduinoAbstract::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TimerArduinoAbstract.data,
    qt_meta_data_TimerArduinoAbstract,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TimerArduinoAbstract::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimerArduinoAbstract::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimerArduinoAbstract.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TimerArduinoAbstract::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_TimerArduinoPing_t {
    QByteArrayData data[3];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimerArduinoPing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimerArduinoPing_t qt_meta_stringdata_TimerArduinoPing = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TimerArduinoPing"
QT_MOC_LITERAL(1, 17, 7), // "execute"
QT_MOC_LITERAL(2, 25, 0) // ""

    },
    "TimerArduinoPing\0execute\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimerArduinoPing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TimerArduinoPing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimerArduinoPing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->execute(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TimerArduinoPing::staticMetaObject = { {
    QMetaObject::SuperData::link<TimerArduinoAbstract::staticMetaObject>(),
    qt_meta_stringdata_TimerArduinoPing.data,
    qt_meta_data_TimerArduinoPing,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TimerArduinoPing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimerArduinoPing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimerArduinoPing.stringdata0))
        return static_cast<void*>(this);
    return TimerArduinoAbstract::qt_metacast(_clname);
}

int TimerArduinoPing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TimerArduinoAbstract::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_TimerArduinoSend_t {
    QByteArrayData data[3];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimerArduinoSend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimerArduinoSend_t qt_meta_stringdata_TimerArduinoSend = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TimerArduinoSend"
QT_MOC_LITERAL(1, 17, 7), // "execute"
QT_MOC_LITERAL(2, 25, 0) // ""

    },
    "TimerArduinoSend\0execute\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimerArduinoSend[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TimerArduinoSend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimerArduinoSend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->execute(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TimerArduinoSend::staticMetaObject = { {
    QMetaObject::SuperData::link<TimerArduinoAbstract::staticMetaObject>(),
    qt_meta_stringdata_TimerArduinoSend.data,
    qt_meta_data_TimerArduinoSend,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TimerArduinoSend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimerArduinoSend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimerArduinoSend.stringdata0))
        return static_cast<void*>(this);
    return TimerArduinoAbstract::qt_metacast(_clname);
}

int TimerArduinoSend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TimerArduinoAbstract::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

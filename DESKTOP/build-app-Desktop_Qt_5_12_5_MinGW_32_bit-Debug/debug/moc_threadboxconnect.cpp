/****************************************************************************
** Meta object code from reading C++ file 'threadboxconnect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../app/threadboxconnect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'threadboxconnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadBoxConnect_t {
    QByteArrayData data[8];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadBoxConnect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadBoxConnect_t qt_meta_stringdata_ThreadBoxConnect = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ThreadBoxConnect"
QT_MOC_LITERAL(1, 17, 16), // "arduinoConnected"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "QSerialPort*"
QT_MOC_LITERAL(4, 48, 24), // "signalSendingDataChanged"
QT_MOC_LITERAL(5, 73, 12), // "SendingData*"
QT_MOC_LITERAL(6, 86, 9), // "terminate"
QT_MOC_LITERAL(7, 96, 22) // "slotSendingDataChanged"

    },
    "ThreadBoxConnect\0arduinoConnected\0\0"
    "QSerialPort*\0signalSendingDataChanged\0"
    "SendingData*\0terminate\0slotSendingDataChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadBoxConnect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x0a /* Public */,
       7,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void ThreadBoxConnect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadBoxConnect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->arduinoConnected((*reinterpret_cast< QSerialPort*(*)>(_a[1]))); break;
        case 1: _t->signalSendingDataChanged((*reinterpret_cast< SendingData*(*)>(_a[1]))); break;
        case 2: _t->terminate(); break;
        case 3: _t->slotSendingDataChanged((*reinterpret_cast< SendingData*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSerialPort* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThreadBoxConnect::*)(QSerialPort * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadBoxConnect::arduinoConnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ThreadBoxConnect::*)(SendingData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadBoxConnect::signalSendingDataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadBoxConnect::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_ThreadBoxConnect.data,
    qt_meta_data_ThreadBoxConnect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadBoxConnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadBoxConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadBoxConnect.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ThreadBoxConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ThreadBoxConnect::arduinoConnected(QSerialPort * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreadBoxConnect::signalSendingDataChanged(SendingData * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
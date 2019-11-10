/****************************************************************************
** Meta object code from reading C++ file 'steering.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../app/steering.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'steering.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SteeringInterface_t {
    QByteArrayData data[4];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SteeringInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SteeringInterface_t qt_meta_stringdata_SteeringInterface = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SteeringInterface"
QT_MOC_LITERAL(1, 18, 25), // "signalSteeringDataChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 13) // "SteeringData*"

    },
    "SteeringInterface\0signalSteeringDataChanged\0"
    "\0SteeringData*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SteeringInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void SteeringInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SteeringInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSteeringDataChanged((*reinterpret_cast< SteeringData*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SteeringInterface::*)(SteeringData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SteeringInterface::signalSteeringDataChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SteeringInterface::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SteeringInterface.data,
    qt_meta_data_SteeringInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SteeringInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SteeringInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SteeringInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SteeringInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void SteeringInterface::signalSteeringDataChanged(SteeringData * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_SteeringGamepad0_t {
    QByteArrayData data[5];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SteeringGamepad0_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SteeringGamepad0_t qt_meta_stringdata_SteeringGamepad0 = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SteeringGamepad0"
QT_MOC_LITERAL(1, 17, 22), // "slotGamepadIsConnected"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 18), // "slotButtonsChanged"
QT_MOC_LITERAL(4, 60, 14) // "ButtonsPressed"

    },
    "SteeringGamepad0\0slotGamepadIsConnected\0"
    "\0slotButtonsChanged\0ButtonsPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SteeringGamepad0[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       3,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

       0        // eod
};

void SteeringGamepad0::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SteeringGamepad0 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotGamepadIsConnected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slotButtonsChanged((*reinterpret_cast< ButtonsPressed(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ButtonsPressed >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SteeringGamepad0::staticMetaObject = { {
    &SteeringInterface::staticMetaObject,
    qt_meta_stringdata_SteeringGamepad0.data,
    qt_meta_data_SteeringGamepad0,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SteeringGamepad0::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SteeringGamepad0::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SteeringGamepad0.stringdata0))
        return static_cast<void*>(this);
    return SteeringInterface::qt_metacast(_clname);
}

int SteeringGamepad0::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SteeringInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_SteeringGamepad1_t {
    QByteArrayData data[7];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SteeringGamepad1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SteeringGamepad1_t qt_meta_stringdata_SteeringGamepad1 = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SteeringGamepad1"
QT_MOC_LITERAL(1, 17, 25), // "signalSteeringDataChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 13), // "SteeringData*"
QT_MOC_LITERAL(4, 58, 22), // "slotGamepadIsConnected"
QT_MOC_LITERAL(5, 81, 18), // "slotButtonsChanged"
QT_MOC_LITERAL(6, 100, 14) // "ButtonsPressed"

    },
    "SteeringGamepad1\0signalSteeringDataChanged\0"
    "\0SteeringData*\0slotGamepadIsConnected\0"
    "slotButtonsChanged\0ButtonsPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SteeringGamepad1[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void SteeringGamepad1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SteeringGamepad1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSteeringDataChanged((*reinterpret_cast< SteeringData*(*)>(_a[1]))); break;
        case 1: _t->slotGamepadIsConnected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slotButtonsChanged((*reinterpret_cast< ButtonsPressed(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ButtonsPressed >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SteeringGamepad1::*)(SteeringData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SteeringGamepad1::signalSteeringDataChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SteeringGamepad1::staticMetaObject = { {
    &SteeringInterface::staticMetaObject,
    qt_meta_stringdata_SteeringGamepad1.data,
    qt_meta_data_SteeringGamepad1,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SteeringGamepad1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SteeringGamepad1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SteeringGamepad1.stringdata0))
        return static_cast<void*>(this);
    return SteeringInterface::qt_metacast(_clname);
}

int SteeringGamepad1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SteeringInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SteeringGamepad1::signalSteeringDataChanged(SteeringData * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

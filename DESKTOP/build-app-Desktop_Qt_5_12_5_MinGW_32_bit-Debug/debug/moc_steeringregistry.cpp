/****************************************************************************
** Meta object code from reading C++ file 'steeringregistry.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../app/steeringregistry.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'steeringregistry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SteeringRegistry_t {
    QByteArrayData data[7];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SteeringRegistry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SteeringRegistry_t qt_meta_stringdata_SteeringRegistry = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SteeringRegistry"
QT_MOC_LITERAL(1, 17, 26), // "signalSteeringsDataChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 29), // "QHash<QString,SteeringData*>*"
QT_MOC_LITERAL(4, 75, 25), // "signalSteeringDataChanged"
QT_MOC_LITERAL(5, 101, 13), // "SteeringData*"
QT_MOC_LITERAL(6, 115, 23) // "slotSteeringDataChanged"

    },
    "SteeringRegistry\0signalSteeringsDataChanged\0"
    "\0QHash<QString,SteeringData*>*\0"
    "signalSteeringDataChanged\0SteeringData*\0"
    "slotSteeringDataChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SteeringRegistry[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void SteeringRegistry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SteeringRegistry *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSteeringsDataChanged((*reinterpret_cast< QHash<QString,SteeringData*>*(*)>(_a[1]))); break;
        case 1: _t->signalSteeringDataChanged((*reinterpret_cast< SteeringData*(*)>(_a[1]))); break;
        case 2: _t->slotSteeringDataChanged((*reinterpret_cast< SteeringData*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SteeringRegistry::*)(QHash<QString,SteeringData*> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SteeringRegistry::signalSteeringsDataChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SteeringRegistry::*)(SteeringData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SteeringRegistry::signalSteeringDataChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SteeringRegistry::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SteeringRegistry.data,
    qt_meta_data_SteeringRegistry,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SteeringRegistry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SteeringRegistry::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SteeringRegistry.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SteeringRegistry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void SteeringRegistry::signalSteeringsDataChanged(QHash<QString,SteeringData*> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SteeringRegistry::signalSteeringDataChanged(SteeringData * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

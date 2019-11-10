/****************************************************************************
** Meta object code from reading C++ file 'drone.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../app/drone.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drone.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Drone_t {
    QByteArrayData data[18];
    char stringdata0[375];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Drone_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Drone_t qt_meta_stringdata_Drone = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Drone"
QT_MOC_LITERAL(1, 6, 20), // "configurationChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 18), // "signalModesChanged"
QT_MOC_LITERAL(4, 47, 6), // "Modes*"
QT_MOC_LITERAL(5, 54, 5), // "modes"
QT_MOC_LITERAL(6, 60, 25), // "signalSteeringDataChanged"
QT_MOC_LITERAL(7, 86, 13), // "SteeringData*"
QT_MOC_LITERAL(8, 100, 25), // "signalSendingsDataChanged"
QT_MOC_LITERAL(9, 126, 28), // "QHash<QString,SendingData*>*"
QT_MOC_LITERAL(10, 155, 34), // "handleMenuActionsSettingsTrig..."
QT_MOC_LITERAL(11, 190, 30), // "handleMenuActionsExitTriggered"
QT_MOC_LITERAL(12, 221, 21), // "handleDialogFlyClosed"
QT_MOC_LITERAL(13, 243, 28), // "handleWizardAddProfileClosed"
QT_MOC_LITERAL(14, 272, 24), // "handleWizardUploadClosed"
QT_MOC_LITERAL(15, 297, 29), // "handleDialogEditProfileClosed"
QT_MOC_LITERAL(16, 327, 23), // "slotSteeringDataChanged"
QT_MOC_LITERAL(17, 351, 23) // "slotSendingsDataChanged"

    },
    "Drone\0configurationChanged\0\0"
    "signalModesChanged\0Modes*\0modes\0"
    "signalSteeringDataChanged\0SteeringData*\0"
    "signalSendingsDataChanged\0"
    "QHash<QString,SendingData*>*\0"
    "handleMenuActionsSettingsTriggered\0"
    "handleMenuActionsExitTriggered\0"
    "handleDialogFlyClosed\0"
    "handleWizardAddProfileClosed\0"
    "handleWizardUploadClosed\0"
    "handleDialogEditProfileClosed\0"
    "slotSteeringDataChanged\0slotSendingsDataChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Drone[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       6,    1,   78,    2, 0x06 /* Public */,
       8,    1,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   84,    2, 0x08 /* Private */,
      11,    1,   87,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,
      16,    1,   94,    2, 0x08 /* Private */,
      17,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void Drone::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Drone *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->configurationChanged(); break;
        case 1: _t->signalModesChanged((*reinterpret_cast< Modes*(*)>(_a[1]))); break;
        case 2: _t->signalSteeringDataChanged((*reinterpret_cast< SteeringData*(*)>(_a[1]))); break;
        case 3: _t->signalSendingsDataChanged((*reinterpret_cast< QHash<QString,SendingData*>*(*)>(_a[1]))); break;
        case 4: _t->handleMenuActionsSettingsTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->handleMenuActionsExitTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->handleDialogFlyClosed(); break;
        case 7: _t->handleWizardAddProfileClosed(); break;
        case 8: _t->handleWizardUploadClosed(); break;
        case 9: _t->handleDialogEditProfileClosed(); break;
        case 10: _t->slotSteeringDataChanged((*reinterpret_cast< SteeringData*(*)>(_a[1]))); break;
        case 11: _t->slotSendingsDataChanged((*reinterpret_cast< QHash<QString,SendingData*>*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Drone::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Drone::configurationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Drone::*)(Modes * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Drone::signalModesChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Drone::*)(SteeringData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Drone::signalSteeringDataChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Drone::*)(QHash<QString,SendingData*> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Drone::signalSendingsDataChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Drone::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Drone.data,
    qt_meta_data_Drone,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Drone::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Drone::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Drone.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Drone::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Drone::configurationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Drone::signalModesChanged(Modes * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Drone::signalSteeringDataChanged(SteeringData * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Drone::signalSendingsDataChanged(QHash<QString,SendingData*> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

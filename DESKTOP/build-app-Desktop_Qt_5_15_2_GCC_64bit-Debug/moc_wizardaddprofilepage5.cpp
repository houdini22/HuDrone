/****************************************************************************
** Meta object code from reading C++ file 'wizardaddprofilepage5.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../app/ui/wizardaddprofilepage5.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wizardaddprofilepage5.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WizardAddProfilePage5_t {
    QByteArrayData data[7];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WizardAddProfilePage5_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WizardAddProfilePage5_t qt_meta_stringdata_WizardAddProfilePage5 = {
    {
QT_MOC_LITERAL(0, 0, 21), // "WizardAddProfilePage5"
QT_MOC_LITERAL(1, 22, 16), // "slotMyPushButton"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 13), // "MyPushButton*"
QT_MOC_LITERAL(4, 54, 22), // "slotMyPushButtonDelete"
QT_MOC_LITERAL(5, 77, 16), // "slotMyTextEdited"
QT_MOC_LITERAL(6, 94, 11) // "MyLineEdit*"

    },
    "WizardAddProfilePage5\0slotMyPushButton\0"
    "\0MyPushButton*\0slotMyPushButtonDelete\0"
    "slotMyTextEdited\0MyLineEdit*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WizardAddProfilePage5[] = {

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
       1,    1,   29,    2, 0x08 /* Private */,
       4,    1,   32,    2, 0x08 /* Private */,
       5,    1,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void WizardAddProfilePage5::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WizardAddProfilePage5 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotMyPushButton((*reinterpret_cast< MyPushButton*(*)>(_a[1]))); break;
        case 1: _t->slotMyPushButtonDelete((*reinterpret_cast< MyPushButton*(*)>(_a[1]))); break;
        case 2: _t->slotMyTextEdited((*reinterpret_cast< MyLineEdit*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MyPushButton* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MyPushButton* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MyLineEdit* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WizardAddProfilePage5::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_WizardAddProfilePage5.data,
    qt_meta_data_WizardAddProfilePage5,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WizardAddProfilePage5::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WizardAddProfilePage5::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WizardAddProfilePage5.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int WizardAddProfilePage5::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

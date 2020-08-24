/****************************************************************************
** Meta object code from reading C++ file 'setupPage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-clock/setupPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setupPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_setuppage_t {
    QByteArrayData data[13];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_setuppage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_setuppage_t qt_meta_stringdata_setuppage = {
    {
QT_MOC_LITERAL(0, 0, 9), // "setuppage"
QT_MOC_LITERAL(1, 10, 13), // "Mute_starting"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "werk_day_set"
QT_MOC_LITERAL(4, 38, 15), // "Time_format_set"
QT_MOC_LITERAL(5, 54, 17), // "Pop_up_window_set"
QT_MOC_LITERAL(6, 72, 16), // "Reminder_off_set"
QT_MOC_LITERAL(7, 89, 20), // "Default_ringtone_set"
QT_MOC_LITERAL(8, 110, 22), // "werk_day_listClickslot"
QT_MOC_LITERAL(9, 133, 25), // "Time_format_listClickslot"
QT_MOC_LITERAL(10, 159, 27), // "Pop_up_window_listClickslot"
QT_MOC_LITERAL(11, 187, 26), // "Reminder_off_listClickslot"
QT_MOC_LITERAL(12, 214, 30) // "Default_ringtone_listClickslot"

    },
    "setuppage\0Mute_starting\0\0werk_day_set\0"
    "Time_format_set\0Pop_up_window_set\0"
    "Reminder_off_set\0Default_ringtone_set\0"
    "werk_day_listClickslot\0Time_format_listClickslot\0"
    "Pop_up_window_listClickslot\0"
    "Reminder_off_listClickslot\0"
    "Default_ringtone_listClickslot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_setuppage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void setuppage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        setuppage *_t = static_cast<setuppage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Mute_starting(); break;
        case 1: _t->werk_day_set(); break;
        case 2: _t->Time_format_set(); break;
        case 3: _t->Pop_up_window_set(); break;
        case 4: _t->Reminder_off_set(); break;
        case 5: _t->Default_ringtone_set(); break;
        case 6: _t->werk_day_listClickslot(); break;
        case 7: _t->Time_format_listClickslot(); break;
        case 8: _t->Pop_up_window_listClickslot(); break;
        case 9: _t->Reminder_off_listClickslot(); break;
        case 10: _t->Default_ringtone_listClickslot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject setuppage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_setuppage.data,
      qt_meta_data_setuppage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *setuppage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *setuppage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_setuppage.stringdata0))
        return static_cast<void*>(const_cast< setuppage*>(this));
    return QWidget::qt_metacast(_clname);
}

int setuppage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

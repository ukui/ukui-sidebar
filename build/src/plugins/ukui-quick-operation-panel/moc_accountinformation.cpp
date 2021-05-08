/****************************************************************************
** Meta object code from reading C++ file 'accountinformation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-quick-operation-panel/accountinformation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accountinformation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AccountInformation_t {
    QByteArrayData data[8];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AccountInformation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AccountInformation_t qt_meta_stringdata_AccountInformation = {
    {
QT_MOC_LITERAL(0, 0, 18), // "AccountInformation"
QT_MOC_LITERAL(1, 19, 23), // "openShutdownWidgetSlots"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 28), // "openContorlCenterWidgetSlots"
QT_MOC_LITERAL(4, 73, 12), // "AccountSlots"
QT_MOC_LITERAL(5, 86, 8), // "property"
QT_MOC_LITERAL(6, 95, 11), // "propertyMap"
QT_MOC_LITERAL(7, 107, 12) // "propertyList"

    },
    "AccountInformation\0openShutdownWidgetSlots\0"
    "\0openContorlCenterWidgetSlots\0"
    "AccountSlots\0property\0propertyMap\0"
    "propertyList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AccountInformation[] = {

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
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    3,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap, QMetaType::QStringList,    5,    6,    7,

       0        // eod
};

void AccountInformation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AccountInformation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openShutdownWidgetSlots(); break;
        case 1: _t->openContorlCenterWidgetSlots(); break;
        case 2: _t->AccountSlots((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QMap<QString,QVariant>(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AccountInformation::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_AccountInformation.data,
    qt_meta_data_AccountInformation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AccountInformation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AccountInformation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AccountInformation.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AccountInformation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

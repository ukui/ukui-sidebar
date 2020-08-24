/****************************************************************************
** Meta object code from reading C++ file 'appmsg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-sidebar-notification/appmsg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appmsg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AppMsg_t {
    QByteArrayData data[31];
    char stringdata0[428];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppMsg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppMsg_t qt_meta_stringdata_AppMsg = {
    {
QT_MOC_LITERAL(0, 0, 6), // "AppMsg"
QT_MOC_LITERAL(1, 7, 18), // "Sig_onDeleteAppMsg"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "AppMsg*"
QT_MOC_LITERAL(4, 35, 1), // "p"
QT_MOC_LITERAL(5, 37, 24), // "Sig_onDeleteTakeInAppMsg"
QT_MOC_LITERAL(6, 62, 26), // "Sig_countTakeInBitAndUpate"
QT_MOC_LITERAL(7, 89, 23), // "Sig_SendTakeInSingleMsg"
QT_MOC_LITERAL(8, 113, 10), // "strAppName"
QT_MOC_LITERAL(9, 124, 7), // "strIcon"
QT_MOC_LITERAL(10, 132, 10), // "strSummary"
QT_MOC_LITERAL(11, 143, 7), // "strBody"
QT_MOC_LITERAL(12, 151, 8), // "dateTime"
QT_MOC_LITERAL(13, 160, 6), // "maxNum"
QT_MOC_LITERAL(14, 167, 14), // "bNewTakeinFlag"
QT_MOC_LITERAL(15, 182, 20), // "Sig_SendAddSingleMsg"
QT_MOC_LITERAL(16, 203, 20), // "bNewNotificationFlag"
QT_MOC_LITERAL(17, 224, 14), // "onDeleteAppMsg"
QT_MOC_LITERAL(18, 239, 16), // "onTakeinWholeApp"
QT_MOC_LITERAL(19, 256, 17), // "onRecoverWholeApp"
QT_MOC_LITERAL(20, 274, 15), // "onDeleSingleMsg"
QT_MOC_LITERAL(21, 290, 10), // "SingleMsg*"
QT_MOC_LITERAL(22, 301, 10), // "pSingleMsg"
QT_MOC_LITERAL(23, 312, 17), // "onTakeInSingleMsg"
QT_MOC_LITERAL(24, 330, 18), // "onRecoverSingleMsg"
QT_MOC_LITERAL(25, 349, 14), // "setAppFoldFlag"
QT_MOC_LITERAL(26, 364, 5), // "bFlag"
QT_MOC_LITERAL(27, 370, 14), // "onMainMsgEnter"
QT_MOC_LITERAL(28, 385, 14), // "onMainMsgLeave"
QT_MOC_LITERAL(29, 400, 13), // "onShowBaseMap"
QT_MOC_LITERAL(30, 414, 13) // "onHideBaseMap"

    },
    "AppMsg\0Sig_onDeleteAppMsg\0\0AppMsg*\0p\0"
    "Sig_onDeleteTakeInAppMsg\0"
    "Sig_countTakeInBitAndUpate\0"
    "Sig_SendTakeInSingleMsg\0strAppName\0"
    "strIcon\0strSummary\0strBody\0dateTime\0"
    "maxNum\0bNewTakeinFlag\0Sig_SendAddSingleMsg\0"
    "bNewNotificationFlag\0onDeleteAppMsg\0"
    "onTakeinWholeApp\0onRecoverWholeApp\0"
    "onDeleSingleMsg\0SingleMsg*\0pSingleMsg\0"
    "onTakeInSingleMsg\0onRecoverSingleMsg\0"
    "setAppFoldFlag\0bFlag\0onMainMsgEnter\0"
    "onMainMsgLeave\0onShowBaseMap\0onHideBaseMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppMsg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       5,    1,   97,    2, 0x06 /* Public */,
       6,    0,  100,    2, 0x06 /* Public */,
       7,    7,  101,    2, 0x06 /* Public */,
      15,    7,  116,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  131,    2, 0x0a /* Public */,
      18,    0,  132,    2, 0x0a /* Public */,
      19,    0,  133,    2, 0x0a /* Public */,
      20,    1,  134,    2, 0x0a /* Public */,
      23,    1,  137,    2, 0x0a /* Public */,
      24,    1,  140,    2, 0x0a /* Public */,
      25,    1,  143,    2, 0x0a /* Public */,
      27,    0,  146,    2, 0x0a /* Public */,
      28,    0,  147,    2, 0x0a /* Public */,
      29,    0,  148,    2, 0x0a /* Public */,
      30,    0,  149,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime, QMetaType::Int, QMetaType::Bool,    8,    9,   10,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime, QMetaType::Int, QMetaType::Bool,    8,    9,   10,   11,   12,   13,   16,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AppMsg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AppMsg *_t = static_cast<AppMsg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Sig_onDeleteAppMsg((*reinterpret_cast< AppMsg*(*)>(_a[1]))); break;
        case 1: _t->Sig_onDeleteTakeInAppMsg((*reinterpret_cast< AppMsg*(*)>(_a[1]))); break;
        case 2: _t->Sig_countTakeInBitAndUpate(); break;
        case 3: _t->Sig_SendTakeInSingleMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QDateTime(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 4: _t->Sig_SendAddSingleMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QDateTime(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 5: _t->onDeleteAppMsg(); break;
        case 6: _t->onTakeinWholeApp(); break;
        case 7: _t->onRecoverWholeApp(); break;
        case 8: _t->onDeleSingleMsg((*reinterpret_cast< SingleMsg*(*)>(_a[1]))); break;
        case 9: _t->onTakeInSingleMsg((*reinterpret_cast< SingleMsg*(*)>(_a[1]))); break;
        case 10: _t->onRecoverSingleMsg((*reinterpret_cast< SingleMsg*(*)>(_a[1]))); break;
        case 11: _t->setAppFoldFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->onMainMsgEnter(); break;
        case 13: _t->onMainMsgLeave(); break;
        case 14: _t->onShowBaseMap(); break;
        case 15: _t->onHideBaseMap(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AppMsg* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AppMsg* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AppMsg::*_t)(AppMsg * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppMsg::Sig_onDeleteAppMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AppMsg::*_t)(AppMsg * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppMsg::Sig_onDeleteTakeInAppMsg)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AppMsg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppMsg::Sig_countTakeInBitAndUpate)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AppMsg::*_t)(QString , QString , QString , QString , QDateTime , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppMsg::Sig_SendTakeInSingleMsg)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AppMsg::*_t)(QString , QString , QString , QString , QDateTime , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppMsg::Sig_SendAddSingleMsg)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject AppMsg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AppMsg.data,
      qt_meta_data_AppMsg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AppMsg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppMsg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AppMsg.stringdata0))
        return static_cast<void*>(const_cast< AppMsg*>(this));
    return QWidget::qt_metacast(_clname);
}

int AppMsg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void AppMsg::Sig_onDeleteAppMsg(AppMsg * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AppMsg::Sig_onDeleteTakeInAppMsg(AppMsg * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AppMsg::Sig_countTakeInBitAndUpate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void AppMsg::Sig_SendTakeInSingleMsg(QString _t1, QString _t2, QString _t3, QString _t4, QDateTime _t5, int _t6, bool _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AppMsg::Sig_SendAddSingleMsg(QString _t1, QString _t2, QString _t3, QString _t4, QDateTime _t5, int _t6, bool _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

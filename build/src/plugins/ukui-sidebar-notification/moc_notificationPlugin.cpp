/****************************************************************************
** Meta object code from reading C++ file 'notificationPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-sidebar-notification/notificationPlugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notificationPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NotificationPlugin_t {
    QByteArrayData data[25];
    char stringdata0[368];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NotificationPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NotificationPlugin_t qt_meta_stringdata_NotificationPlugin = {
    {
QT_MOC_LITERAL(0, 0, 18), // "NotificationPlugin"
QT_MOC_LITERAL(1, 19, 21), // "Sig_onNewNotification"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 17), // "onAddSingleNotify"
QT_MOC_LITERAL(4, 60, 10), // "strAppName"
QT_MOC_LITERAL(5, 71, 11), // "strIconPath"
QT_MOC_LITERAL(6, 83, 10), // "strSummary"
QT_MOC_LITERAL(7, 94, 7), // "strBody"
QT_MOC_LITERAL(8, 102, 8), // "dateTime"
QT_MOC_LITERAL(9, 111, 6), // "maxNum"
QT_MOC_LITERAL(10, 118, 20), // "bNewNotificationFlag"
QT_MOC_LITERAL(11, 139, 20), // "onTakeInSingleNotify"
QT_MOC_LITERAL(12, 160, 7), // "strIcon"
QT_MOC_LITERAL(13, 168, 14), // "bNewTakeinFlag"
QT_MOC_LITERAL(14, 183, 17), // "onClearAllMessage"
QT_MOC_LITERAL(15, 201, 13), // "onClearAppMsg"
QT_MOC_LITERAL(16, 215, 7), // "AppMsg*"
QT_MOC_LITERAL(17, 223, 7), // "pAppMsg"
QT_MOC_LITERAL(18, 231, 19), // "onClearTakeInAppMsg"
QT_MOC_LITERAL(19, 251, 19), // "onShowTakeInMessage"
QT_MOC_LITERAL(20, 271, 18), // "onCallControlPanel"
QT_MOC_LITERAL(21, 290, 24), // "onCountTakeInBitAndUpate"
QT_MOC_LITERAL(22, 315, 13), // "onCloseAppMsg"
QT_MOC_LITERAL(23, 329, 17), // "onUpdateAppMaxNum"
QT_MOC_LITERAL(24, 347, 20) // "onSwitchMsgBoxFinish"

    },
    "NotificationPlugin\0Sig_onNewNotification\0"
    "\0onAddSingleNotify\0strAppName\0strIconPath\0"
    "strSummary\0strBody\0dateTime\0maxNum\0"
    "bNewNotificationFlag\0onTakeInSingleNotify\0"
    "strIcon\0bNewTakeinFlag\0onClearAllMessage\0"
    "onClearAppMsg\0AppMsg*\0pAppMsg\0"
    "onClearTakeInAppMsg\0onShowTakeInMessage\0"
    "onCallControlPanel\0onCountTakeInBitAndUpate\0"
    "onCloseAppMsg\0onUpdateAppMaxNum\0"
    "onSwitchMsgBoxFinish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NotificationPlugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    7,   75,    2, 0x08 /* Private */,
      11,    7,   90,    2, 0x08 /* Private */,
      14,    0,  105,    2, 0x08 /* Private */,
      15,    1,  106,    2, 0x08 /* Private */,
      18,    1,  109,    2, 0x08 /* Private */,
      19,    0,  112,    2, 0x08 /* Private */,
      20,    0,  113,    2, 0x08 /* Private */,
      21,    0,  114,    2, 0x08 /* Private */,
      22,    1,  115,    2, 0x08 /* Private */,
      23,    2,  118,    2, 0x08 /* Private */,
      24,    0,  123,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::UInt, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime, QMetaType::Int, QMetaType::Bool,    4,    5,    6,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime, QMetaType::Int, QMetaType::Bool,    4,   12,    6,    7,    8,    9,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    4,    9,
    QMetaType::Void,

       0        // eod
};

void NotificationPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NotificationPlugin *_t = static_cast<NotificationPlugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Sig_onNewNotification(); break;
        case 1: { uint _r = _t->onAddSingleNotify((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QDateTime(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 2: _t->onTakeInSingleNotify((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QDateTime(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 3: _t->onClearAllMessage(); break;
        case 4: _t->onClearAppMsg((*reinterpret_cast< AppMsg*(*)>(_a[1]))); break;
        case 5: _t->onClearTakeInAppMsg((*reinterpret_cast< AppMsg*(*)>(_a[1]))); break;
        case 6: _t->onShowTakeInMessage(); break;
        case 7: _t->onCallControlPanel(); break;
        case 8: _t->onCountTakeInBitAndUpate(); break;
        case 9: _t->onCloseAppMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->onUpdateAppMaxNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->onSwitchMsgBoxFinish(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NotificationPlugin::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NotificationPlugin::Sig_onNewNotification)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject NotificationPlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NotificationPlugin.data,
      qt_meta_data_NotificationPlugin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NotificationPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotificationPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NotificationPlugin.stringdata0))
        return static_cast<void*>(const_cast< NotificationPlugin*>(this));
    if (!strcmp(_clname, "NotificationInterface"))
        return static_cast< NotificationInterface*>(const_cast< NotificationPlugin*>(this));
    if (!strcmp(_clname, "org.qt-project.Qt.QGenericPluginFactoryInterface"))
        return static_cast< NotificationInterface*>(const_cast< NotificationPlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int NotificationPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void NotificationPlugin::Sig_onNewNotification()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xd8, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xc4, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '0',  0x00, 'o',  'r',  'g',  '.',  'q',  't', 
    '-',  'p',  'r',  'o',  'j',  'e',  'c',  't', 
    '.',  'Q',  't',  '.',  'Q',  'G',  'e',  'n', 
    'e',  'r',  'i',  'c',  'P',  'l',  'u',  'g', 
    'i',  'n',  'F',  'a',  'c',  't',  'o',  'r', 
    'y',  'I',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e',  0x00, 0x00, 0x9b, 0x0b, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x12, 0x00, 'N',  'o', 
    't',  'i',  'f',  'i',  'c',  'a',  't',  'i', 
    'o',  'n',  'P',  'l',  'u',  'g',  'i',  'n', 
    ':',  0xc0, 0xa0, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x13, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, '(',  0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, '$',  0x00, 0x00, 0x00,
    0x14, 0x03, 0x00, 0x00, 0x04, 0x00, 'K',  'e', 
    'y',  's',  0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x8c, 0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x00, 'p',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xd8, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xc4, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '0',  0x00, 'o',  'r',  'g',  '.',  'q',  't', 
    '-',  'p',  'r',  'o',  'j',  'e',  'c',  't', 
    '.',  'Q',  't',  '.',  'Q',  'G',  'e',  'n', 
    'e',  'r',  'i',  'c',  'P',  'l',  'u',  'g', 
    'i',  'n',  'F',  'a',  'c',  't',  'o',  'r', 
    'y',  'I',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e',  0x00, 0x00, 0x95, 0x0b, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, '(',  0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, '$',  0x00, 0x00, 0x00,
    0x14, 0x03, 0x00, 0x00, 0x04, 0x00, 'K',  'e', 
    'y',  's',  0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x9b, 0x12, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x12, 0x00, 'N',  'o', 
    't',  'i',  'f',  'i',  'c',  'a',  't',  'i', 
    'o',  'n',  'P',  'l',  'u',  'g',  'i',  'n', 
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, ':',  0xc0, 0xa0, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    'L',  0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00,
    0xa8, 0x00, 0x00, 0x00, 0xb4, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(NotificationPlugin, NotificationPlugin)

QT_END_MOC_NAMESPACE

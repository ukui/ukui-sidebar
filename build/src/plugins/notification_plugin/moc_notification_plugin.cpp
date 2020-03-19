/****************************************************************************
** Meta object code from reading C++ file 'notification_plugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/notification_plugin/notification_plugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notification_plugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NotificationPlugin_t {
    QByteArrayData data[20];
    char stringdata0[293];
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
QT_MOC_LITERAL(9, 111, 20), // "bNewNotificationFlag"
QT_MOC_LITERAL(10, 132, 20), // "onTakeInSingleNotify"
QT_MOC_LITERAL(11, 153, 7), // "strIcon"
QT_MOC_LITERAL(12, 161, 17), // "onClearAllMessage"
QT_MOC_LITERAL(13, 179, 13), // "onClearAppMsg"
QT_MOC_LITERAL(14, 193, 7), // "AppMsg*"
QT_MOC_LITERAL(15, 201, 7), // "pAppMsg"
QT_MOC_LITERAL(16, 209, 19), // "onClearTakeInAppMsg"
QT_MOC_LITERAL(17, 229, 19), // "onShowTakeInMessage"
QT_MOC_LITERAL(18, 249, 18), // "onCallControlPanel"
QT_MOC_LITERAL(19, 268, 24) // "onCountTakeInBitAndUpate"

    },
    "NotificationPlugin\0Sig_onNewNotification\0"
    "\0onAddSingleNotify\0strAppName\0strIconPath\0"
    "strSummary\0strBody\0dateTime\0"
    "bNewNotificationFlag\0onTakeInSingleNotify\0"
    "strIcon\0onClearAllMessage\0onClearAppMsg\0"
    "AppMsg*\0pAppMsg\0onClearTakeInAppMsg\0"
    "onShowTakeInMessage\0onCallControlPanel\0"
    "onCountTakeInBitAndUpate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NotificationPlugin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    6,   60,    2, 0x08 /* Private */,
      10,    5,   73,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,
      16,    1,   88,    2, 0x08 /* Private */,
      17,    0,   91,    2, 0x08 /* Private */,
      18,    0,   92,    2, 0x08 /* Private */,
      19,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::UInt, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime, QMetaType::Bool,    4,    5,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime,    4,   11,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NotificationPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NotificationPlugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Sig_onNewNotification(); break;
        case 1: { uint _r = _t->onAddSingleNotify((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QDateTime(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->onTakeInSingleNotify((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QDateTime(*)>(_a[5]))); break;
        case 3: _t->onClearAllMessage(); break;
        case 4: _t->onClearAppMsg((*reinterpret_cast< AppMsg*(*)>(_a[1]))); break;
        case 5: _t->onClearTakeInAppMsg((*reinterpret_cast< AppMsg*(*)>(_a[1]))); break;
        case 6: _t->onShowTakeInMessage(); break;
        case 7: _t->onCallControlPanel(); break;
        case 8: _t->onCountTakeInBitAndUpate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NotificationPlugin::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NotificationPlugin::Sig_onNewNotification)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NotificationPlugin::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_NotificationPlugin.data,
    qt_meta_data_NotificationPlugin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NotificationPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotificationPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NotificationPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NotificationInterface"))
        return static_cast< NotificationInterface*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QGenericPluginFactoryInterface"))
        return static_cast< NotificationInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int NotificationPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void NotificationPlugin::Sig_onNewNotification()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x30,  'o',  'r',  'g',  '.',  'q', 
    't',  '-',  'p',  'r',  'o',  'j',  'e',  'c', 
    't',  '.',  'Q',  't',  '.',  'Q',  'G',  'e', 
    'n',  'e',  'r',  'i',  'c',  'P',  'l',  'u', 
    'g',  'i',  'n',  'F',  'a',  'c',  't',  'o', 
    'r',  'y',  'I',  'n',  't',  'e',  'r',  'f', 
    'a',  'c',  'e', 
    // "className"
    0x03,  0x72,  'N',  'o',  't',  'i',  'f',  'i', 
    'c',  'a',  't',  'i',  'o',  'n',  'P',  'l', 
    'u',  'g',  'i',  'n', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x80, 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(NotificationPlugin, NotificationPlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE

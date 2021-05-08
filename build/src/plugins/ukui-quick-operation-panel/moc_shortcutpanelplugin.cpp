/****************************************************************************
** Meta object code from reading C++ file 'shortcutpanelplugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-quick-operation-panel/shortcutpanelplugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shortcutpanelplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_shortcutPanelPlugin_t {
    QByteArrayData data[11];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_shortcutPanelPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_shortcutPanelPlugin_t qt_meta_stringdata_shortcutPanelPlugin = {
    {
QT_MOC_LITERAL(0, 0, 19), // "shortcutPanelPlugin"
QT_MOC_LITERAL(1, 20, 17), // "spreadClikedSlots"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 15), // "foldClikedSlots"
QT_MOC_LITERAL(4, 55, 19), // "ShowEditWidgetSlots"
QT_MOC_LITERAL(5, 75, 19), // "HideEditWidgetSlots"
QT_MOC_LITERAL(6, 95, 14), // "addButtonSlots"
QT_MOC_LITERAL(7, 110, 16), // "resetShortWidget"
QT_MOC_LITERAL(8, 127, 27), // "setCanceGsettingButtonValue"
QT_MOC_LITERAL(9, 155, 3), // "key"
QT_MOC_LITERAL(10, 159, 21) // "hideDropDownWidgetBox"

    },
    "shortcutPanelPlugin\0spreadClikedSlots\0"
    "\0foldClikedSlots\0ShowEditWidgetSlots\0"
    "HideEditWidgetSlots\0addButtonSlots\0"
    "resetShortWidget\0setCanceGsettingButtonValue\0"
    "key\0hideDropDownWidgetBox"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_shortcutPanelPlugin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    1,   60,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

       0        // eod
};

void shortcutPanelPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<shortcutPanelPlugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->spreadClikedSlots(); break;
        case 1: _t->foldClikedSlots(); break;
        case 2: _t->ShowEditWidgetSlots(); break;
        case 3: _t->HideEditWidgetSlots(); break;
        case 4: _t->addButtonSlots(); break;
        case 5: _t->resetShortWidget(); break;
        case 6: _t->setCanceGsettingButtonValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->hideDropDownWidgetBox(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject shortcutPanelPlugin::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_shortcutPanelPlugin.data,
    qt_meta_data_shortcutPanelPlugin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *shortcutPanelPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *shortcutPanelPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_shortcutPanelPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "shortCutPanelInterface"))
        return static_cast< shortCutPanelInterface*>(this);
    if (!strcmp(_clname, "org.ukui.sidebar-qt.plugin-iface.shortCutPanelInterface"))
        return static_cast< shortCutPanelInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int shortcutPanelPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x37,  'o',  'r',  'g',  '.',  'u', 
    'k',  'u',  'i',  '.',  's',  'i',  'd',  'e', 
    'b',  'a',  'r',  '-',  'q',  't',  '.',  'p', 
    'l',  'u',  'g',  'i',  'n',  '-',  'i',  'f', 
    'a',  'c',  'e',  '.',  's',  'h',  'o',  'r', 
    't',  'C',  'u',  't',  'P',  'a',  'n',  'e', 
    'l',  'I',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e', 
    // "className"
    0x03,  0x73,  's',  'h',  'o',  'r',  't',  'c', 
    'u',  't',  'P',  'a',  'n',  'e',  'l',  'P', 
    'l',  'u',  'g',  'i',  'n', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x80, 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(shortcutPanelPlugin, shortcutPanelPlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE

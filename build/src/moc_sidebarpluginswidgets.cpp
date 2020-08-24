/****************************************************************************
** Meta object code from reading C++ file 'sidebarpluginswidgets.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/sidebarpluginswidgets.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sidebarpluginswidgets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_sidebarPluginsWidgets_t {
    QByteArrayData data[13];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sidebarPluginsWidgets_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sidebarPluginsWidgets_t qt_meta_stringdata_sidebarPluginsWidgets = {
    {
QT_MOC_LITERAL(0, 0, 21), // "sidebarPluginsWidgets"
QT_MOC_LITERAL(1, 22, 18), // "FontModifyComplete"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 22), // "m_pClipBoardStateSlots"
QT_MOC_LITERAL(4, 65, 25), // "m_pSmallPluginsStateSlots"
QT_MOC_LITERAL(5, 91, 22), // "m_ClipboardButtonSlots"
QT_MOC_LITERAL(6, 114, 26), // "m_SidebarPluginButtonSlots"
QT_MOC_LITERAL(7, 141, 18), // "m_pFoldButtonSlots"
QT_MOC_LITERAL(8, 160, 20), // "m_pSpreadButtonSlots"
QT_MOC_LITERAL(9, 181, 28), // "m_AnimationClipbarodEndSlots"
QT_MOC_LITERAL(10, 210, 30), // "m_AnimationSmallWidgetEndSlots"
QT_MOC_LITERAL(11, 241, 20), // "getTransparencyValue"
QT_MOC_LITERAL(12, 262, 3) // "key"

    },
    "sidebarPluginsWidgets\0FontModifyComplete\0"
    "\0m_pClipBoardStateSlots\0"
    "m_pSmallPluginsStateSlots\0"
    "m_ClipboardButtonSlots\0"
    "m_SidebarPluginButtonSlots\0"
    "m_pFoldButtonSlots\0m_pSpreadButtonSlots\0"
    "m_AnimationClipbarodEndSlots\0"
    "m_AnimationSmallWidgetEndSlots\0"
    "getTransparencyValue\0key"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sidebarPluginsWidgets[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void sidebarPluginsWidgets::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sidebarPluginsWidgets *_t = static_cast<sidebarPluginsWidgets *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FontModifyComplete(); break;
        case 1: _t->m_pClipBoardStateSlots(); break;
        case 2: _t->m_pSmallPluginsStateSlots(); break;
        case 3: _t->m_ClipboardButtonSlots(); break;
        case 4: _t->m_SidebarPluginButtonSlots(); break;
        case 5: _t->m_pFoldButtonSlots(); break;
        case 6: _t->m_pSpreadButtonSlots(); break;
        case 7: _t->m_AnimationClipbarodEndSlots(); break;
        case 8: _t->m_AnimationSmallWidgetEndSlots(); break;
        case 9: _t->getTransparencyValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (sidebarPluginsWidgets::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sidebarPluginsWidgets::FontModifyComplete)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject sidebarPluginsWidgets::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_sidebarPluginsWidgets.data,
      qt_meta_data_sidebarPluginsWidgets,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *sidebarPluginsWidgets::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sidebarPluginsWidgets::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_sidebarPluginsWidgets.stringdata0))
        return static_cast<void*>(const_cast< sidebarPluginsWidgets*>(this));
    return QWidget::qt_metacast(_clname);
}

int sidebarPluginsWidgets::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void sidebarPluginsWidgets::FontModifyComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

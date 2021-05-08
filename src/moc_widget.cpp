/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[22];
    char stringdata0[342];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 19), // "onResolutionChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "argc"
QT_MOC_LITERAL(4, 33, 17), // "onNewNotification"
QT_MOC_LITERAL(5, 51, 19), // "hideAnimationFinish"
QT_MOC_LITERAL(6, 71, 19), // "showAnimationAction"
QT_MOC_LITERAL(7, 91, 5), // "value"
QT_MOC_LITERAL(8, 97, 19), // "showAnimationFinish"
QT_MOC_LITERAL(9, 117, 24), // "primaryScreenChangedSLot"
QT_MOC_LITERAL(10, 142, 18), // "ClipboardShowSlots"
QT_MOC_LITERAL(11, 161, 18), // "ClipboardHideSlots"
QT_MOC_LITERAL(12, 180, 23), // "screenCountChangedSlots"
QT_MOC_LITERAL(13, 204, 5), // "count"
QT_MOC_LITERAL(14, 210, 16), // "OpenSidebarSlots"
QT_MOC_LITERAL(15, 227, 25), // "OpenControlCenterSettings"
QT_MOC_LITERAL(16, 253, 26), // "ClickPanelHideSidebarSlots"
QT_MOC_LITERAL(17, 280, 17), // "bootOptionsFilter"
QT_MOC_LITERAL(18, 298, 3), // "opt"
QT_MOC_LITERAL(19, 302, 14), // "XkbEventsPress"
QT_MOC_LITERAL(20, 317, 7), // "keycode"
QT_MOC_LITERAL(21, 325, 16) // "XkbEventsRelease"

    },
    "Widget\0onResolutionChanged\0\0argc\0"
    "onNewNotification\0hideAnimationFinish\0"
    "showAnimationAction\0value\0showAnimationFinish\0"
    "primaryScreenChangedSLot\0ClipboardShowSlots\0"
    "ClipboardHideSlots\0screenCountChangedSlots\0"
    "count\0OpenSidebarSlots\0OpenControlCenterSettings\0"
    "ClickPanelHideSidebarSlots\0bootOptionsFilter\0"
    "opt\0XkbEventsPress\0keycode\0XkbEventsRelease"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x08 /* Private */,
       4,    0,   92,    2, 0x08 /* Private */,
       5,    0,   93,    2, 0x08 /* Private */,
       6,    1,   94,    2, 0x08 /* Private */,
       8,    0,   97,    2, 0x08 /* Private */,
       9,    0,   98,    2, 0x08 /* Private */,
      10,    0,   99,    2, 0x08 /* Private */,
      11,    0,  100,    2, 0x08 /* Private */,
      12,    1,  101,    2, 0x08 /* Private */,
      14,    0,  104,    2, 0x08 /* Private */,
      15,    0,  105,    2, 0x08 /* Private */,
      16,    0,  106,    2, 0x08 /* Private */,
      17,    1,  107,    2, 0x08 /* Private */,
      19,    1,  110,    2, 0x08 /* Private */,
      21,    1,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QRect,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,   20,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onResolutionChanged((*reinterpret_cast< const QRect(*)>(_a[1]))); break;
        case 1: _t->onNewNotification(); break;
        case 2: _t->hideAnimationFinish(); break;
        case 3: _t->showAnimationAction((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 4: _t->showAnimationFinish(); break;
        case 5: _t->primaryScreenChangedSLot(); break;
        case 6: _t->ClipboardShowSlots(); break;
        case 7: _t->ClipboardHideSlots(); break;
        case 8: _t->screenCountChangedSlots((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->OpenSidebarSlots(); break;
        case 10: _t->OpenControlCenterSettings(); break;
        case 11: _t->ClickPanelHideSidebarSlots(); break;
        case 12: _t->bootOptionsFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->XkbEventsPress((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->XkbEventsRelease((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

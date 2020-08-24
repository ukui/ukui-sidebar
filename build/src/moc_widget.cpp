/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[20];
    char stringdata0[359];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 23, 28), // "com.ukui.panel.sidebar.value"
QT_MOC_LITERAL(3, 52, 19), // "onResolutionChanged"
QT_MOC_LITERAL(4, 72, 0), // ""
QT_MOC_LITERAL(5, 73, 4), // "argc"
QT_MOC_LITERAL(6, 78, 17), // "onNewNotification"
QT_MOC_LITERAL(7, 96, 19), // "hideAnimationFinish"
QT_MOC_LITERAL(8, 116, 19), // "showAnimationAction"
QT_MOC_LITERAL(9, 136, 5), // "value"
QT_MOC_LITERAL(10, 142, 19), // "showAnimationFinish"
QT_MOC_LITERAL(11, 162, 24), // "primaryScreenChangedSLot"
QT_MOC_LITERAL(12, 187, 18), // "ClipboardShowSlots"
QT_MOC_LITERAL(13, 206, 18), // "ClipboardHideSlots"
QT_MOC_LITERAL(14, 225, 23), // "screenCountChangedSlots"
QT_MOC_LITERAL(15, 249, 5), // "count"
QT_MOC_LITERAL(16, 255, 16), // "OpenSidebarSlots"
QT_MOC_LITERAL(17, 272, 25), // "OpenControlCenterSettings"
QT_MOC_LITERAL(18, 298, 26), // "ClickPanelHideSidebarSlots"
QT_MOC_LITERAL(19, 325, 33) // "updateSmallPluginsClipboardWi..."

    },
    "Widget\0D-Bus Interface\0"
    "com.ukui.panel.sidebar.value\0"
    "onResolutionChanged\0\0argc\0onNewNotification\0"
    "hideAnimationFinish\0showAnimationAction\0"
    "value\0showAnimationFinish\0"
    "primaryScreenChangedSLot\0ClipboardShowSlots\0"
    "ClipboardHideSlots\0screenCountChangedSlots\0"
    "count\0OpenSidebarSlots\0OpenControlCenterSettings\0"
    "ClickPanelHideSidebarSlots\0"
    "updateSmallPluginsClipboardWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       1,   14, // classinfo
      13,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

 // slots: name, argc, parameters, tag, flags
       3,    1,   81,    4, 0x08 /* Private */,
       6,    0,   84,    4, 0x08 /* Private */,
       7,    0,   85,    4, 0x08 /* Private */,
       8,    1,   86,    4, 0x08 /* Private */,
      10,    0,   89,    4, 0x08 /* Private */,
      11,    0,   90,    4, 0x08 /* Private */,
      12,    0,   91,    4, 0x08 /* Private */,
      13,    0,   92,    4, 0x08 /* Private */,
      14,    1,   93,    4, 0x08 /* Private */,
      16,    0,   96,    4, 0x08 /* Private */,
      17,    0,   97,    4, 0x08 /* Private */,
      18,    0,   98,    4, 0x08 /* Private */,
      19,    0,   99,    4, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QRect,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
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
        case 12: _t->updateSmallPluginsClipboardWidget(); break;
        default: ;
        }
    }
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

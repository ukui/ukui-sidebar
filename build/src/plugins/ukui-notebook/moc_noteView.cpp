/****************************************************************************
** Meta object code from reading C++ file 'noteView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-notebook/noteView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'noteView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NoteView_t {
    QByteArrayData data[17];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoteView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoteView_t qt_meta_stringdata_NoteView = {
    {
QT_MOC_LITERAL(0, 0, 8), // "NoteView"
QT_MOC_LITERAL(1, 9, 15), // "viewportPressed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 18), // "rowsAboutToBeMoved"
QT_MOC_LITERAL(4, 45, 11), // "QModelIndex"
QT_MOC_LITERAL(5, 57, 12), // "sourceParent"
QT_MOC_LITERAL(6, 70, 11), // "sourceStart"
QT_MOC_LITERAL(7, 82, 9), // "sourceEnd"
QT_MOC_LITERAL(8, 92, 17), // "destinationParent"
QT_MOC_LITERAL(9, 110, 14), // "destinationRow"
QT_MOC_LITERAL(10, 125, 9), // "rowsMoved"
QT_MOC_LITERAL(11, 135, 6), // "parent"
QT_MOC_LITERAL(12, 142, 5), // "start"
QT_MOC_LITERAL(13, 148, 3), // "end"
QT_MOC_LITERAL(14, 152, 11), // "destination"
QT_MOC_LITERAL(15, 164, 3), // "row"
QT_MOC_LITERAL(16, 168, 4) // "init"

    },
    "NoteView\0viewportPressed\0\0rowsAboutToBeMoved\0"
    "QModelIndex\0sourceParent\0sourceStart\0"
    "sourceEnd\0destinationParent\0destinationRow\0"
    "rowsMoved\0parent\0start\0end\0destination\0"
    "row\0init"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    5,   35,    2, 0x0a /* Public */,
      10,    5,   46,    2, 0x0a /* Public */,
      16,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int, QMetaType::Int, 0x80000000 | 4, QMetaType::Int,    5,    6,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int, QMetaType::Int, 0x80000000 | 4, QMetaType::Int,   11,   12,   13,   14,   15,
    QMetaType::Void,

       0        // eod
};

void NoteView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NoteView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->viewportPressed(); break;
        case 1: _t->rowsAboutToBeMoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->rowsMoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 3: _t->init(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NoteView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NoteView::viewportPressed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NoteView::staticMetaObject = { {
    &QListView::staticMetaObject,
    qt_meta_stringdata_NoteView.data,
    qt_meta_data_NoteView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NoteView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NoteView.stringdata0))
        return static_cast<void*>(this);
    return QListView::qt_metacast(_clname);
}

int NoteView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void NoteView::viewportPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

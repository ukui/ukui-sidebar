/****************************************************************************
** Meta object code from reading C++ file 'noteView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-notebook/noteView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'noteView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NoteView_t {
    QByteArrayData data[18];
    char stringdata0[195];
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
QT_MOC_LITERAL(4, 45, 12), // "sourceParent"
QT_MOC_LITERAL(5, 58, 11), // "sourceStart"
QT_MOC_LITERAL(6, 70, 9), // "sourceEnd"
QT_MOC_LITERAL(7, 80, 17), // "destinationParent"
QT_MOC_LITERAL(8, 98, 14), // "destinationRow"
QT_MOC_LITERAL(9, 113, 9), // "rowsMoved"
QT_MOC_LITERAL(10, 123, 6), // "parent"
QT_MOC_LITERAL(11, 130, 5), // "start"
QT_MOC_LITERAL(12, 136, 3), // "end"
QT_MOC_LITERAL(13, 140, 11), // "destination"
QT_MOC_LITERAL(14, 152, 3), // "row"
QT_MOC_LITERAL(15, 156, 4), // "init"
QT_MOC_LITERAL(16, 161, 12), // "rowsInserted"
QT_MOC_LITERAL(17, 174, 20) // "rowsAboutToBeRemoved"

    },
    "NoteView\0viewportPressed\0\0rowsAboutToBeMoved\0"
    "sourceParent\0sourceStart\0sourceEnd\0"
    "destinationParent\0destinationRow\0"
    "rowsMoved\0parent\0start\0end\0destination\0"
    "row\0init\0rowsInserted\0rowsAboutToBeRemoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    5,   45,    2, 0x0a /* Public */,
       9,    5,   56,    2, 0x0a /* Public */,
      15,    0,   67,    2, 0x08 /* Private */,
      16,    3,   68,    2, 0x09 /* Protected */,
      17,    3,   75,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int, QMetaType::QModelIndex, QMetaType::Int,    4,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int, QMetaType::QModelIndex, QMetaType::Int,   10,   11,   12,   13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,   10,   11,   12,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,   10,   11,   12,

       0        // eod
};

void NoteView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoteView *_t = static_cast<NoteView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->viewportPressed(); break;
        case 1: _t->rowsAboutToBeMoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->rowsMoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QModelIndex(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 3: _t->init(); break;
        case 4: _t->rowsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->rowsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NoteView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoteView::viewportPressed)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject NoteView::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_NoteView.data,
      qt_meta_data_NoteView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoteView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoteView.stringdata0))
        return static_cast<void*>(const_cast< NoteView*>(this));
    return QListView::qt_metacast(_clname);
}

int NoteView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NoteView::viewportPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

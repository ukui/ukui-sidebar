/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-notebook/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[44];
    char stringdata0[601];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 16), // "requestNotesList"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 20), // "requestOpenDBManager"
QT_MOC_LITERAL(4, 46, 4), // "path"
QT_MOC_LITERAL(5, 51, 8), // "doCreate"
QT_MOC_LITERAL(6, 60, 23), // "requestCreateUpdateNote"
QT_MOC_LITERAL(7, 84, 9), // "NoteData*"
QT_MOC_LITERAL(8, 94, 4), // "note"
QT_MOC_LITERAL(9, 99, 17), // "requestDeleteNote"
QT_MOC_LITERAL(10, 117, 19), // "requestRestoreNotes"
QT_MOC_LITERAL(11, 137, 16), // "QList<NoteData*>"
QT_MOC_LITERAL(12, 154, 8), // "noteList"
QT_MOC_LITERAL(13, 163, 18), // "requestImportNotes"
QT_MOC_LITERAL(14, 182, 18), // "requestExportNotes"
QT_MOC_LITERAL(15, 201, 8), // "fileName"
QT_MOC_LITERAL(16, 210, 19), // "requestMigrateNotes"
QT_MOC_LITERAL(17, 230, 19), // "requestMigrateTrash"
QT_MOC_LITERAL(18, 250, 29), // "requestForceLastRowIndexValue"
QT_MOC_LITERAL(19, 280, 5), // "index"
QT_MOC_LITERAL(20, 286, 8), // "InitData"
QT_MOC_LITERAL(21, 295, 9), // "loadNotes"
QT_MOC_LITERAL(22, 305, 11), // "noteCounter"
QT_MOC_LITERAL(23, 317, 8), // "exitSlot"
QT_MOC_LITERAL(24, 326, 8), // "miniSlot"
QT_MOC_LITERAL(25, 335, 8), // "editSlot"
QT_MOC_LITERAL(26, 344, 7), // "newSlot"
QT_MOC_LITERAL(27, 352, 13), // "listClickSlot"
QT_MOC_LITERAL(28, 366, 19), // "listDoubleClickSlot"
QT_MOC_LITERAL(29, 386, 21), // "onTextEditTextChanged"
QT_MOC_LITERAL(30, 408, 6), // "noteId"
QT_MOC_LITERAL(31, 415, 1), // "i"
QT_MOC_LITERAL(32, 417, 14), // "onColorChanged"
QT_MOC_LITERAL(33, 432, 5), // "color"
QT_MOC_LITERAL(34, 438, 20), // "onTrashButtonClicked"
QT_MOC_LITERAL(35, 459, 23), // "onSearchEditTextChanged"
QT_MOC_LITERAL(36, 483, 7), // "keyword"
QT_MOC_LITERAL(37, 491, 8), // "sortSlot"
QT_MOC_LITERAL(38, 500, 14), // "changePageSlot"
QT_MOC_LITERAL(39, 515, 24), // "delAction_del_SearchLine"
QT_MOC_LITERAL(40, 540, 25), // "on_SearchLine_textChanged"
QT_MOC_LITERAL(41, 566, 4), // "arg1"
QT_MOC_LITERAL(42, 571, 15), // "setNoteNullSlot"
QT_MOC_LITERAL(43, 587, 13) // "emptyNoteSLot"

    },
    "Widget\0requestNotesList\0\0requestOpenDBManager\0"
    "path\0doCreate\0requestCreateUpdateNote\0"
    "NoteData*\0note\0requestDeleteNote\0"
    "requestRestoreNotes\0QList<NoteData*>\0"
    "noteList\0requestImportNotes\0"
    "requestExportNotes\0fileName\0"
    "requestMigrateNotes\0requestMigrateTrash\0"
    "requestForceLastRowIndexValue\0index\0"
    "InitData\0loadNotes\0noteCounter\0exitSlot\0"
    "miniSlot\0editSlot\0newSlot\0listClickSlot\0"
    "listDoubleClickSlot\0onTextEditTextChanged\0"
    "noteId\0i\0onColorChanged\0color\0"
    "onTrashButtonClicked\0onSearchEditTextChanged\0"
    "keyword\0sortSlot\0changePageSlot\0"
    "delAction_del_SearchLine\0"
    "on_SearchLine_textChanged\0arg1\0"
    "setNoteNullSlot\0emptyNoteSLot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  154,    2, 0x06 /* Public */,
       3,    2,  155,    2, 0x06 /* Public */,
       6,    1,  160,    2, 0x06 /* Public */,
       9,    1,  163,    2, 0x06 /* Public */,
      10,    1,  166,    2, 0x06 /* Public */,
      13,    1,  169,    2, 0x06 /* Public */,
      14,    1,  172,    2, 0x06 /* Public */,
      16,    1,  175,    2, 0x06 /* Public */,
      17,    1,  178,    2, 0x06 /* Public */,
      18,    1,  181,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    0,  184,    2, 0x08 /* Private */,
      21,    2,  185,    2, 0x08 /* Private */,
      23,    0,  190,    2, 0x08 /* Private */,
      24,    0,  191,    2, 0x08 /* Private */,
      25,    0,  192,    2, 0x08 /* Private */,
      26,    0,  193,    2, 0x08 /* Private */,
      27,    1,  194,    2, 0x08 /* Private */,
      28,    1,  197,    2, 0x08 /* Private */,
      29,    2,  200,    2, 0x08 /* Private */,
      32,    2,  205,    2, 0x08 /* Private */,
      34,    0,  210,    2, 0x08 /* Private */,
      35,    1,  211,    2, 0x08 /* Private */,
      37,    0,  214,    2, 0x08 /* Private */,
      38,    0,  215,    2, 0x08 /* Private */,
      39,    0,  216,    2, 0x08 /* Private */,
      40,    1,  217,    2, 0x08 /* Private */,
      42,    0,  220,    2, 0x08 /* Private */,
      43,    0,  221,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Int,   19,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int,   12,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   19,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   30,   31,
    QMetaType::Void, QMetaType::QColor, QMetaType::Int,   33,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   41,
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
        case 0: _t->requestNotesList(); break;
        case 1: _t->requestOpenDBManager((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->requestCreateUpdateNote((*reinterpret_cast< NoteData*(*)>(_a[1]))); break;
        case 3: _t->requestDeleteNote((*reinterpret_cast< NoteData*(*)>(_a[1]))); break;
        case 4: _t->requestRestoreNotes((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 5: _t->requestImportNotes((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 6: _t->requestExportNotes((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->requestMigrateNotes((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 8: _t->requestMigrateTrash((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 9: _t->requestForceLastRowIndexValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->InitData(); break;
        case 11: _t->loadNotes((*reinterpret_cast< QList<NoteData*>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->exitSlot(); break;
        case 13: _t->miniSlot(); break;
        case 14: _t->editSlot(); break;
        case 15: _t->newSlot(); break;
        case 16: _t->listClickSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 17: _t->listDoubleClickSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 18: _t->onTextEditTextChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->onColorChanged((*reinterpret_cast< const QColor(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: _t->onTrashButtonClicked(); break;
        case 21: _t->onSearchEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->sortSlot(); break;
        case 23: _t->changePageSlot(); break;
        case 24: _t->delAction_del_SearchLine(); break;
        case 25: _t->on_SearchLine_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->setNoteNullSlot(); break;
        case 27: _t->emptyNoteSLot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NoteData* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NoteData* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Widget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestNotesList)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestOpenDBManager)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(NoteData * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestCreateUpdateNote)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(NoteData * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestDeleteNote)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(QList<NoteData*> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestRestoreNotes)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(QList<NoteData*> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestImportNotes)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestExportNotes)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(QList<NoteData*> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestMigrateNotes)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(QList<NoteData*> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestMigrateTrash)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Widget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Widget::requestForceLastRowIndexValue)) {
                *result = 9;
                return;
            }
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
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void Widget::requestNotesList()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Widget::requestOpenDBManager(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Widget::requestCreateUpdateNote(NoteData * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Widget::requestDeleteNote(NoteData * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Widget::requestRestoreNotes(QList<NoteData*> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Widget::requestImportNotes(QList<NoteData*> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Widget::requestExportNotes(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Widget::requestMigrateNotes(QList<NoteData*> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Widget::requestMigrateTrash(QList<NoteData*> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Widget::requestForceLastRowIndexValue(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE

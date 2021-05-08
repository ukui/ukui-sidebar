/****************************************************************************
** Meta object code from reading C++ file 'dbManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-notebook/dbManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DBManager_t {
    QByteArrayData data[23];
    char stringdata0[377];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DBManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DBManager_t qt_meta_stringdata_DBManager = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DBManager"
QT_MOC_LITERAL(1, 10, 13), // "notesReceived"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 16), // "QList<NoteData*>"
QT_MOC_LITERAL(4, 42, 8), // "noteList"
QT_MOC_LITERAL(5, 51, 11), // "noteCounter"
QT_MOC_LITERAL(6, 63, 25), // "permanantlyRemoveAllNotes"
QT_MOC_LITERAL(7, 89, 20), // "onNotesListRequested"
QT_MOC_LITERAL(8, 110, 24), // "onOpenDBManagerRequested"
QT_MOC_LITERAL(9, 135, 4), // "path"
QT_MOC_LITERAL(10, 140, 8), // "doCreate"
QT_MOC_LITERAL(11, 149, 23), // "onCreateUpdateRequested"
QT_MOC_LITERAL(12, 173, 9), // "NoteData*"
QT_MOC_LITERAL(13, 183, 4), // "note"
QT_MOC_LITERAL(14, 188, 21), // "onDeleteNoteRequested"
QT_MOC_LITERAL(15, 210, 22), // "onImportNotesRequested"
QT_MOC_LITERAL(16, 233, 23), // "onRestoreNotesRequested"
QT_MOC_LITERAL(17, 257, 22), // "onExportNotesRequested"
QT_MOC_LITERAL(18, 280, 8), // "fileName"
QT_MOC_LITERAL(19, 289, 23), // "onMigrateNotesRequested"
QT_MOC_LITERAL(20, 313, 23), // "onMigrateTrashRequested"
QT_MOC_LITERAL(21, 337, 33), // "onForceLastRowIndexValueReque..."
QT_MOC_LITERAL(22, 371, 5) // "index"

    },
    "DBManager\0notesReceived\0\0QList<NoteData*>\0"
    "noteList\0noteCounter\0permanantlyRemoveAllNotes\0"
    "onNotesListRequested\0onOpenDBManagerRequested\0"
    "path\0doCreate\0onCreateUpdateRequested\0"
    "NoteData*\0note\0onDeleteNoteRequested\0"
    "onImportNotesRequested\0onRestoreNotesRequested\0"
    "onExportNotesRequested\0fileName\0"
    "onMigrateNotesRequested\0onMigrateTrashRequested\0"
    "onForceLastRowIndexValueRequested\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DBManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   79,    2, 0x0a /* Public */,
       7,    0,   80,    2, 0x0a /* Public */,
       8,    2,   81,    2, 0x0a /* Public */,
      11,    1,   86,    2, 0x0a /* Public */,
      14,    1,   89,    2, 0x0a /* Public */,
      15,    1,   92,    2, 0x0a /* Public */,
      16,    1,   95,    2, 0x0a /* Public */,
      17,    1,   98,    2, 0x0a /* Public */,
      19,    1,  101,    2, 0x0a /* Public */,
      20,    1,  104,    2, 0x0a /* Public */,
      21,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,   22,

       0        // eod
};

void DBManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DBManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notesReceived((*reinterpret_cast< QList<NoteData*>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: { bool _r = _t->permanantlyRemoveAllNotes();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->onNotesListRequested(); break;
        case 3: _t->onOpenDBManagerRequested((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->onCreateUpdateRequested((*reinterpret_cast< NoteData*(*)>(_a[1]))); break;
        case 5: _t->onDeleteNoteRequested((*reinterpret_cast< NoteData*(*)>(_a[1]))); break;
        case 6: _t->onImportNotesRequested((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 7: _t->onRestoreNotesRequested((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 8: _t->onExportNotesRequested((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->onMigrateNotesRequested((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 10: _t->onMigrateTrashRequested((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 11: _t->onForceLastRowIndexValueRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NoteData* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NoteData* >(); break;
            }
            break;
        case 6:
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
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DBManager::*)(QList<NoteData*> , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DBManager::notesReceived)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DBManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DBManager.data,
    qt_meta_data_DBManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DBManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DBManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DBManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DBManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void DBManager::notesReceived(QList<NoteData*> _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

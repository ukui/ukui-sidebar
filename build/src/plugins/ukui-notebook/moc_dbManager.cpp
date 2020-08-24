/****************************************************************************
** Meta object code from reading C++ file 'dbManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
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
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DBManager_t {
    QByteArrayData data[22];
    char stringdata0[351];
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
QT_MOC_LITERAL(6, 63, 20), // "onNotesListRequested"
QT_MOC_LITERAL(7, 84, 24), // "onOpenDBManagerRequested"
QT_MOC_LITERAL(8, 109, 4), // "path"
QT_MOC_LITERAL(9, 114, 8), // "doCreate"
QT_MOC_LITERAL(10, 123, 23), // "onCreateUpdateRequested"
QT_MOC_LITERAL(11, 147, 9), // "NoteData*"
QT_MOC_LITERAL(12, 157, 4), // "note"
QT_MOC_LITERAL(13, 162, 21), // "onDeleteNoteRequested"
QT_MOC_LITERAL(14, 184, 22), // "onImportNotesRequested"
QT_MOC_LITERAL(15, 207, 23), // "onRestoreNotesRequested"
QT_MOC_LITERAL(16, 231, 22), // "onExportNotesRequested"
QT_MOC_LITERAL(17, 254, 8), // "fileName"
QT_MOC_LITERAL(18, 263, 23), // "onMigrateNotesRequested"
QT_MOC_LITERAL(19, 287, 23), // "onMigrateTrashRequested"
QT_MOC_LITERAL(20, 311, 33), // "onForceLastRowIndexValueReque..."
QT_MOC_LITERAL(21, 345, 5) // "index"

    },
    "DBManager\0notesReceived\0\0QList<NoteData*>\0"
    "noteList\0noteCounter\0onNotesListRequested\0"
    "onOpenDBManagerRequested\0path\0doCreate\0"
    "onCreateUpdateRequested\0NoteData*\0"
    "note\0onDeleteNoteRequested\0"
    "onImportNotesRequested\0onRestoreNotesRequested\0"
    "onExportNotesRequested\0fileName\0"
    "onMigrateNotesRequested\0onMigrateTrashRequested\0"
    "onForceLastRowIndexValueRequested\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DBManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   74,    2, 0x0a /* Public */,
       7,    2,   75,    2, 0x0a /* Public */,
      10,    1,   80,    2, 0x0a /* Public */,
      13,    1,   83,    2, 0x0a /* Public */,
      14,    1,   86,    2, 0x0a /* Public */,
      15,    1,   89,    2, 0x0a /* Public */,
      16,    1,   92,    2, 0x0a /* Public */,
      18,    1,   95,    2, 0x0a /* Public */,
      19,    1,   98,    2, 0x0a /* Public */,
      20,    1,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void DBManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DBManager *_t = static_cast<DBManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notesReceived((*reinterpret_cast< QList<NoteData*>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->onNotesListRequested(); break;
        case 2: _t->onOpenDBManagerRequested((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->onCreateUpdateRequested((*reinterpret_cast< NoteData*(*)>(_a[1]))); break;
        case 4: _t->onDeleteNoteRequested((*reinterpret_cast< NoteData*(*)>(_a[1]))); break;
        case 5: _t->onImportNotesRequested((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 6: _t->onRestoreNotesRequested((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 7: _t->onExportNotesRequested((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->onMigrateNotesRequested((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 9: _t->onMigrateTrashRequested((*reinterpret_cast< QList<NoteData*>(*)>(_a[1]))); break;
        case 10: _t->onForceLastRowIndexValueRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
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
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NoteData* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<NoteData*> >(); break;
            }
            break;
        case 6:
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
        case 9:
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
            typedef void (DBManager::*_t)(QList<NoteData*> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DBManager::notesReceived)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DBManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DBManager.data,
      qt_meta_data_DBManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DBManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DBManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DBManager.stringdata0))
        return static_cast<void*>(const_cast< DBManager*>(this));
    return QObject::qt_metacast(_clname);
}

int DBManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DBManager::notesReceived(QList<NoteData*> _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

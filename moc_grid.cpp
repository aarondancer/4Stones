/****************************************************************************
** Meta object code from reading C++ file 'grid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "grid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Grid_t {
    QByteArrayData data[18];
    char stringdata[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Grid_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Grid_t qt_meta_stringdata_Grid = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 21),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 10),
QT_MOC_LITERAL(4, 39, 5),
QT_MOC_LITERAL(5, 45, 6),
QT_MOC_LITERAL(6, 52, 8),
QT_MOC_LITERAL(7, 61, 10),
QT_MOC_LITERAL(8, 72, 13),
QT_MOC_LITERAL(9, 86, 17),
QT_MOC_LITERAL(10, 104, 3),
QT_MOC_LITERAL(11, 108, 6),
QT_MOC_LITERAL(12, 115, 14),
QT_MOC_LITERAL(13, 130, 4),
QT_MOC_LITERAL(14, 135, 18),
QT_MOC_LITERAL(15, 154, 10),
QT_MOC_LITERAL(16, 165, 8),
QT_MOC_LITERAL(17, 174, 10)
    },
    "Grid\0idkwhattodowithnotify\0\0placePiece\0"
    "index\0player\0checkWin\0indexToRow\0"
    "indexToColumn\0coordinateToIndex\0row\0"
    "column\0valueFromIndex\0grid\0"
    "QList<QList<int> >\0gridLength\0lastMove\0"
    "countToWin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Grid[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       4,   72, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    2,   50,    2, 0x02 /* Public */,
       6,    1,   55,    2, 0x02 /* Public */,
       7,    1,   58,    2, 0x02 /* Public */,
       8,    1,   61,    2, 0x02 /* Public */,
       9,    2,   64,    2, 0x02 /* Public */,
      12,    1,   69,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Bool, QMetaType::Int,    5,
    QMetaType::Int, QMetaType::Int,    4,
    QMetaType::Int, QMetaType::Int,    4,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Int, QMetaType::Int,    4,

 // properties: name, type, flags
      13, 0x80000000 | 14, 0x00495009,
      15, QMetaType::Int, 0x00495103,
      16, QMetaType::Int, 0x00495103,
      17, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,

       0        // eod
};

void Grid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Grid *_t = static_cast<Grid *>(_o);
        switch (_id) {
        case 0: _t->idkwhattodowithnotify(); break;
        case 1: _t->placePiece((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: { bool _r = _t->checkWin((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->indexToRow((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = _t->indexToColumn((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = _t->coordinateToIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->valueFromIndex((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Grid::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Grid::idkwhattodowithnotify)) {
                *result = 0;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QList<int> > >(); break;
        }
    }

}

const QMetaObject Grid::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Grid.data,
      qt_meta_data_Grid,  qt_static_metacall, 0, 0}
};


const QMetaObject *Grid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Grid::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Grid.stringdata))
        return static_cast<void*>(const_cast< Grid*>(this));
    return QObject::qt_metacast(_clname);
}

int Grid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QList<QList<int> >*>(_v) = getGrid(); break;
        case 1: *reinterpret_cast< int*>(_v) = getGridLength(); break;
        case 2: *reinterpret_cast< int*>(_v) = getLastMove(); break;
        case 3: *reinterpret_cast< int*>(_v) = getCountToWin(); break;
        default: break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: setGridLength(*reinterpret_cast< int*>(_v)); break;
        case 2: setLastMove(*reinterpret_cast< int*>(_v)); break;
        case 3: setCountToWin(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Grid::idkwhattodowithnotify()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'st_group.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/widget/st_group.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'st_group.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SelectGroup_t {
    QByteArrayData data[6];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectGroup_t qt_meta_stringdata_SelectGroup = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SelectGroup"
QT_MOC_LITERAL(1, 12, 25), // "changeMessageListForFlist"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "index"
QT_MOC_LITERAL(4, 45, 4), // "name"
QT_MOC_LITERAL(5, 50, 25) // "changeMessageListForClist"

    },
    "SelectGroup\0changeMessageListForFlist\0"
    "\0index\0name\0changeMessageListForClist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectGroup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x02 /* Public */,
       5,    2,   29,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

       0        // eod
};

void SelectGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SelectGroup *_t = static_cast<SelectGroup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeMessageListForFlist((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->changeMessageListForClist((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SelectGroup::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SelectGroup.data,
      qt_meta_data_SelectGroup,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SelectGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SelectGroup.stringdata0))
        return static_cast<void*>(const_cast< SelectGroup*>(this));
    return QObject::qt_metacast(_clname);
}

int SelectGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

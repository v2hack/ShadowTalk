/****************************************************************************
** Meta object code from reading C++ file 'st_pixelsize.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/core/st_pixelsize.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'st_pixelsize.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PointSizeToPixelSize_t {
    QByteArrayData data[7];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PointSizeToPixelSize_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PointSizeToPixelSize_t qt_meta_stringdata_PointSizeToPixelSize = {
    {
QT_MOC_LITERAL(0, 0, 20), // "PointSizeToPixelSize"
QT_MOC_LITERAL(1, 21, 9), // "pixelSize"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "pointSize"
QT_MOC_LITERAL(4, 42, 6), // "height"
QT_MOC_LITERAL(5, 49, 5), // "width"
QT_MOC_LITERAL(6, 55, 4) // "text"

    },
    "PointSizeToPixelSize\0pixelSize\0\0"
    "pointSize\0height\0width\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PointSizeToPixelSize[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x02 /* Public */,
       4,    1,   32,    2, 0x02 /* Public */,
       5,    2,   35,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, QMetaType::Int,    3,
    QMetaType::Int, QMetaType::Int,    3,
    QMetaType::Int, QMetaType::Int, QMetaType::QString,    3,    6,

       0        // eod
};

void PointSizeToPixelSize::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PointSizeToPixelSize *_t = static_cast<PointSizeToPixelSize *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->pixelSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->height((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->width((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject PointSizeToPixelSize::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PointSizeToPixelSize.data,
      qt_meta_data_PointSizeToPixelSize,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PointSizeToPixelSize::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PointSizeToPixelSize::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PointSizeToPixelSize.stringdata0))
        return static_cast<void*>(const_cast< PointSizeToPixelSize*>(this));
    return QObject::qt_metacast(_clname);
}

int PointSizeToPixelSize::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

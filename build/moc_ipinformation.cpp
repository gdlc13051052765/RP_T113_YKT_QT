/****************************************************************************
** Meta object code from reading C++ file 'ipinformation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ipinformation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ipinformation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ipInformation_t {
    QByteArrayData data[10];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ipInformation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ipInformation_t qt_meta_stringdata_ipInformation = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ipInformation"
QT_MOC_LITERAL(1, 14, 13), // "keyPressEvent"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "QKeyEvent*"
QT_MOC_LITERAL(4, 40, 2), // "ev"
QT_MOC_LITERAL(5, 43, 11), // "eventFilter"
QT_MOC_LITERAL(6, 55, 7), // "watched"
QT_MOC_LITERAL(7, 63, 7), // "QEvent*"
QT_MOC_LITERAL(8, 71, 5), // "event"
QT_MOC_LITERAL(9, 77, 31) // "save_ipInformation_to_config_db"

    },
    "ipInformation\0keyPressEvent\0\0QKeyEvent*\0"
    "ev\0eventFilter\0watched\0QEvent*\0event\0"
    "save_ipInformation_to_config_db"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ipInformation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       5,    2,   32,    2, 0x08 /* Private */,
       9,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 7,    6,    8,
    QMetaType::Void,

       0        // eod
};

void ipInformation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ipInformation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->save_ipInformation_to_config_db(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ipInformation::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_ipInformation.data,
    qt_meta_data_ipInformation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ipInformation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ipInformation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ipInformation.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ipInformation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

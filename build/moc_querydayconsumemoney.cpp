/****************************************************************************
** Meta object code from reading C++ file 'querydayconsumemoney.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../querydayconsumemoney.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'querydayconsumemoney.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QueryDayConsumeMoney_t {
    QByteArrayData data[11];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QueryDayConsumeMoney_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QueryDayConsumeMoney_t qt_meta_stringdata_QueryDayConsumeMoney = {
    {
QT_MOC_LITERAL(0, 0, 20), // "QueryDayConsumeMoney"
QT_MOC_LITERAL(1, 21, 10), // "paintEvent"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "QPaintEvent*"
QT_MOC_LITERAL(4, 46, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(5, 62, 10), // "QKeyEvent*"
QT_MOC_LITERAL(6, 73, 2), // "ev"
QT_MOC_LITERAL(7, 76, 11), // "eventFilter"
QT_MOC_LITERAL(8, 88, 7), // "watched"
QT_MOC_LITERAL(9, 96, 7), // "QEvent*"
QT_MOC_LITERAL(10, 104, 5) // "event"

    },
    "QueryDayConsumeMoney\0paintEvent\0\0"
    "QPaintEvent*\0keyReleaseEvent\0QKeyEvent*\0"
    "ev\0eventFilter\0watched\0QEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QueryDayConsumeMoney[] = {

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
       4,    1,   32,    2, 0x08 /* Private */,
       7,    2,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 9,    8,   10,

       0        // eod
};

void QueryDayConsumeMoney::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QueryDayConsumeMoney *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 1: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QueryDayConsumeMoney::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_QueryDayConsumeMoney.data,
    qt_meta_data_QueryDayConsumeMoney,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QueryDayConsumeMoney::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QueryDayConsumeMoney::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QueryDayConsumeMoney.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int QueryDayConsumeMoney::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

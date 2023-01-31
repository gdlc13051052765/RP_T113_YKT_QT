/****************************************************************************
** Meta object code from reading C++ file 'setup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../setup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_setUp_t {
    QByteArrayData data[14];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_setUp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_setUp_t qt_meta_stringdata_setUp = {
    {
QT_MOC_LITERAL(0, 0, 5), // "setUp"
QT_MOC_LITERAL(1, 6, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "QKeyEvent*"
QT_MOC_LITERAL(4, 34, 2), // "ev"
QT_MOC_LITERAL(5, 37, 12), // "focusInEvent"
QT_MOC_LITERAL(6, 50, 12), // "QFocusEvent*"
QT_MOC_LITERAL(7, 63, 18), // "setIpButtonClicked"
QT_MOC_LITERAL(8, 82, 28), // "setDeviceNumberButtonClicked"
QT_MOC_LITERAL(9, 111, 34), // "queryDayConsumeRecordButtonCl..."
QT_MOC_LITERAL(10, 146, 31), // "queryCollectRecordButtonClicked"
QT_MOC_LITERAL(11, 178, 27), // "setConsumeModeButtonClicked"
QT_MOC_LITERAL(12, 206, 26), // "modifySysTimeButtonClicked"
QT_MOC_LITERAL(13, 233, 16) // "otaButtonClicked"

    },
    "setUp\0keyReleaseEvent\0\0QKeyEvent*\0ev\0"
    "focusInEvent\0QFocusEvent*\0setIpButtonClicked\0"
    "setDeviceNumberButtonClicked\0"
    "queryDayConsumeRecordButtonClicked\0"
    "queryCollectRecordButtonClicked\0"
    "setConsumeModeButtonClicked\0"
    "modifySysTimeButtonClicked\0otaButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_setUp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    0,   68,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,
      12,    0,   70,    2, 0x08 /* Private */,
      13,    0,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void setUp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<setUp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->focusInEvent((*reinterpret_cast< QFocusEvent*(*)>(_a[1]))); break;
        case 2: _t->setIpButtonClicked(); break;
        case 3: _t->setDeviceNumberButtonClicked(); break;
        case 4: _t->queryDayConsumeRecordButtonClicked(); break;
        case 5: _t->queryCollectRecordButtonClicked(); break;
        case 6: _t->setConsumeModeButtonClicked(); break;
        case 7: _t->modifySysTimeButtonClicked(); break;
        case 8: _t->otaButtonClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject setUp::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_setUp.data,
    qt_meta_data_setUp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *setUp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *setUp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_setUp.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int setUp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

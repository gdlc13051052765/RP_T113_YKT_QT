/****************************************************************************
** Meta object code from reading C++ file 'mainconsumeinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainconsumeinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainconsumeinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mainConsumeInterface_t {
    QByteArrayData data[13];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mainConsumeInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mainConsumeInterface_t qt_meta_stringdata_mainConsumeInterface = {
    {
QT_MOC_LITERAL(0, 0, 20), // "mainConsumeInterface"
QT_MOC_LITERAL(1, 21, 15), // "mainConsumeslot"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 19), // "updateSysTimeHandle"
QT_MOC_LITERAL(4, 58, 22), // "twinkleTimerTimeHandle"
QT_MOC_LITERAL(5, 81, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(6, 97, 10), // "QKeyEvent*"
QT_MOC_LITERAL(7, 108, 2), // "ev"
QT_MOC_LITERAL(8, 111, 28), // "Communicate_Msg_QT_Go_Handle"
QT_MOC_LITERAL(9, 140, 20), // "udp_client_read_data"
QT_MOC_LITERAL(10, 161, 20), // "getConsumeModeHandle"
QT_MOC_LITERAL(11, 182, 23), // "Handle_Rfal_Value_Event"
QT_MOC_LITERAL(12, 206, 3) // "str"

    },
    "mainConsumeInterface\0mainConsumeslot\0"
    "\0updateSysTimeHandle\0twinkleTimerTimeHandle\0"
    "keyReleaseEvent\0QKeyEvent*\0ev\0"
    "Communicate_Msg_QT_Go_Handle\0"
    "udp_client_read_data\0getConsumeModeHandle\0"
    "Handle_Rfal_Value_Event\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mainConsumeInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   57,    2, 0x08 /* Private */,
       4,    0,   58,    2, 0x08 /* Private */,
       5,    1,   59,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,
      10,    1,   64,    2, 0x0a /* Public */,
      11,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void mainConsumeInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mainConsumeInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mainConsumeslot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->updateSysTimeHandle(); break;
        case 2: _t->twinkleTimerTimeHandle(); break;
        case 3: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 4: _t->Communicate_Msg_QT_Go_Handle(); break;
        case 5: _t->udp_client_read_data(); break;
        case 6: _t->getConsumeModeHandle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->Handle_Rfal_Value_Event((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (mainConsumeInterface::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mainConsumeInterface::mainConsumeslot)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mainConsumeInterface::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_mainConsumeInterface.data,
    qt_meta_data_mainConsumeInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mainConsumeInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainConsumeInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mainConsumeInterface.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int mainConsumeInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void mainConsumeInterface::mainConsumeslot(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

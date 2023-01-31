/****************************************************************************
** Meta object code from reading C++ file 'mutexdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mutexdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mutexdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mutexDialog_t {
    QByteArrayData data[11];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mutexDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mutexDialog_t qt_meta_stringdata_mutexDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "mutexDialog"
QT_MOC_LITERAL(1, 12, 11), // "SigExternal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "str"
QT_MOC_LITERAL(4, 29, 15), // "SigExternalJson"
QT_MOC_LITERAL(5, 45, 15), // "SigInsideDelier"
QT_MOC_LITERAL(6, 61, 5), // "char*"
QT_MOC_LITERAL(7, 67, 26), // "Receive_MainWindow_Handler"
QT_MOC_LITERAL(8, 94, 3), // "msg"
QT_MOC_LITERAL(9, 98, 16), // "SlotInsideDelier"
QT_MOC_LITERAL(10, 115, 12) // "slotReadData"

    },
    "mutexDialog\0SigExternal\0\0str\0"
    "SigExternalJson\0SigInsideDelier\0char*\0"
    "Receive_MainWindow_Handler\0msg\0"
    "SlotInsideDelier\0slotReadData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mutexDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   53,    2, 0x08 /* Private */,
       9,    1,   56,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QJsonArray,    3,
    QMetaType::Void, 0x80000000 | 6,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void,

       0        // eod
};

void mutexDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mutexDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigExternal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->SigExternalJson((*reinterpret_cast< QJsonArray(*)>(_a[1]))); break;
        case 2: _t->SigInsideDelier((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 3: _t->Receive_MainWindow_Handler((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SlotInsideDelier((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 5: _t->slotReadData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (mutexDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mutexDialog::SigExternal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (mutexDialog::*)(QJsonArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mutexDialog::SigExternalJson)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (mutexDialog::*)(char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mutexDialog::SigInsideDelier)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mutexDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_mutexDialog.data,
    qt_meta_data_mutexDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mutexDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mutexDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mutexDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int mutexDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void mutexDialog::SigExternal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mutexDialog::SigExternalJson(QJsonArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mutexDialog::SigInsideDelier(char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

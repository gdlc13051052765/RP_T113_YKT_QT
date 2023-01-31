/****************************************************************************
** Meta object code from reading C++ file 'udp_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../udp_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udp_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UDP_THREAD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UDP_THREAD[] = {
    "UDP_THREAD\0\0rfal_Receive_Handler(QString)\0"
};

void UDP_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UDP_THREAD *_t = static_cast<UDP_THREAD *>(_o);
        switch (_id) {
        case 0: _t->rfal_Receive_Handler((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UDP_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UDP_THREAD::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_UDP_THREAD,
      qt_meta_data_UDP_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UDP_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UDP_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UDP_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UDP_THREAD))
        return static_cast<void*>(const_cast< UDP_THREAD*>(this));
    return QThread::qt_metacast(_clname);
}

int UDP_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'mytcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mytcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyTcpServer_t {
    QByteArrayData data[8];
    char stringdata[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTcpServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTcpServer_t qt_meta_stringdata_MyTcpServer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyTcpServer"
QT_MOC_LITERAL(1, 12, 4), // "code"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "picture"
QT_MOC_LITERAL(4, 26, 14), // "decodedPicture"
QT_MOC_LITERAL(5, 41, 13), // "newConnection"
QT_MOC_LITERAL(6, 55, 17), // "messageDispatcher"
QT_MOC_LITERAL(7, 73, 3) // "msg"

    },
    "MyTcpServer\0code\0\0picture\0decodedPicture\0"
    "newConnection\0messageDispatcher\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTcpServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   40,    2, 0x0a /* Public */,
       6,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    1,
    QMetaType::Void, QMetaType::QPixmap,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void MyTcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyTcpServer *_t = static_cast<MyTcpServer *>(_o);
        switch (_id) {
        case 0: _t->code((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->picture((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 2: _t->newConnection(); break;
        case 3: _t->messageDispatcher((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyTcpServer::*_t)(const QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpServer::code)) {
                *result = 0;
            }
        }
        {
            typedef void (MyTcpServer::*_t)(const QPixmap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyTcpServer::picture)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MyTcpServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyTcpServer.data,
      qt_meta_data_MyTcpServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyTcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyTcpServer.stringdata))
        return static_cast<void*>(const_cast< MyTcpServer*>(this));
    return QObject::qt_metacast(_clname);
}

int MyTcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MyTcpServer::code(const QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyTcpServer::picture(const QPixmap _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'chatdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../chatdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_chatDialog_t {
    QByteArrayData data[15];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_chatDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_chatDialog_t qt_meta_stringdata_chatDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "chatDialog"
QT_MOC_LITERAL(1, 11, 19), // "SIG_sendChatMessage"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 2), // "id"
QT_MOC_LITERAL(4, 35, 4), // "text"
QT_MOC_LITERAL(5, 40, 12), // "SIG_sendFile"
QT_MOC_LITERAL(6, 53, 4), // "path"
QT_MOC_LITERAL(7, 58, 19), // "SIG_sendFileBlockRq"
QT_MOC_LITERAL(8, 78, 8), // "friendId"
QT_MOC_LITERAL(9, 87, 9), // "timestamp"
QT_MOC_LITERAL(10, 97, 18), // "on_pb_send_clicked"
QT_MOC_LITERAL(11, 116, 22), // "on_pb_openFile_clicked"
QT_MOC_LITERAL(12, 139, 32), // "on_tb_fileInfo_cellDoubleClicked"
QT_MOC_LITERAL(13, 172, 3), // "row"
QT_MOC_LITERAL(14, 176, 6) // "column"

    },
    "chatDialog\0SIG_sendChatMessage\0\0id\0"
    "text\0SIG_sendFile\0path\0SIG_sendFileBlockRq\0"
    "friendId\0timestamp\0on_pb_send_clicked\0"
    "on_pb_openFile_clicked\0"
    "on_tb_fileInfo_cellDoubleClicked\0row\0"
    "column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chatDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    2,   49,    2, 0x06 /* Public */,
       7,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   59,    2, 0x08 /* Private */,
      11,    0,   60,    2, 0x08 /* Private */,
      12,    2,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,

       0        // eod
};

void chatDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        chatDialog *_t = static_cast<chatDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_sendChatMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->SIG_sendFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->SIG_sendFileBlockRq((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->on_pb_send_clicked(); break;
        case 4: _t->on_pb_openFile_clicked(); break;
        case 5: _t->on_tb_fileInfo_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (chatDialog::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&chatDialog::SIG_sendChatMessage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (chatDialog::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&chatDialog::SIG_sendFile)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (chatDialog::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&chatDialog::SIG_sendFileBlockRq)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject chatDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_chatDialog.data,
      qt_meta_data_chatDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *chatDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chatDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_chatDialog.stringdata0))
        return static_cast<void*>(const_cast< chatDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int chatDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void chatDialog::SIG_sendChatMessage(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void chatDialog::SIG_sendFile(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void chatDialog::SIG_sendFileBlockRq(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

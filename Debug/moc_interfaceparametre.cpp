/****************************************************************************
** Meta object code from reading C++ file 'interfaceparametre.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../interfaceparametre.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfaceparametre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InterfaceParametre_t {
    QByteArrayData data[6];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InterfaceParametre_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InterfaceParametre_t qt_meta_stringdata_InterfaceParametre = {
    {
QT_MOC_LITERAL(0, 0, 18), // "InterfaceParametre"
QT_MOC_LITERAL(1, 19, 9), // "ajoutEtat"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 21), // "EnregistrerParametres"
QT_MOC_LITERAL(4, 52, 17), // "ChargerParametres"
QT_MOC_LITERAL(5, 70, 17) // "ValiderParametres"

    },
    "InterfaceParametre\0ajoutEtat\0\0"
    "EnregistrerParametres\0ChargerParametres\0"
    "ValiderParametres"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InterfaceParametre[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void InterfaceParametre::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InterfaceParametre *_t = static_cast<InterfaceParametre *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ajoutEtat(); break;
        case 1: _t->EnregistrerParametres(); break;
        case 2: _t->ChargerParametres(); break;
        case 3: _t->ValiderParametres(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject InterfaceParametre::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InterfaceParametre.data,
      qt_meta_data_InterfaceParametre,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InterfaceParametre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceParametre::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceParametre.stringdata0))
        return static_cast<void*>(const_cast< InterfaceParametre*>(this));
    return QWidget::qt_metacast(_clname);
}

int InterfaceParametre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

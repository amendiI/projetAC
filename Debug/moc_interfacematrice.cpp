/****************************************************************************
** Meta object code from reading C++ file 'interfacematrice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../interfacematrice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfacematrice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InterfaceMatrice_t {
    QByteArrayData data[17];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InterfaceMatrice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InterfaceMatrice_t qt_meta_stringdata_InterfaceMatrice = {
    {
QT_MOC_LITERAL(0, 0, 16), // "InterfaceMatrice"
QT_MOC_LITERAL(1, 17, 19), // "actualiserAffichage"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(4, 56, 4), // "item"
QT_MOC_LITERAL(5, 61, 8), // "Afficher"
QT_MOC_LITERAL(6, 70, 15), // "LancerIterateur"
QT_MOC_LITERAL(7, 86, 10), // "ChangerRec"
QT_MOC_LITERAL(8, 97, 5), // "state"
QT_MOC_LITERAL(9, 103, 20), // "ChangerNbGenerations"
QT_MOC_LITERAL(10, 124, 3), // "val"
QT_MOC_LITERAL(11, 128, 17), // "NbGenerationsFini"
QT_MOC_LITERAL(12, 146, 12), // "NbIterations"
QT_MOC_LITERAL(13, 159, 9), // "FaireStop"
QT_MOC_LITERAL(14, 169, 14), // "RecupererTemps"
QT_MOC_LITERAL(15, 184, 1), // "t"
QT_MOC_LITERAL(16, 186, 17) // "ValiderTempsFinal"

    },
    "InterfaceMatrice\0actualiserAffichage\0"
    "\0QTableWidgetItem*\0item\0Afficher\0"
    "LancerIterateur\0ChangerRec\0state\0"
    "ChangerNbGenerations\0val\0NbGenerationsFini\0"
    "NbIterations\0FaireStop\0RecupererTemps\0"
    "t\0ValiderTempsFinal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InterfaceMatrice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    1,   69,    2, 0x0a /* Public */,
       9,    1,   72,    2, 0x0a /* Public */,
      11,    0,   75,    2, 0x0a /* Public */,
      12,    0,   76,    2, 0x0a /* Public */,
      13,    0,   77,    2, 0x0a /* Public */,
      14,    1,   78,    2, 0x0a /* Public */,
      16,    0,   81,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,

       0        // eod
};

void InterfaceMatrice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InterfaceMatrice *_t = static_cast<InterfaceMatrice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->actualiserAffichage((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->Afficher(); break;
        case 2: _t->LancerIterateur(); break;
        case 3: _t->ChangerRec((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->ChangerNbGenerations((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->NbGenerationsFini(); break;
        case 6: _t->NbIterations(); break;
        case 7: _t->FaireStop(); break;
        case 8: _t->RecupererTemps((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->ValiderTempsFinal(); break;
        default: ;
        }
    }
}

const QMetaObject InterfaceMatrice::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InterfaceMatrice.data,
      qt_meta_data_InterfaceMatrice,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InterfaceMatrice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceMatrice::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InterfaceMatrice.stringdata0))
        return static_cast<void*>(const_cast< InterfaceMatrice*>(this));
    return QWidget::qt_metacast(_clname);
}

int InterfaceMatrice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

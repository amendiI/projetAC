#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QVBoxLayout>
#include "interfaceparametre.h"
#include "interfaceregle.h"

class Interface : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout *layout;
    InterfaceParametre *Ip;
    InterfaceRegle *Ir;

public:
    explicit Interface(QWidget *parent = 0);

signals:

public slots:
};

#endif // INTERFACE_H

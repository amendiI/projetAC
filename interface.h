#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QVBoxLayout>
#include "interfaceparametre.h"
#include "interfaceregle.h"
#include "interfacematrice.h"
#include "Jeu_de_Regle_nt.h"
#include "Jeu_de_Regle.h"

class Interface : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout *layout;
    InterfaceParametre *Ip;
    InterfaceRegle *Ir;
    InterfaceMatrice * Im;
    Jeu_de_Regle_nt * Jdr_nt;
    Jeu_de_Regle* Jdr;

public:
    explicit Interface(QWidget *parent = 0);

signals:

public slots:
};

#endif // INTERFACE_H

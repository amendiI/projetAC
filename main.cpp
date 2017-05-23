#include "mainwindow.h"
#include <QApplication>

#include "interfacematrice.h"
#include "iterateur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Matrice* matrix = new Matrice(25,2);
    Iterateur* worker = new Iterateur(matrix);

    //InterfaceMatrice *inter = new InterfaceMatrice();

    InterfaceMatrice *inter = new InterfaceMatrice(matrix,worker);
    inter->show();

    return a.exec();
}
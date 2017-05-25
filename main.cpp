#include <QApplication>

#include "interfacematrice.h"
#include "iterateur.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	srand((unsigned)time(NULL));
    Interface *I = new Interface();
    I->show();
/*
    Matrice* matrix = new Matrice(10,2);
    Iterateur* worker = new Iterateur();

    //InterfaceMatrice *inter = new InterfaceMatrice();

    InterfaceMatrice *inter = new InterfaceMatrice(matrix,worker);
    inter->show();
*/
    return a.exec();
}

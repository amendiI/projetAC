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

    return a.exec();
}

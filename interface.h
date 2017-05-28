#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QVBoxLayout>
<<<<<<< HEAD
=======
#include <QDesktopWidget>
#include <QApplication>
>>>>>>> a993c6265709d3f6563d501e9618de2c5f73de04

#include "interfaceparametre.h"
#include "interfaceregle.h"
#include "interfacematrice.h"
#include "Jeu_de_Regle_nt.h"
#include "iterateur.h"

class Interface : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout *layout;
	QHBoxLayout *layoutB;
    QHBoxLayout *layoutH;
    InterfaceParametre *interP;
    InterfaceRegle *interR;
    InterfaceMatrice * interM;
	QPushButton * quitterBouton;
	QPushButton * reinitBouton;
    QPushButton *chargerBouton;
    QPushButton *enregistrerBouton;

    Jeu_de_Regle* jdr;
    Matrice * matrix;
    Iterateur * worker;


public:
    explicit Interface(QWidget *parent = 0);

public slots :
    void recevePara(unsigned int size,unsigned short nbPS,int v,vector<EtatType*>* d);
    void Reinitialisation();
	void Charger();
	void Enregistrer();
	void InterROK();
};

#endif // INTERFACE_H

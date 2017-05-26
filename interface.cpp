#include "interface.h"

void Interface::Reinitialisation() {
	/*
	delete Ip;
	delete Jdr_nt;
	delete Jdr;

	Jdr_nt = new Jeu_de_Regle_nt();
	Jdr = new Jeu_de_Regle();
	Ip = new InterfaceParametre(layoutH, Jdr, Jdr_nt, layout);
	Ip->show();
	layout->addWidget(Ip);*/
}

void Interface::recevePara(unsigned int size,unsigned short nbPS,int v,vector<EtatType*>* d){
    matrix=new Matrice(size,nbPS,0);
    interR->setTableauEtats(d);
    interM->setTableauEtats(d);
    interM->setMatrice(matrix);
    worker->setMatrice(matrix);
    if(v==1)matrix->setMoore(true);
    interR->getJDR_nt()->set_val(size,nbPS,v);

    interM->Afficher();
    interM->update();
    interR->update();
    layoutH->update();
    interM->repaint();
    interR->repaint();
}

Interface::Interface(QWidget *parent) : QWidget(parent)
{
    matrix=NULL;
    worker=new Iterateur();
    jdr = new Jeu_de_Regle();
    worker->setJDR(jdr);

    interP=new InterfaceParametre();
    interR=new InterfaceRegle();
    interM=new InterfaceMatrice();
    /*interP->setParent(this);
    interR->setParent(this);
    interM->setParent(this);
*/
    reinitBouton = new QPushButton("Reinitialiser");
    layoutH = new QHBoxLayout(this);
    layout = new QVBoxLayout();
    layoutH->addLayout(layout);
    reinitBouton->show();
    layout->addWidget(reinitBouton);
    layout->addWidget(interP);
    layout->addWidget(interR);
    layoutH->addWidget(interM);

    interP->setVisible(true);
    interR->setVisible(true);
    interM->setVisible(true);


    interR->setJDR(jdr);
    interM->setIterateur(worker);

    QObject::connect(interP,SIGNAL(validP(unsigned int,unsigned short,int,vector<EtatType*>*)),this,SLOT(recevePara(uint,unsigned short,int,vector<EtatType*>*)));
    //QObject::connect(reinitBouton, SIGNAL(clicked()), this, SLOT(Reinitialisation()));
}

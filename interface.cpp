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

void  Interface::Charger() {

	QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers Texte (*.txt)");

}

void Interface::Enregistrer() {
	QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Fichier Texte(*.txt *.ol *.fe)");
	QFile file(fichier);
	
	// Ouverture en écriture seule et petites optimisations avec QIODevice::Text
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	return;
	// On écrit à l'emplacement du fichier en mettant le contenu de la zone de texte dedans
	QTextStream out(&file);


	out << interP->getTaille() << ";" << endl;
	out << interP->getVoisinage() << ";" << endl;
	out << interP->getNbEtats() << ";" << endl;

	
	for (int i = 0; i < interP->getNbEtats(); i++)
	{
		out << interP->getNomEtat(i) << "," << interP->getColorStrEtat(i) << ";" << endl;
	}

	for (int i = 0; i < interR->getNbRegles(); i++) 
	{
		out << interR->getDepartRegle(i) << "," << interR->getArriveeRegle(i) << "," << interR->getProbaRegle(i) << "," << interR->getProbaArriveeRegle(i) << ",(";
		out << interR->getVoisinage(i, 0);
		for (int j = 1; j < interP->getNbEtats(); j++) 
		{
			out << "," << interR->getVoisinage(i,j);
		}
		out << ");" << endl;
	}

	file.close();
}

void Interface::InterROK()
{
	enregistrerBouton->setDisabled(false);
    interM->Play->setEnabled(true);
    interM->Infini->setEnabled(true);
    interM->PlayN->setEnabled(true);
}

void Interface::recevePara(unsigned int size,unsigned short nbPS,int v,vector<EtatType*>* d){
    matrix=new Matrice(size,nbPS,0);
    interR->setTableauEtats(d);
    interM->setTableauEtats(d);
    interM->setMatrice(matrix);
    interM->Chargement->setEnabled(true);
    interM->Enregistrer->setEnabled(true);
    interM->AleaBouton->setEnabled(true);
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

    reinitBouton = new QPushButton("Reinitialiser");
	chargerBouton = new QPushButton("Charger depuis...");
	enregistrerBouton = new QPushButton("Enregistrer sous...");

    layoutH = new QHBoxLayout();
    layout = new QVBoxLayout();
	layoutV = new QVBoxLayout(this);
	layoutV->addLayout(layoutH);
    layoutH->addLayout(layout);
    
    layout->addWidget(reinitBouton);
	layout->addWidget(chargerBouton);
    layout->addWidget(interP);
    layout->addWidget(interR);
	layout->addWidget(enregistrerBouton);
    layoutH->addWidget(interM);

	enregistrerBouton->setDisabled(true);

    interR->setJDR(jdr);
    interM->setIterateur(worker);

    QObject::connect(interP,SIGNAL(validP(unsigned int,unsigned short,int,vector<EtatType*>*)),this,SLOT(recevePara(uint,unsigned short,int,vector<EtatType*>*)));
    //QObject::connect(reinitBouton, SIGNAL(clicked()), this, SLOT(Reinitialisation()));
	QObject::connect(chargerBouton, SIGNAL(clicked()), this, SLOT(Charger()));
	QObject::connect(enregistrerBouton, SIGNAL(clicked()), this, SLOT(Enregistrer()));
	QObject::connect(interR, SIGNAL(validerInterR()), this, SLOT(InterROK()));
}

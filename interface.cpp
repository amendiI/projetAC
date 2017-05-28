#include "interface.h"



void  Interface::Charger() {

	QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers Texte (*.txt)");
	QFile file(fichier);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);
	QString str;
	bool ok = true;
	int nbEtats;

	interP->setTailleMatrice(in.readLine().split(';')[0].toInt(&ok, 10));
	interP->setTypeVoisinage(in.readLine().split(';')[0].toInt());
	nbEtats = in.readLine().split(';')[0].toInt();

	for (int i = 0; i < nbEtats; i++)
	{
		str = in.readLine();
		QString c = str.split(',')[1]; c .chop(1);
		interP->ajouterEtatChargement(str.split(',')[0], c);
	}
	interP->ValiderParametres();

	for (str = in.readLine(); !str.isEmpty(); str = in.readLine()) 
	{
		QString str2;
		vector<QString> R;
		str2 = str.split('(')[1];
		str2.chop(2);
		for (int i = 0; i < nbEtats; i++)
		{
			R.push_back(str2.split(',')[i]);
		}
		interR->ajouterRegleChargement(str.split(',')[0].toInt(), str.split(',')[1].toInt(), str.split(',')[2].toInt(), str.split(',')[3].toInt(), R);
	}
	file.close();
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
    if(v==0)matrix->setMoore(true);
    interR->getJDR_nt()->set_val(nbPS,v);

    interM->Afficher();
    interM->update();
    interR->update();
    layoutH->update();
    interM->repaint();
    interR->repaint();
	interR->griser(false);
}

void Interface::Reinitialisation()
{
	interM->reinit();
	/*interR->reinit();
	interP->reinit();

	delete matrix; matrix = NULL;
	delete worker; worker = new Iterateur(); worker->setJDR(jdr);
	delete jdr;  jdr = new Jeu_de_Regle();

	interM->griser(true);
	interR->griser(true);
	*/
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

	quitterBouton = new QPushButton("Quitter");
    reinitBouton = new QPushButton("Reinitialiser");
	chargerBouton = new QPushButton("Charger depuis...");
	enregistrerBouton = new QPushButton("Enregistrer sous...");

    layoutH = new QHBoxLayout(this);
    layout = new QVBoxLayout();
	layoutB = new QHBoxLayout();
	layout->addLayout(layoutB);
    layoutH->addLayout(layout);
    
	layoutB->addWidget(quitterBouton);
    layoutB->addWidget(reinitBouton);
	layout->addWidget(chargerBouton);
	layout->addWidget(enregistrerBouton);
    layout->addWidget(interP);
    layout->addWidget(interR);
    layoutH->addWidget(interM);

	enregistrerBouton->setDisabled(true);

    interR->setJDR(jdr);
    interM->setIterateur(worker);

    QObject::connect(interP,SIGNAL(validP(unsigned int,unsigned short,int,vector<EtatType*>*)),this,SLOT(recevePara(uint,unsigned short,int,vector<EtatType*>*)));
    QObject::connect(reinitBouton, SIGNAL(clicked()), this, SLOT(Reinitialisation()));
	QObject::connect(chargerBouton, SIGNAL(clicked()), this, SLOT(Charger()));
	QObject::connect(enregistrerBouton, SIGNAL(clicked()), this, SLOT(Enregistrer()));
	QObject::connect(interR, SIGNAL(validerInterR()), this, SLOT(InterROK()));
	QObject::connect(quitterBouton, SIGNAL(clicked()), qApp, SLOT(quit())); // connecte le bouton à la fonction quit

}

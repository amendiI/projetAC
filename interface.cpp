#include "interface.h"



void  Interface::Charger() {

    QString fichier = QFileDialog::getOpenFileName(this, "Charger des paramètres", QString(), "Fichiers Texte (*.txt)");
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

void Interface::LoadingMatrice(){
    Matrice* matrix2;
    QString chemin = QFileDialog::getOpenFileName(this, "Charger une Matrice", QString(), "Fichier Texte(*.matrice)");
    if (chemin == NULL) return;
    QString textFichier;
    QFile fichier(chemin);

    //TODO le chemin peut etre passé en paramètre pour etre fourni par un explorateur de fichiers
    if(!fichier.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    //le fichier ne s'est pas ouvert
    textFichier=fichier.readAll();
    fichier.close();
    QRegExp rx("^(\\d+);(\\d+);(\\d+);\\{(\\d+)(?:,\\d+)*\\}$");
    if(rx.indexIn(textFichier) != 0) return;
    //mauvaise syntaxe de fichier !
    bool tmpB=true;
    unsigned short tmp, size=rx.cap(3).toUInt(&tmpB,10), nbPS=rx.cap(2).toUShort(&tmpB,10);
    if(!tmpB)return;
    //erreur de conversion
    matrix2 = new Matrice(size,nbPS);
    textFichier.remove(0,textFichier.indexOf("{"));
    rx.setPattern("(\\d+)");
    unsigned int cmpt=0,stop=matrix2->getNbCells();
    int pos=0;
    while((pos=rx.indexIn(textFichier,pos)) != -1 && cmpt<stop){
        tmp=rx.cap(1).toUShort(&tmpB,10);
        if(tmp>=nbPS)return;
        //valeur incorrecte dans le fichier
        matrix2->getCell(cmpt)->setValue(tmp);
        pos+=rx.matchedLength();
        cmpt++;
    }
    if(!tmpB)return;
    //erreur de conversion
    delete matrix;
    matrix = matrix2;
    worker->setMatrice(matrix);
    interM->setMatrice(matrix);
    interM->Afficher();
}

void Interface::Enregistrer() {
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer les Paramètres", QString(), "Fichier Texte(*.txt *.ol *.fe)");
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

void Interface::RecordingMatrice(){   //store only one state (etat courrant)
    QString text="";
        text+=QString::number(matrix->getNbDimensions());
        text+=";";
        text+=QString::number(matrix->getNbPossibleStates());
        text+=";";
        text+=QString::number(matrix->getSize());
        text+=";";
    QString file = QFileDialog::getSaveFileName(this, "Enregistrer la Matrice", QString(), "Fichier Texte(*.matrice)");
    if(file == NULL) return;
    //TODO le chemin peut etre passé en paramètre pour etre fourni par un explorateur de fichiers
    QRegExp rx("*.matrice"); QRegExp rx2("*.*"); rx2.setPatternSyntax(QRegExp::Wildcard);
    rx.setPatternSyntax(QRegExp::Wildcard);
    if (!rx.exactMatch(file) && rx2.exactMatch(file)) return;
    else if (!rx.exactMatch(file)) file.push_back(".matrice");
    QFile fichier(file);
    if(!fichier.open(QIODevice::WriteOnly|QIODevice::Text)) return;//le fichier ne s'est pas ouvert
    unsigned int i=0;
    text+="{";
    text+=QString::number(matrix->getCell(i)->getValue());
    for(i=1;i<matrix->getNbCells();i++){
        text+=",";
        text+=QString::number(matrix->getCell(i)->getValue());
    }
    text+="}";
    QTextStream flux(&fichier);
    flux << text;
    fichier.close();
    return;
}

void Interface::loadTransitionTable(){
    int tmp=matrix->isMoore()?10:6;
    unsigned short** transitionTable=new unsigned short*[maxTransition];
    for(int i=0;i<maxTransition;i++){
        transitionTable[i]=new unsigned short[tmp];
        for(int j=0;j<tmp;j++)transitionTable[i][j]=0;
    }
    QString chemin = QFileDialog::getOpenFileName(this, "Charger une Table de Transition", QString(), "Fichier Texte(*.txt *.ol *.fe)");
    QString textFichier;
    if(chemin==NULL)return;
    QFile fichier(chemin);
    if(!fichier.open(QIODevice::ReadOnly|QIODevice::Text))return;
    //le fichier ne s'est pas ouvert
    textFichier=fichier.readAll();
    fichier.close();
    QRegExp rx;
    if(matrix->isMoore()){
        rx.setPattern("(?:(\\d,\\d,\\d,\\d,\\d,\\d,\\d,\\d,\\d,\\d);)+\n");
    }
    else{
        rx.setPattern("(?:(\\d,\\d,\\d,\\d,\\d,\\d);)+\n");
    }
    QRegExp rx2("(\\d)");
    QString trans;
    if(rx.indexIn(textFichier) != 0) return;
    //mauvaise syntaxe de fichier !
    bool tmpB=true;
    int c2=0,pos=0;
    while((pos=rx.indexIn(textFichier,pos))!=-1){
        trans=rx.cap(1);
        int c=0,pos2=0;
        while((pos2=rx2.indexIn(trans,pos2))!=-1){
            transitionTable[c2][c]=rx2.cap(1).toUShort(&tmpB,10);
            pos2+=rx2.matchedLength();
            c++;
        }
        pos+=rx.matchedLength();
        c2++;
    }
    if(!tmpB)return;
    worker->setTransitions(transitionTable);
}


void Interface::InterROK()
{
	enregistrerBouton->setDisabled(false);
    interM->Play->setEnabled(true);
    interM->Infini->setEnabled(true);
    interM->PlayN->setEnabled(true);
}

void Interface::griserChargement()
{
	chargerBouton->setDisabled(true);
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
	reinitBouton->setEnabled(true);
}

void Interface::Reinitialisation()
{
	interM->reinit();
	interR->reinit();
	interP->reinit();

	matrix = NULL;
	delete worker; worker = new Iterateur(); worker->setJDR(jdr);

	interM->griser(true);
	interR->griser(true);
	interP->griser(false);
	chargerBouton->setDisabled(false);
	reinitBouton->setDisabled(true);
}

void Interface::setIteratorAppli(){
    worker->setApplication(interM->VersionIte->value());
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
	reinitBouton->setDisabled(true);

    interR->setJDR(jdr);
    interM->setIterateur(worker);

    QObject::connect(interP,SIGNAL(validP(unsigned int,unsigned short,int,vector<EtatType*>*)),this,SLOT(recevePara(uint,unsigned short,int,vector<EtatType*>*)));
    QObject::connect(reinitBouton, SIGNAL(clicked()), this, SLOT(Reinitialisation()));
	QObject::connect(chargerBouton, SIGNAL(clicked()), this, SLOT(Charger()));
	QObject::connect(enregistrerBouton, SIGNAL(clicked()), this, SLOT(Enregistrer()));
	QObject::connect(interR, SIGNAL(validerInterR()), this, SLOT(InterROK()));
	QObject::connect(quitterBouton, SIGNAL(clicked()), qApp, SLOT(quit())); // connecte le bouton à la fonction quit
	QObject::connect(interP, SIGNAL(ajouterUn()), this, SLOT(griserChargement()));
    QObject::connect(interM->Chargement, SIGNAL(clicked()), this, SLOT(LoadingMatrice()));
    QObject::connect(interM->Enregistrer, SIGNAL(clicked()), this, SLOT(RecordingMatrice()));
    QObject::connect(interM->ChargementTransition, SIGNAL(clicked()), this, SLOT(loadTransitionTable()));
    QObject::connect(interM->ValiderAppliIte, SIGNAL(clicked()), this, SLOT(setIteratorAppli()));

}

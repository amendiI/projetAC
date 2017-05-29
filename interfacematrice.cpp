#include "interfacematrice.h"

// FONCTION STATIQUE //




void InterfaceMatrice::setMatrice(Matrice *matrice)
{
    if(matrice == NULL)return;
    matcour = matrice;
    unsigned int i,j;
    bool ok = true;
    int val;

    //Initialisation grilleCellule avec taille matrice
    grilleCellule->setRowCount(matcour->getSize());
    grilleCellule->setColumnCount(matcour->getSize());

    //Remplissage des cellules de grilleCellule avec les valeurs de la matrice
    for(i=0; i<matcour->getSize(); i++)
    {
        for(j=0; j<matcour->getSize(); j++)
        {
            itemCellule = new QTableWidgetItem(QString::number(matcour->getVal(i,j)));
            itemCellule->setTextAlignment(Qt::AlignCenter);
            val = itemCellule->text().toInt(&ok,10);
            itemCellule->setBackground(*brushEtats.at(val));
            grilleCellule->setItem(i,j,itemCellule);
        }
    }

    QObject::connect(grilleCellule,SIGNAL(cellChanged(int,int)),this,SLOT(ChangerCellule(int,int)));

    //Définir la taille des cellules
    int taille = matcour->getSize();
    int sizeCell = 800/taille;

    for(int c=0;c<grilleCellule->columnCount();c++)
    {
        grilleCellule->setColumnWidth(c,sizeCell);
        grilleCellule->setRowHeight(c,sizeCell);
    }

    setMaximumSize(400+taille*sizeCell+3,20+taille*sizeCell+3);

    //Resize de grilleCellule dans la fenêtre
    grilleCellule->setFixedSize(sizeCell*taille+3,sizeCell*taille+3);
    grilleCellule->horizontalHeader()->hide();
    grilleCellule->verticalHeader()->hide();
}

void InterfaceMatrice::setIterateur(Iterateur *iterateur)
{
    if(iterateur != NULL)
        travailleur = iterateur;
    travailleur->setMatrice(matcour);
}

void InterfaceMatrice::setTableauEtats(vector<EtatType *> *type)
{
    if(type == NULL)return;
        Etats = type;

    //Initialisation des couleurs possibles des cellules
    for(unsigned int i=0; i<Etats->size();i++)
    {
        QBrush* B = new QBrush(Etats->at(i)->GetQColor());
        brushEtats.push_back(B);
    }

    for (unsigned int i = 0; i <  Etats->size(); i++)
    {
        QLabel * L = new QLabel();
        L->setText(Etats->at(i)->GetNom());
        QSpinBox *S = new QSpinBox();
        S->setRange(0, 100);
        QLabel * L2 = new QLabel();
        L2->setText("%");
        tabAlea.push_back(S);
		layoutGridMA->addWidget(L,i, 0);
		layoutGridMA->addWidget(S,i,1);
		layoutGridMA->addWidget(L2,i,2);
    }
}



// PUBLIC SLOTS //
void InterfaceMatrice::ChangerCellule(int row, int column)
{
    QTableWidgetItem* item = grilleCellule->item(row,column);
    bool ok = true;
    if(!(item->text().toUInt(&ok,10) < Etats->size()))
    {
        item->setText("0");
    }
    matcour->setVal(item->row(), item->column(),item->text().toUShort(&ok,10));
    item->setBackground(*brushEtats.at(item->text().toInt(&ok,10)));
}

void InterfaceMatrice::Afficher()
{
    unsigned int i,j;
    QTableWidgetItem* item;
    int val;
    bool ok = true;

    for(i=0;i<matcour->getSize();i++)
    {
        for(j=0;j<matcour->getSize();j++)
        {
            item = grilleCellule->item(i,j);
            item->setText(QString::number(matcour->getVal(i,j)));
            val = item->text().toInt(&ok,10);
            item->setBackground(*brushEtats.at(val));
        }
    }
}

void InterfaceMatrice::LancerIterateur()
{
    unsigned int i,j;
    QObject::disconnect(grilleCellule,SIGNAL(cellChanged(int,int)),this,SLOT(ChangerCellule(int,int)));

    travailleur->transformMatrice();
    for(i=0;i<matcour->getSize();i++)
    {
        for(j=0;j<matcour->getSize();j++)
        {
            itemCellule->setText(QString::number(matcour->getVal(i,j)));
        }
    }
    Afficher();
    QObject::connect(grilleCellule,SIGNAL(cellChanged(int,int)),this,SLOT(ChangerCellule(int,int)));
}



void InterfaceMatrice::InfiniIterations()
{
    timer1 = new QTimer();
    QObject::connect(timer1,SIGNAL(timeout()),this,SLOT(LancerIterateur()));
    timer1->start(tempsfinal);
    StopInf->setEnabled(true);
    Infini->setDisabled(true);
    PlayN->setDisabled(true);
    StopN->setDisabled(true);
    nbSlider->setDisabled(true);
    ValiderNbGen->setDisabled(true);
    tempsIteration->setDisabled(true);
    ValiderTemps->setDisabled(true);
    AleaBouton->setDisabled(true);
    Play->setDisabled(true);
}

void InterfaceMatrice::StopInfini()
{
    timer1->stop();

    Infini->setEnabled(true);
    PlayN->setEnabled(true);
    StopN->setEnabled(true);
    nbSlider->setEnabled(true);
    ValiderNbGen->setEnabled(true);
    tempsIteration->setEnabled(true);
    ValiderTemps->setEnabled(true);
    AleaBouton->setEnabled(true);
    Play->setEnabled(true);
}

void InterfaceMatrice::RecupererTemps(int t)
{
    if(t < 250)
        temps = 250;
    else
        temps = t;         //1000ms = 1s.
}

void InterfaceMatrice::ValiderTempsFinal()
{
    if(temps < 250)
    {
        tempsfinal = 250;
    }
    else
    {
        tempsfinal = temps;
        tempsIteration->setDisabled(true);
        ValiderTemps->setDisabled(true);
    }
}

void InterfaceMatrice::ChangerNbGenerations(int val)
{
    if(val == 0)
        nbGenerations = 1;
    else
        nbGenerations = val;
}

void InterfaceMatrice::NbGenerationsFini()
{
    if(nbGenerations == 0)
        NbGenFinal = 1;
    else
        NbGenFinal = nbGenerations;
    nbSlider->setDisabled(true);
    ValiderNbGen->setDisabled(true);
    saisieNbGenerations->setDisabled(true);
}

void InterfaceMatrice::LancerIterateurN()
{
    unsigned int i,j;
    QObject::disconnect(grilleCellule,SIGNAL(cellChanged(int,int)),this,SLOT(ChangerCellule(int,int)));

    travailleur->transformMatrice();
    for(i=0;i<matcour->getSize();i++)
    {
        for(j=0;j<matcour->getSize();j++)
        {
            itemCellule->setText(QString::number(matcour->getVal(i,j)));
        }
    }
    Afficher();

    if((stopNit+1) == NbGenFinal)
    {
        timer1->stop();
    }
    stopNit++;
    QObject::connect(grilleCellule,SIGNAL(cellChanged(int,int)),this,SLOT(ChangerCellule(int,int)));
}

void InterfaceMatrice::NIterations()
{
    timer1 = new QTimer();

    QObject::connect(timer1,SIGNAL(timeout()),this,SLOT(LancerIterateurN()));

    stopNit = 0;
    timer1->start(tempsfinal);

    StopN->setEnabled(true);
    PlayN->setDisabled(true);
    Infini->setDisabled(true);
    StopInf->setDisabled(true);
    nbSlider->setDisabled(true);
    ValiderNbGen->setDisabled(true);
    tempsIteration->setDisabled(true);
    ValiderTemps->setDisabled(true);
    AleaBouton->setDisabled(true);
    Play->setDisabled(true);
}

void InterfaceMatrice::FaireStopN()
{
    timer1->stop();

    PlayN->setEnabled(true);
    Infini->setEnabled(true);
    StopInf->setEnabled(true);
    nbSlider->setEnabled(true);
    ValiderNbGen->setEnabled(true);
    tempsIteration->setEnabled(true);
    ValiderTemps->setEnabled(true);
    AleaBouton->setEnabled(true);
    Play->setEnabled(true);
	saisieNbGenerations->setEnabled(true);
}

void InterfaceMatrice::ChangerRec(int state)
{
    if(state == 0 || state == 1)
        rec = false;
    else
        rec = true;
}

void InterfaceMatrice::InitMatrice()
{
    int somme = 0;
    for (unsigned int i = 0; i < Etats->size(); i++)
    {
        somme += tabAlea.at(i)->value();
    }
    if (somme == 100){
        for (unsigned int i = 0; i < matcour->getSize(); i++)
        {
            for (unsigned int j = 0; j < matcour->getSize(); j++)
            {
                int k = 0;
                int r = (rand() % 100 + 1);
                somme = tabAlea.at(0)->value();
                while (r > somme) {
                    k++;
                    somme += tabAlea.at(k)->value();
                }
                matcour->setVal(i, j, (unsigned short)k);
            }
        }
        Afficher();
    }
    else {
        QMessageBox::information(this, tr("Initialisation Matrice"), tr("Erreur : Les Valeurs sont fausses!"));

    }
}

void InterfaceMatrice::griser(bool b)
{
	AleaBouton->setDisabled(b);
	ValiderTemps->setDisabled(!b);
	Play->setDisabled(b);
	Infini->setDisabled(b);
	StopInf->setDisabled(b);
	PlayN->setDisabled(b);
	StopN->setDisabled(b);
	Chargement->setDisabled(b);
	Enregistrer->setDisabled(b);
	ValiderNbGen->setDisabled(!b);
	enregistrement->setDisabled(!b);
	nbSlider->setDisabled(!b);
}

void InterfaceMatrice::reinit()
{
	QLayoutItem *il;

	while ((il = layoutGridMA->takeAt(0)) != 0)
	{
		il->widget()->hide();
		il->widget()->close();
	}

	for (size_t i = 0; i < tabAlea.size(); i++)
		tabAlea[i]->hide();
	tabAlea.clear();

	brushEtats.clear();

	delete matcour; matcour = NULL;
	travailleur = NULL;
	Etats = NULL;
	delete grilleCellule;
	grilleCellule = new QTableWidget();
	grilleCellule->setFixedSize(803, 803);
	LayoutMatrice->addWidget(grilleCellule);
}

// CONSTRUCTEURS //
InterfaceMatrice::InterfaceMatrice()
{
    //Initialisation matrice courante
    matcour = NULL;
    travailleur=NULL;
    Etats=NULL;

    //Initialisation des Layout
    layoutPrincipal = new QHBoxLayout();
    LayoutSecondaire = new QFormLayout();
    LayoutMatrice = new QVBoxLayout();

    //Initialisation des boutons
    tempsIteration = new QSpinBox();
    tempsIteration->setSuffix("  ms");
    tempsIteration->setRange(250,10000);
    tempsIteration->setValue(250);
    temps = 250;

    grilleCellule = new QTableWidget(this);

    // Initialisation Boutons
    AleaBouton = new QPushButton("Genérer");
    ValiderTemps = new QPushButton("Valider temps");
    Play = new QPushButton("Pas à Pas");
    Infini = new QPushButton("Infini");
    StopInf = new QPushButton("Stop Infini");
    PlayN = new QPushButton("Play N fois");
    StopN = new QPushButton("Stop N itérations");
    Chargement = new QPushButton("Charger matrice");
    Enregistrer = new QPushButton("Enregistrer matrice");
    ChargementTransition = new QPushButton("Charger des Transitions");
    ValiderAppliIte = new QPushButton("Valider");


    // Initialisation Autres Widgets
    QWidget *parent = 0;
    saisieNbGenerations = new QSlider(Qt::Horizontal,parent);
    saisieNbGenerations->setRange(1,100);
    saisieNbGenerations->setValue(1);

    nbSlider = new QLCDNumber();
    nbSlider->setSegmentStyle(QLCDNumber::Flat);
    nbSlider->display(1);
    nbGenerations = 1;

    ValiderNbGen = new QPushButton("Valider");

    enregistrement = new QCheckBox("Enregistrer");
    rec = false;

    VersionIte = new QSpinBox(); VersionIte->setRange(0,5);

    //Connecter les boutons à leurs slots
    QObject::connect(Play,SIGNAL(clicked()),this,SLOT(LancerIterateur()));
    QObject::connect(Infini,SIGNAL(clicked(bool)),this,SLOT(InfiniIterations()));
    QObject::connect(StopInf,SIGNAL(clicked(bool)),this,SLOT(StopInfini()));
    QObject::connect(PlayN,SIGNAL(clicked()),this,SLOT(NIterations()));
    QObject::connect(StopN,SIGNAL(clicked(bool)),this,SLOT(FaireStopN()));
    QObject::connect(tempsIteration,SIGNAL(valueChanged(int)),this,SLOT(RecupererTemps(int)));
    QObject::connect(ValiderTemps,SIGNAL(clicked()),this,SLOT(ValiderTempsFinal()));
    QObject::connect(saisieNbGenerations,SIGNAL(valueChanged(int)),nbSlider,SLOT(display(int)));
    QObject::connect(ValiderNbGen,SIGNAL(clicked()),this,SLOT(NbGenerationsFini()));
    QObject::connect(saisieNbGenerations,SIGNAL(valueChanged(int)),this,SLOT(ChangerNbGenerations(int)));
    QObject::connect(enregistrement,SIGNAL(stateChanged(int)),this,SLOT(ChangerRec(int)));
    QObject::connect(AleaBouton, SIGNAL(clicked()), this, SLOT(InitMatrice()));

    //BOX ET LAYOUTS
    BoxMatriceAlea = new QGroupBox("Init Matrice :");
    InfiniBox = new QGroupBox("Iterations Infinies :");
    NIteBox = new QGroupBox("Iterations N fois :");
    ValiderParamBox = new QGroupBox("Valider Paramètres :");
    BoxChoixVersion = new QGroupBox("Choix Version");

    layoutMA = new QVBoxLayout(BoxMatriceAlea);
	layoutGridMA = new QGridLayout();
    InfiniLayout = new QVBoxLayout(InfiniBox);
    NIteLayout = new QVBoxLayout(NIteBox);
    ValiderParamLayout = new QVBoxLayout(ValiderParamBox);
    LayoutBoxChoix = new QVBoxLayout(BoxChoixVersion);

    //Ajout des Widgets aux Layout
    ValiderParamLayout->addWidget(tempsIteration);
    ValiderParamLayout->addWidget(ValiderTemps);
    ValiderParamLayout->addWidget(enregistrement);

    InfiniLayout->addWidget(Infini);
    InfiniLayout->addWidget(StopInf);

    NIteLayout->addWidget(nbSlider);
    NIteLayout->addWidget(saisieNbGenerations);
    NIteLayout->addWidget(ValiderNbGen);
    NIteLayout->addWidget(PlayN);
    NIteLayout->addWidget(StopN);

    LayoutBoxChoix->addWidget(VersionIte);
    LayoutBoxChoix->addWidget(ValiderAppliIte);

    layoutMA->addWidget(AleaBouton);
	layoutMA->addLayout(layoutGridMA);
    LayoutSecondaire->addWidget(BoxMatriceAlea);
    LayoutSecondaire->addWidget(Play);
    LayoutSecondaire->addWidget(ValiderParamBox);
    LayoutSecondaire->addWidget(InfiniBox);
    LayoutSecondaire->addWidget(NIteBox);

    LayoutSecondaire->addWidget(Enregistrer);
    LayoutSecondaire->addWidget(Chargement);
    LayoutSecondaire->addWidget(ChargementTransition);

    LayoutSecondaire->addWidget(BoxChoixVersion);

    //Ajout de grilleCellule dans le Layout
    grilleCellule->setFixedSize(803,803);
    LayoutMatrice->addWidget(grilleCellule);

    //Ajout des Layout dans le layoutPrincipal
    layoutPrincipal->addLayout(LayoutSecondaire);
    layoutPrincipal->addLayout(LayoutMatrice);

    //layoutPrincipal dans la fenêtre
    this->setLayout(layoutPrincipal);
	griser(true);

}

// DESTRUCTEUR //
InterfaceMatrice::~InterfaceMatrice()
{
    //delete boutons
    delete Play;
    delete Infini;
    delete PlayN;
    delete StopInf;
    delete StopN;
    delete ValiderTemps;
    delete ValiderNbGen;
    delete Chargement;
    delete AleaBouton;

    //delete Affichage
    delete saisieNbGenerations;
    delete enregistrement;
    delete grilleCellule;
    delete nbSlider;
    delete BoxMatriceAlea;
    delete layoutMA;
    delete tempsIteration;

    //delete Iteration
    delete timer1;
    matcour->~Matrice();
    travailleur->~Iterateur();
    delete matcour;
    delete travailleur;
}


// FONCTIONS PUBLIQUES //
void InterfaceMatrice::modificationGrille()
{
    //modification
    bool ok = true;
    matcour->setVal(itemCellule->column(),itemCellule->row(),itemCellule->text().toInt(&ok,10));
}

void InterfaceMatrice::matriceAleatoire()
{}

void InterfaceMatrice::playPause1(bool record)
{
    rec = record;
}

void InterfaceMatrice::playPause2(bool record, int n)
{
    rec = record;
    nbGenerations = n;
}

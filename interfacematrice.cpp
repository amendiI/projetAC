#include "interfacematrice.h"

// FONCTION STATIQUE //
Matrice* InterfaceMatrice::Loading(){
    Matrice* matrix;
    QString chemin = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Fichier Texte(*.txt *.ol *.fe)");
    QString textFichier;
    QFile fichier(chemin);
    //TODO le chemin peut etre passé en paramètre pour etre fourni par un explorateur de fichiers
    if(!fichier.open(QIODevice::ReadOnly|QIODevice::Text)) return NULL;
    //le fichier ne s'est pas ouvert
    textFichier=fichier.readAll();
    fichier.close();
    QRegExp rx("^(\\d+);(\\d+);(\\d+);\\{(\\d+)(?:,\\d+)*\\}$");
    if(rx.indexIn(textFichier) != 0) return NULL;
    //mauvaise syntaxe de fichier !
    bool tmpB=true;
    unsigned short tmp, size=rx.cap(3).toUInt(&tmpB,10), nbPS=rx.cap(2).toUShort(&tmpB,10);
    if(!tmpB)return NULL;
    //erreur de conversion
    matrix=new Matrice(size,nbPS);
    textFichier.remove(0,textFichier.indexOf("{"));
    rx.setPattern("(\\d+)");
    unsigned int cmpt=0,stop=matrix->getNbCells();
    int pos=0;
    while((pos=rx.indexIn(textFichier,pos)) != -1 && cmpt<stop){
        tmp=rx.cap(1).toUShort(&tmpB,10);
        if(tmp>=nbPS)return NULL;
        //valeur incorrecte dans le fichier
        matrix->getCell(cmpt)->setValue(tmp);
        pos+=rx.matchedLength();
        cmpt++;
    }
    if(!tmpB)return NULL;
    //erreur de conversion
    return matrix;
}


int InterfaceMatrice::Recording2(Matrice* matrix){   //store only one state (etat courrant)
    QString text="";
        text+=QString::number(matrix->getNbDimensions());
        text+=";";
        text+=QString::number(matrix->getNbPossibleStates());
        text+=";";
        text+=QString::number(matrix->getSize());
        text+=";";
    QString file = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Fichier Texte(*.txt *.ol *.fe)");
    QString chemin(file);
    //TODO le chemin peut etre passé en paramètre pour etre fourni par un explorateur de fichiers
    QFile fichier(chemin);
    if(!fichier.open(QIODevice::WriteOnly|QIODevice::Text)) return 1;//le fichier ne s'est pas ouvert
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
    return 0;
}


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
    int sizeCell = (hauteurEcran-50)/taille;      //changer ici par hauteurEcran-50

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
        QBrush* B = new QBrush(Etats->at(i)->GetColor());
        brushEtats.push_back(B);
    }

    for (unsigned int i = 0; i <  Etats->size(); i++)
    {
        QHBoxLayout *layoutH = new QHBoxLayout();
        QLabel * L = new QLabel();
        L->setText(Etats->at(i)->GetNom());
        QSpinBox *S = new QSpinBox();
        S->setRange(0, 100);
        QLabel * L2 = new QLabel();
        L2->setText("%");
        tabAlea.push_back(S);
        layoutH->addWidget(L);
        layoutH->addWidget(S);
        layoutH->addWidget(L2);
        layoutMA->addLayout(layoutH);
        L->show();
        S->show();
        L2->show();
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

    if((stopNit-1) == NbGenFinal)
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

void InterfaceMatrice::ChargerMatrice()
{
    matcour = Loading();
    Afficher();
}

void InterfaceMatrice::EnregistrerMatrice()
{
    int record = Recording2(matcour);
    cout << record << endl;
}

// CONSTRUCTEURS //
InterfaceMatrice::InterfaceMatrice(int hE)
{
    //Initialisation matrice courante
    matcour = NULL;
    travailleur=NULL;
    Etats=NULL;
    hauteurEcran = hE;

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
    AleaBouton = new QPushButton("Go");
    AleaBouton->setDisabled(true);
    ValiderTemps = new QPushButton("Valider temps");
    Play = new QPushButton("Play 1 fois");
    Play->setDisabled(true);
    Infini = new QPushButton("Infini");
    Infini->setDisabled(true);
    StopInf = new QPushButton("Stop Infini");
    StopInf->setDisabled(true);
    PlayN = new QPushButton("Play N fois");
    PlayN->setDisabled(true);
    StopN = new QPushButton("Stop N itérations");
    StopN->setDisabled(true);
    Chargement = new QPushButton("Charger matrice");
    Chargement->setDisabled(true);
    Enregistrer = new QPushButton("Enregistrer matrice");
    Enregistrer->setDisabled(true);

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
    QObject::connect(Enregistrer,SIGNAL(clicked(bool)),this,SLOT(EnregistrerMatrice()));
    QObject::connect(Chargement,SIGNAL(clicked(bool)),this,SLOT(ChargerMatrice()));
    QObject::connect(AleaBouton, SIGNAL(clicked()), this, SLOT(InitMatrice()));

    //BOX ET LAYOUTS
    BoxMatriceAlea = new QGroupBox("Init Matrice :");
    InfiniBox = new QGroupBox("Iterations Infinies :");
    NIteBox = new QGroupBox("Iterations N fois :");
    ValiderParamBox = new QGroupBox("Valider Paramètres :");

    layoutMA = new QVBoxLayout(BoxMatriceAlea);
    InfiniLayout = new QVBoxLayout(InfiniBox);
    NIteLayout = new QVBoxLayout(NIteBox);
    ValiderParamLayout = new QVBoxLayout(ValiderParamBox);

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

    layoutMA->addWidget(AleaBouton);
    LayoutSecondaire->addWidget(BoxMatriceAlea);
    LayoutSecondaire->addWidget(Play);
    LayoutSecondaire->addWidget(ValiderParamBox);
    LayoutSecondaire->addWidget(InfiniBox);
    LayoutSecondaire->addWidget(NIteBox);

    LayoutSecondaire->addWidget(Enregistrer);
    LayoutSecondaire->addWidget(Chargement);

    //Ajout de grilleCellule dans le Layout
    grilleCellule->setFixedSize(hauteurEcran-47,hauteurEcran-47);       //A changer! avec la taille de l'ecran -100? px
    LayoutMatrice->addWidget(grilleCellule);

    //Ajout des Layout dans le layoutPrincipal
    layoutPrincipal->addLayout(LayoutSecondaire);
    layoutPrincipal->addLayout(LayoutMatrice);

    //layoutPrincipal dans la fenêtre
    this->setLayout(layoutPrincipal);

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

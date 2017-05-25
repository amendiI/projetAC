#include "interfacematrice.h"

// FONCTION STATIQUE //
static QSize myGetQTableWidgetSize(QTableWidget *table) {
   int wid = table->verticalHeader()->width();
   for (int i = 0; i < table->columnCount(); i++)
   {
       wid += table->columnWidth(i);
   }

   int hei = table->horizontalHeader()->height();
   for (int j = 0; j < table->rowCount(); j++)
   {
       hei += table->rowHeight(j);
   }

   return QSize(wid, hei);
}


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


// PUBLIC SLOTS //

/*
void InterfaceMatrice::actualiserAffichage(QTableWidgetItem * item)
{
    bool ok = true;
    int val;

    printf("coucou, change la valeur mec ! \n");

    val = item->text().toInt(&ok,10);
    if(val > Etats->size() || val < 0)
    {
        printf("coucou, valeur pas bonne \n");
        val = 0;
        item->setText(QString::number(val));
    }

    matcour->setVal(item->column(),item->row(),val);
    item->setBackground(*brushEtats.at(val));
}
*/

void InterfaceMatrice::ChangerCellule(int row, int column)
{
    QTableWidgetItem* item = grilleCellule->item(row,column);
    bool ok = true;
    if(!(item->text().toInt(&ok,10) < Etats->size()))
    {
        item->setText("0");
    }
    matcour->setVal(item->column(),item->row(),item->text().toUShort(&ok,10));
    //travailleur->SetValMatriceTransition(item->column(),item->row(),item->text().toUShort(&ok,10));
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

void InterfaceMatrice::ChangerRec(int state)
{
    if(state == 0 || state == 1)
        rec = false;
    else
        rec = true;
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
}

void InterfaceMatrice::NbIterations()
{
    timer1 = new QTimer();
    QTimer * timer2 = new QTimer();

    QObject::connect(timer1,SIGNAL(timeout()),this,SLOT(LancerIterateur()));
    QObject::connect(timer2,SIGNAL(timeout()),timer1,SLOT(stop()));

    timer1->start(tempsfinal);
    timer2->start(tempsfinal*(NbGenFinal+1));    //de 1 à 10 = 9 itérations --> +1

    int enr;
    if(rec)
    {
        enr = Recording2(matcour);
    }
}

void InterfaceMatrice::FaireStop()
{
    timer1->stop();
    nbSlider->setEnabled(true);
    ValiderNbGen->setEnabled(true);
    tempsIteration->setEnabled(true);
    ValiderTemps->setEnabled(true);
}

void InterfaceMatrice::RecupererTemps(int t)
{
    printf("t = %d \n",t);
    if(t == 0)
        temps = 100;
    else
        temps = t*100;         //100ds = 1s.
}

void InterfaceMatrice::ValiderTempsFinal()
{
    if(temps == 0)
        tempsfinal = 1;
    else
        tempsfinal = temps;
    tempsIteration->setDisabled(true);
    ValiderTemps->setDisabled(true);
}

void InterfaceMatrice::ChargerMatrice()
{
    matcour = Loading();
    Afficher();
}

// CONSTRUCTEURS //
InterfaceMatrice::InterfaceMatrice()
{}

InterfaceMatrice::InterfaceMatrice(Matrice* cour, Iterateur* worker, vector<EtatType *> *type)
{
    //Initialisation matrice courante et Iterateur
    matcour = cour;
    travailleur = worker;
    travailleur->setMatrice(matcour);
    Etats = type;

    //Initialisation des couleurs possibles des cellules
    for(unsigned int i=0; i<Etats->size();i++)
    {
        QBrush* B = new QBrush(Etats->at(i)->GetColor());
        brushEtats.push_back(B);
    }

    //variables
    unsigned int i,j;
    bool ok = true;
    int val;

    //Initialisation grilleCellule avec taille matrice
    grilleCellule = new QTableWidget(this);
    grilleCellule->setRowCount(matcour->getSize());
    grilleCellule->setColumnCount(matcour->getSize());

    //Initialisation des Layout
    QWidget *parent = 0;
    QHBoxLayout *layoutPrincipal = new QHBoxLayout();
    QFormLayout *LayoutSecondaire = new QFormLayout();
    QVBoxLayout *LayoutMatrice = new QVBoxLayout();

    //Initialisation des boutons
    playPause = new QPushButton("Play");

    Stop = new QPushButton("Stop");

    enregistrement = new QCheckBox("Enregistrer");

    saisieNbGenerations = new QSlider(Qt::Horizontal,parent);
    saisieNbGenerations->setRange(1,100);
    saisieNbGenerations->setValue(1);

    nbSlider = new QLCDNumber();
    nbSlider->setSegmentStyle(QLCDNumber::Flat);
    nbSlider->display(1);
    nbGenerations = 1;

    ValiderNbGen = new QPushButton("Valider");

    tempsIteration = new QSpinBox();
    tempsIteration->setSuffix("  ds");
    tempsIteration->setRange(1,100);
    tempsIteration->setValue(10);
    temps = 100;

    ValiderTemps = new QPushButton("Valider temps");

    Chargement = new QPushButton("Charger Matrice");

    //Connecter les boutons à leurs slots
    QObject::connect(saisieNbGenerations,SIGNAL(valueChanged(int)),nbSlider,SLOT(display(int)));

    QObject::connect(playPause,SIGNAL(clicked()),this,SLOT(NbIterations()));

    QObject::connect(Stop,SIGNAL(clicked()),this,SLOT(FaireStop()));

    QObject::connect(enregistrement,SIGNAL(stateChanged(int)),this,SLOT(ChangerRec(int)));

    QObject::connect(saisieNbGenerations,SIGNAL(valueChanged(int)),this,SLOT(ChangerNbGenerations(int)));

    QObject::connect(ValiderNbGen,SIGNAL(clicked()),this,SLOT(NbGenerationsFini()));

    QObject::connect(tempsIteration,SIGNAL(valueChanged(int)),this,SLOT(RecupererTemps(int)));

    QObject::connect(ValiderTemps,SIGNAL(clicked()),this,SLOT(ValiderTempsFinal()));

    QObject::connect(Chargement,SIGNAL(clicked(bool)),this,SLOT(ChargerMatrice()));

    //Ajout des boutons aux Layout
    LayoutSecondaire->addWidget(Chargement);
    LayoutSecondaire->addWidget(enregistrement);
    LayoutSecondaire->addWidget(tempsIteration);
    LayoutSecondaire->addWidget(ValiderTemps);
    LayoutSecondaire->addWidget(saisieNbGenerations);
    LayoutSecondaire->addWidget(nbSlider);
    LayoutSecondaire->addWidget(ValiderNbGen);
    LayoutSecondaire->addWidget(playPause);
    LayoutSecondaire->addWidget(Stop);

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

    //Ajout de grilleCellule dans le Layout
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
    //delete
    delete grilleCellule;
    delete playPause;
    delete enregistrement;
    delete saisieNbGenerations;
    delete nbSlider;
    delete Stop;
    delete timer1;
    delete matcour;
    delete travailleur;
    delete ValiderNbGen;
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

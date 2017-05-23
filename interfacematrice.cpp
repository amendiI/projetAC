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

// PUBLIC SLOTS //
void InterfaceMatrice::actualiserAffichage(QTableWidgetItem * item)
{
    QBrush brush0(Qt::red, Qt::Dense2Pattern);
    QBrush brush1(Qt::blue, Qt::Dense2Pattern);
    QBrush brush2(Qt::green, Qt::Dense2Pattern);
    QBrush brush3(Qt::yellow, Qt::Dense2Pattern);
    QBrush brush4(Qt::magenta, Qt::Dense2Pattern);

    bool ok = true;
    int val;

    val = item->text().toInt(&ok,10);
    if(!ok)
    {
        val = -1;
        item->setText("");
    }

    matcour->setVal(item->column(),item->row(),item->text().toInt(&ok,10));

    switch (val) {
    case 0:
        item->setBackground(brush0);
        break;
    case 1:
        item->setBackground(brush1);
        break;
    case 2:
        item->setBackground(brush2);
        break;
    case 3:
        item->setBackground(brush3);
        break;
    case 4:
        item->setBackground(brush4);
        break;
    default:
        break;
    }
}

void InterfaceMatrice::Afficher()
{
    QBrush brush0(Qt::red, Qt::Dense2Pattern);
    QBrush brush1(Qt::blue, Qt::Dense2Pattern);
    QBrush brush2(Qt::green, Qt::Dense2Pattern);
    QBrush brush3(Qt::yellow, Qt::Dense2Pattern);
    QBrush brush4(Qt::magenta, Qt::Dense2Pattern);

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
            switch (val) {
            case 0:
                item->setBackground(brush0);
                break;
            case 1:
                item->setBackground(brush1);
                break;
            case 2:
                item->setBackground(brush2);
                break;
            case 3:
                item->setBackground(brush3);
                break;
            case 4:
                item->setBackground(brush4);
                break;
            default:
                break;
            }
        }
    }
}

void InterfaceMatrice::LancerIterateur()
{
    unsigned int i,j;

    travailleur->transformMatrice();

    for(i=0;i<matcour->getSize();i++)
    {
        for(j=0;j<matcour->getSize();j++)
        {
            itemCellule->setText(QString::number(matcour->getVal(i,j)));
            actualiserAffichage(itemCellule);
        }
    }
    Afficher();
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
    if(t == 0)
        temps = 100;
    else
        temps = t*100;         //100ds = 1s.
}

void InterfaceMatrice::ValiderTempsFinal()
{
    tempsfinal = temps;
    tempsIteration->setDisabled(true);
    ValiderTemps->setDisabled(true);
}

// CONSTRUCTEURS //
InterfaceMatrice::InterfaceMatrice()
{
    //initialisation test
/*
    matcour = new Matrice(5,2);

    matcour->setMoore(true);
//    Iterateur* worker = new Iterateur(matcour);

    setFixedSize(150+46*matcour->getNbCells(),100+30*matcour->getNbCells());
    grilleCellule = new QTableWidget(this);
    grilleCellule->setRowCount(matcour->getNbCells());
    grilleCellule->setColumnCount(matcour->getNbCells());

    QWidget *parent = 0;
    QHBoxLayout *layoutPrincipal = new QHBoxLayout();
    QFormLayout *LayoutSecondaire = new QFormLayout();
    QVBoxLayout *LayoutMatrice = new QVBoxLayout();

    playPause = new QPushButton("Play/Pause");
    enregistrement = new QCheckBox("Enregistrer");
    saisieNbGenerations = new QSlider(Qt::Horizontal,parent);
    nbSlider = new QLCDNumber();

    nbSlider->setSegmentStyle(QLCDNumber::Flat);

    LayoutSecondaire->addWidget(playPause);
    LayoutSecondaire->addWidget(enregistrement);
    LayoutSecondaire->addWidget(saisieNbGenerations);
    LayoutSecondaire->addWidget(nbSlider);

    QObject::connect(saisieNbGenerations, SIGNAL(valueChanged(int)), nbSlider, SLOT(display(int))) ;

    grilleCellule->setMaximumSize(myGetQTableWidgetSize(grilleCellule));
    grilleCellule->setMinimumSize(layoutPrincipal->maximumSize());
    grilleCellule->setMinimumSize(myGetQTableWidgetSize(grilleCellule));

    grilleCellule->setMaximumSize(QSize(500,500));
    grilleCellule->setMinimumSize(layoutPrincipal->maximumSize());

    grilleCellule->setMaximumSize(QSize(TAILLEMATRICE,TAILLEMATRICE));
    grilleCellule->setMinimumSize(layoutPrincipal->maximumSize());


    //grilleCellule->horizontalHeader()->hide();
    //grilleCellule->verticalHeader()->hide();

    //grilleCellule->horizontalScrollBar()->hide();
    //grilleCellule->verticalScrollBar()->hide();
*/

    //matriceAleatoire();
/*    QBrush brush1(Qt::red, Qt::Dense2Pattern);
    QBrush brush2(Qt::blue, Qt::Dense2Pattern);
    QBrush brush3(Qt::green, Qt::Dense2Pattern);
    QBrush brush4(Qt::yellow, Qt::Dense2Pattern);
    QBrush brush5(Qt::magenta, Qt::Dense2Pattern);

    unsigned int i,j;
    bool ok = true;

    for(i=0; i<matcour->getNbCells(); i++)
    {
        for(j=0; j<matcour->getNbCells(); j++)
        {
            itemCellule = new QTableWidgetItem(matcour->getVal(i,j));
            itemCellule->setTextAlignment(Qt::AlignCenter);
            switch (itemCellule->text().toInt(&ok,10)) {
            case 1:
                itemCellule->setBackground(brush1);
                break;
            case 2:
                itemCellule->setBackground(brush2);
                break;
            case 3:
                itemCellule->setBackground(brush3);
                break;
            case 4:
                itemCellule->setBackground(brush4);
                break;
            case 5:
                itemCellule->setBackground(brush5);
                break;
            default:
                break;
            }
            grilleCellule->setItem(i,j,itemCellule);
        }
    }

    grilleCellule->resize(myGetQTableWidgetSize(grilleCellule));
    grilleCellule->setMaximumSize(myGetQTableWidgetSize(grilleCellule));
    grilleCellule->setMinimumSize(LayoutMatrice->maximumSize());

    LayoutMatrice->addWidget(grilleCellule);

    layoutPrincipal->addLayout(LayoutSecondaire);
    layoutPrincipal->addLayout(LayoutMatrice);

    this->setLayout(layoutPrincipal);

    rec = 0;
    nbGenerations=0;

    QObject::connect(grilleCellule, SIGNAL(itemChanged(QTableWidgetItem*)),this, SLOT(actualiserAffichage(QTableWidgetItem*)));
*/
}

InterfaceMatrice::InterfaceMatrice(Matrice* cour,Iterateur* worker)
{
    //Initialisation matrice courante et Iterateur
    matcour = cour;
    matcour->setMoore(true);
    travailleur = worker;
    travailleur->setMatrice(matcour);

    //Initialisation des couleurs possibles des cellules
    QBrush brush0(Qt::red, Qt::Dense2Pattern);
    QBrush brush1(Qt::blue, Qt::Dense2Pattern);

    //variables
    unsigned int i,j;
    bool ok = true;
    int val;

    //Initialisation grilleCellule avec taille matrice
    grilleCellule = new QTableWidget(this);
    grilleCellule->setRowCount(matcour->getSize());
    grilleCellule->setColumnCount(matcour->getSize());

    QObject::connect(grilleCellule,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(actualiserAffichage(QTableWidgetItem*)));

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
    nbSlider = new QLCDNumber();
    nbSlider->setSegmentStyle(QLCDNumber::Flat);
    ValiderNbGen = new QPushButton("Valider");
    tempsIteration = new QSpinBox();
    tempsIteration->setSuffix("  ds");
    ValiderTemps = new QPushButton("Valider temps");

    //Connecter les boutons à leurs slots
    QObject::connect(saisieNbGenerations,SIGNAL(valueChanged(int)),nbSlider,SLOT(display(int)));
    QObject::connect(playPause,SIGNAL(clicked()),this,SLOT(NbIterations()));
    QObject::connect(Stop,SIGNAL(clicked()),this,SLOT(FaireStop()));
    QObject::connect(enregistrement,SIGNAL(stateChanged(int)),this,SLOT(ChangerRec(int)));
    QObject::connect(saisieNbGenerations,SIGNAL(valueChanged(int)),this,SLOT(ChangerNbGenerations(int)));
    QObject::connect(ValiderNbGen,SIGNAL(clicked()),this,SLOT(NbGenerationsFini()));
    QObject::connect(tempsIteration,SIGNAL(valueChanged(int)),this,SLOT(RecupererTemps(int)));
    QObject::connect(ValiderTemps,SIGNAL(clicked()),this,SLOT(ValiderTempsFinal()));

    //Ajout des boutons aux Layout
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
            switch (val) {
            case 0:
                itemCellule->setBackground(brush0);
                break;
            case 1:
                itemCellule->setBackground(brush1);
                break;
            default:
                break;
            }
            grilleCellule->setItem(i,j,itemCellule);
        }
    }

    //Définir la taille des cellules
    int taille = matcour->getSize();
    int sizeCell = 800/taille;

    for(int c=0;c<grilleCellule->columnCount();c++)
    {
        grilleCellule->setColumnWidth(c,sizeCell);
        grilleCellule->setRowHeight(c,sizeCell);
    }

    //grilleCellule->resizeColumnsToContents();
    //grilleCellule->resizeRowsToContents();

    //Initialisation de la taille de la fenêtre
    //setFixedSize(300+taille*sizeCell+3,20+taille*sizeCell+3);

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
{
/*    //init aleatoire QTableWidgetItem et QTableWidget
    srand(time(NULL));

    QBrush brush1(Qt::red, Qt::Dense2Pattern);
    QBrush brush2(Qt::blue, Qt::Dense2Pattern);
    QBrush brush3(Qt::green, Qt::Dense2Pattern);
    QBrush brush4(Qt::yellow, Qt::Dense2Pattern);
    QBrush brush5(Qt::magenta, Qt::Dense2Pattern);

    QBrush brush6(Qt::darkRed, Qt::Dense2Pattern);
    QBrush brush7(Qt::darkBlue, Qt::Dense2Pattern);
    QBrush brush8(Qt::darkGreen, Qt::Dense2Pattern);
    QBrush brush9(Qt::darkYellow, Qt::Dense2Pattern);
    QBrush brush10(Qt::darkMagenta, Qt::Dense2Pattern);

    int alea;
    int i,j;
    for(i=0; i<NBCELL; i++)
    {
        for(j=0; j<NBCELL; j++)
        {
            //générer nombre aléatoire : fonction rand() C++
            alea = rand()%NB_ETAT_INI+1;
            //le caster en string
            //s = static_cast<QString>(alea);
            //le mettre dans itemCellule
            itemCellule = new QTableWidgetItem(QString::number(alea));
            itemCellule->setTextAlignment(Qt::AlignCenter);
            switch (alea) {
            case 1:
                itemCellule->setBackground(brush1);
                break;
            case 2:
                itemCellule->setBackground(brush2);
                break;
            case 3:
                itemCellule->setBackground(brush3);
                break;
            case 4:
                itemCellule->setBackground(brush4);
                break;
            case 5:
                itemCellule->setBackground(brush5);
                break;
            case 6:
                itemCellule->setBackground(brush6);
                break;
            case 7:
                itemCellule->setBackground(brush7);
                break;
            case 8:
                itemCellule->setBackground(brush8);
                break;
            case 9:
                itemCellule->setBackground(brush9);
                break;
            case 10:
                itemCellule->setBackground(brush10);
                break;
            default:
                break;
            }
            grilleCellule->setItem(i,j,itemCellule);
        }
    }
*/
}

void InterfaceMatrice::playPause1(bool record)
{
    rec = record;
}

void InterfaceMatrice::playPause2(bool record, int n)
{
    rec = record;
    nbGenerations = n;
}

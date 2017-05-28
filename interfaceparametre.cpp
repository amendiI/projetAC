#include "interfaceparametre.h"
#include <QApplication>
#include <QObject>
#include <QMessageBox>
#include "interfaceregle.h"
#include <QDebug>

InterfaceParametre::InterfaceParametre()
{
    this->resize(600, 600);
    parametreLayout = new QVBoxLayout(this);

    //TAILLE LAYOUT
    tailleLayout = new QHBoxLayout();

    tailleLabel = new QLabel();
    saisieTaille = new QSpinBox();

    tailleLabel->setText("Taille Matrice : ");
    saisieTaille->setRange(1, 100);
    saisieTaille->setValue(10);

    tailleLayout->addWidget(tailleLabel);
    tailleLayout->addWidget(saisieTaille);

    parametreLayout->addLayout(tailleLayout);

    //TYPE LAYOUT
    typeLayout = new QHBoxLayout();

    typeLabel = new QLabel();
    saisieVoisinage = new QComboBox();

    typeLabel->setText("Type voisinage : ");
    saisieVoisinage->addItem("Moore");
    saisieVoisinage->addItem("VonNeumman");

    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(saisieVoisinage);

    parametreLayout->addLayout(typeLayout);

    //GROUPBOX ETAT

    boxEtat = new QGroupBox("Etat :");
    //boxEtat->setStyleSheet("border-style: outset; border-width: 2px;");


        //BOX ETAT LAYOUT
        boxEtatLayout = new QVBoxLayout(boxEtat);

        //NOM LAYOUT
        nomLayout = new QHBoxLayout();

        nomLabel = new QLabel();
        saisieNomEtat = new QLineEdit();

        nomLabel->setText("Nom de l\'Etat : ");

        nomLayout->addWidget(nomLabel);
        nomLayout->addWidget(saisieNomEtat);

        boxEtatLayout->addLayout(nomLayout);

        //COULEUR LAYOUT
        couleurLayout = new QHBoxLayout();

        couleurLabel = new QLabel();
        saisieCouleurEtat = new QComboBox();

        couleurLabel->setText("Couleur de l\'Etat : ");
        const QStringList colorNames = QColor::colorNames();
        int index = 0;
        foreach (const QString &colorName, colorNames) {
            const QColor color(colorName);
            saisieCouleurEtat->addItem(colorName, color);
            const QModelIndex idx = saisieCouleurEtat->model()->index(index++, 0);
            saisieCouleurEtat->model()->setData(idx, color, Qt::BackgroundColorRole);
        }

        couleurLayout->addWidget(couleurLabel);
        couleurLayout->addWidget(saisieCouleurEtat);

        boxEtatLayout->addLayout(couleurLayout);

        //BOUTON AJOUTER
        ajouterEtatbouton = new QPushButton("+ Ajouter");

        connect(ajouterEtatbouton, SIGNAL(clicked()),this,SLOT(ajoutEtat()));

        boxEtatLayout->addWidget(ajouterEtatbouton);

        //Fenetre Etat

        fenetreEtatScroll = new QScrollArea();

        fenetreEtat = new QFrame();
        fenetreEtatLayout = new QVBoxLayout(fenetreEtat);


        fenetreEtatScroll->move(50,150);
        fenetreEtatScroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn);
        fenetreEtatScroll->setWidgetResizable(true);

        fenetreEtatScroll->setWidget(fenetreEtat);

        boxEtatLayout->addWidget(fenetreEtatScroll);

    parametreLayout->addWidget(boxEtat);

    //Bouton LAYOUT
    boutonLayout = new QHBoxLayout();

    validerBouton = new QPushButton("Valider");

    connect(validerBouton, SIGNAL(clicked()),this,SLOT(ValiderParametres()));

    boutonLayout->addWidget(validerBouton);

    parametreLayout->addLayout(boutonLayout);

}

InterfaceParametre::~InterfaceParametre()
{

}

int InterfaceParametre::VerifierParametreEtat(QColor c, QString n)
{
    if(n == "") return 1;
    for(unsigned int i = 0; i<tabEtats.size(); i++){
        if (tabEtats.at(i)->GetQColor() == c) return 2;
        if (tabEtats.at(i)->GetNom() == n) return 3;
    }
    return 0;
}

int InterfaceParametre::getTaille()
{
	return saisieTaille->value();
}

int InterfaceParametre::getVoisinage()
{
	return saisieVoisinage->currentIndex();
}

int InterfaceParametre::getNbEtats()
{
	return (int) tabEtats.size();
}

QString InterfaceParametre::getNomEtat(int i)
{
	return tabEtats.at(i)->GetNom();
}

QString InterfaceParametre::getColorStrEtat(int i)
{
    return tabEtats.at(i)->GetColor();
}


void InterfaceParametre::setTailleMatrice(int i)
{
	saisieTaille->setValue(i);
}

void InterfaceParametre::setTypeVoisinage(int i)
{
	saisieVoisinage->setCurrentIndex(i);
}

void InterfaceParametre::ajouterEtatChargement(QString nom, QString colorStr)
{
		EtatType *E = new EtatType(&tabEtats, colorStr, nom, fenetreEtat);
		fenetreEtatLayout->addWidget(E);
		tabEtats.push_back(E);

		saisieNomEtat->setText("");
		saisieCouleurEtat->setCurrentIndex(0);
 
	
}

void InterfaceParametre::griser(bool b)
{
	saisieTaille->setDisabled(b);
	saisieVoisinage->setDisabled(b);
	saisieNomEtat->setText("");
	saisieNomEtat->setDisabled(b);
	saisieCouleurEtat->setDisabled(b);
	ajouterEtatbouton->setDisabled(b);
	fenetreEtat->setDisabled(b);
	validerBouton->setDisabled(b);
}

void InterfaceParametre::reinit()
{
	tabEtats.clear();
}

void InterfaceParametre::ajoutEtat(){

    int v = VerifierParametreEtat(QColor(saisieCouleurEtat->currentText()),saisieNomEtat->text());
    if (v == 0){
        EtatType *E = new EtatType(&tabEtats,saisieCouleurEtat->currentText(),saisieNomEtat->text(), fenetreEtat);
        fenetreEtatLayout->addWidget(E);
        tabEtats.push_back(E);

        saisieNomEtat->setText("");
        saisieCouleurEtat->setCurrentIndex(0);
    }
     else if(v == 1) {
        QMessageBox::information(this,tr("Parametre"),tr("Erreur : Pas de Nom pour l'Etat"));
    }
    else if (v == 2) {
        QMessageBox::information(this,tr("Parametre"),tr("Erreur : Couleur deja utilise"));

    }
    else if(v == 3){
        QMessageBox::information(this,tr("Parametre"),tr("Erreur : Nom deja utilise"));

    }

}


void InterfaceParametre::ValiderParametres(){

    if(!tabEtats.empty()){
		griser(true);
        emit validP((unsigned int)saisieTaille->value(),(unsigned short)tabEtats.size(), saisieVoisinage->currentIndex(), &tabEtats);
    }

    else {
        QMessageBox::information(this,tr("Parametre"),tr("Erreur :\n Il faut rentrer au moins un Etat."));
    }
}

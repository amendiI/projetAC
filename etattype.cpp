#include "etattype.h"

void EtatType::Supprimer(){

    vector<EtatType *>::iterator it = vectPere->begin();
    while(this != *it) it++;
    vectPere->erase(it);
    delete(this);
}


EtatType::EtatType(vector<EtatType *> *V, QString c, QString s, QWidget *parent):QWidget(parent) {

    vectPere = V;
    couleur = QColor(c);
    c.push_front("background-color: ");

    layout = new QHBoxLayout(this) ;

    echantillonCouleur = new QLineEdit();
    echantillonCouleur->setText("  ");
    echantillonCouleur->setReadOnly(true);
    echantillonCouleur->setStyleSheet(c);

    nom = new QLineEdit();
    nom->setText(s);
    nom->setReadOnly(true);
    nom->setStyleSheet("background-color: white");

    supprimer = new QPushButton("X");
    supprimer->setStyleSheet("background-color: red");
    QObject::connect(supprimer, SIGNAL(clicked()),this,SLOT(Supprimer()));

    layout->addWidget(echantillonCouleur);
    layout->addWidget(nom);
    layout->addWidget(supprimer);

    /*QFrame *separ = new QFrame;
    separ->setFrameStyle(QFrame::VLine | QFrame::Sunken);

    layout->addWidget(separ);*/



}

EtatType::~EtatType(){
}

QColor EtatType::GetColor()
{
    return couleur;
}

QString EtatType::GetNom()
{
    return nom->text();
}


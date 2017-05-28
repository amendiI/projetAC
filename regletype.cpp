#include "regletype.h"

void RegleType::Supprimer(){

    vector<RegleType *>::iterator it = vectPere->begin();
    while(this != *it) it++;
    vectPere->erase(it);
	emit suppr();
    delete(this);
}

RegleType::RegleType(vector<RegleType*> *p, int d, int a, vector<QLineEdit *> *b, int proba, int ap, QWidget *parent) : QWidget(parent)
{
    vectPere = p;
    depart = d;
    arrivee = a;
    this->proba[0] = proba;
    this->proba[1] = ap;
    regles = new string[b->size()]();
    for(unsigned int i=0; i< b->size(); i++){
        regles[i]= b->at(i)->text().toStdString();
    }

    layout = new QHBoxLayout(this);
       labelregles = new QLabel();
       QString t;
       t = "(";
       t+= QString::number(depart);
       t += ",(";
       if (b->at(0)->text() != "")
           t += b->at(0)->text();
       else
           t += "n";
       for (unsigned int i = 1; i<b->size(); i++){
            t += ",";
            if (b->at(i)->text() != "")
                t += b->at(i)->text();
            else
                t += "n";
       }
       t += "),";
       t += QString::number(arrivee);
       t += ",(";
       t += QString::number(this->proba[0]);
       t += "%,";
       t += QString::number(this->proba[1]);
       t += "))";
       labelregles->setText(t);
       labelregles->show();
       layout->addWidget(labelregles);
       supprimerBouton = new QPushButton("X");
	   supprimerBouton->setStyleSheet("background-color: red");
       supprimerBouton->show();
       QObject::connect(supprimerBouton, SIGNAL(clicked()),this,SLOT(Supprimer()));
       layout->addWidget(supprimerBouton);
}

int RegleType::getDepart()
{
    return depart;
}

int RegleType::getArrivee()
{
    return arrivee;
}

string *RegleType::getRegle()
{
    return regles;
}

int *RegleType::getProba()
{
    return proba;
}


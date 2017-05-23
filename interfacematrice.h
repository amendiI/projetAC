#ifndef INTERFACEMATRICE_H
#define INTERFACEMATRICE_H

#include <QWidget>
#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>

#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <QString>
#include <QBrush>
#include <QSize>
#include <QLCDNumber>
#include <QScrollBar>
#include <QTimer>

#include "matrice.h"
#include "iterateur.h"

#define NB_ETAT_INI 5   //nombre d'états initiaux
#define temps 1000      //t = 1000ms = 1s

class InterfaceMatrice:public QWidget
{
    Q_OBJECT
private:
    QTableWidget *grilleCellule;
    QTableWidgetItem *itemCellule;
    QPushButton *playPause;
    QCheckBox *enregistrement;
    bool rec;
    QSlider *saisieNbGenerations;
    int nbGenerations;

    QPushButton* Stop;
    QPushButton* ValiderNbGen;
    int NbGenFinal;
    QLCDNumber *nbSlider;
    Matrice * matcour;
    Iterateur* travailleur;
    QTimer* timer1;

public:
    InterfaceMatrice();
    InterfaceMatrice(Matrice* cour,Iterateur* worker);
    ~InterfaceMatrice();
    void modificationGrille();
    void matriceAleatoire();
    void playPause1(bool record);
    void playPause2(bool record, int n);

public slots:
    void actualiserAffichage(QTableWidgetItem * item);
    void Afficher();
    void LancerIterateur();
    void ChangerRec(int state);
    void ChangerNbGenerations(int val);
    void NbGenerationsFini();
    void NbIterations();
    void FaireStop();
};

#endif // INTERFACEMATRICE_H

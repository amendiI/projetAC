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
#include <QSpinBox>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>

#include "matrice.h"
#include "iterateur.h"
#include "etattype.h"

class InterfaceMatrice:public QWidget
{
    Q_OBJECT
private: //variables
    bool rec;
    int nbGenerations;
    int NbGenFinal;
    int temps;
    int tempsfinal;
    int stopNit;

    //Affichage
    QCheckBox *enregistrement;
    QSlider *saisieNbGenerations;
    QTableWidget *grilleCellule;
    QTableWidgetItem *itemCellule;
    vector<EtatType*> *Etats;
    vector<QBrush*> brushEtats;
    QLCDNumber *nbSlider;
    QSpinBox* tempsIteration;
    QGroupBox * BoxMatriceAlea;
    QVBoxLayout * layoutMA;
    vector<QSpinBox*> tabAlea;

    //Iteration
    Matrice * matcour;
    Iterateur* travailleur;
    QTimer* timer1;

    //Boutons
    QPushButton *Play;      // lancer UNE itération
    QPushButton *Infini;    // lancer une INFINITE d'itérations
    QPushButton *PlayN;     // lancer N itérations
    QPushButton *StopInf;      // Stopper l'infinité d'itérations
    QPushButton *StopN;     // Stopper les N itérations
    QPushButton *ValiderNbGen;  // Valider le nombre N d'itérations
    QPushButton *ValiderTemps;  // Valider le temps entre deux itérations
    QPushButton *Chargement;    // Charger une matrice
    QPushButton *AleaBouton;

public:
    InterfaceMatrice();
    InterfaceMatrice(Matrice* cour,Iterateur* worker,vector<EtatType*> *type);
    ~InterfaceMatrice();
    void modificationGrille();
    void matriceAleatoire();
    void playPause1(bool record);
    void playPause2(bool record, int n);
    Matrice* Loading();
    int Recording2(Matrice* matrix);
    void InitMatrice();

public slots:
    void ChangerCellule(int row,int column);   // changer la valeur d'une cellule
    void Afficher();                // Afficher l'ensemble de la matrice
    void LancerIterateur();         // Lancer l'itérateur une fois
    void InfiniIterations();        // Lancer l'itérateur une infinité de fois
    void StopInfini();              // Arrêter l'itérateur infini
    void RecupererTemps(int t);     // Récupérer le temps entre 2 itérations
    void ValiderTempsFinal();       // Valider le temps final entre 2 itérations
    void ChangerNbGenerations(int val);         // Changer le Nombre de générations grâce au slider
    void NbGenerationsFini();       // Valider le nombre de générations final
    void LancerIterateurN();        // Lancer N itérations
    void LancerNIterations();       // Lancer N itérations
    void FaireStopN();              // Stopper les N itérations
    void ChangerRec(int state);     // Changer l'état de rec

    void ChargerMatrice();          // Charger une matrice
};

#endif // INTERFACEMATRICE_H

#ifndef INTERFACEMATRICE_H
#define INTERFACEMATRICE_H

#include <QWidget>
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
#include <QString>
#include <QBrush>
#include <QSize>
#include <QLCDNumber>
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
    //QCheckBox *enregistrement;
    QSlider *saisieNbGenerations;
    QTableWidget *grilleCellule;
    QTableWidgetItem *itemCellule;
    vector<EtatType*> *Etats;
    vector<QBrush*> brushEtats;
    QLCDNumber *nbSlider;
    QSpinBox *tempsIteration;
    QGroupBox *BoxMatriceAlea;
    QHBoxLayout *layoutPrincipal;
    QFormLayout *LayoutSecondaire;
    QVBoxLayout *LayoutMatrice;
    QVBoxLayout *layoutMA;
	QGridLayout *layoutGridMA;
    QGroupBox *InfiniBox;
    QVBoxLayout *InfiniLayout;
    QGroupBox *NIteBox;
    QVBoxLayout *NIteLayout;
    QGroupBox *ValiderParamBox;
    QVBoxLayout *ValiderParamLayout;
    vector<QSpinBox*> tabAlea;
    //QGroupBox *BoxChoixVersion;
    //QVBoxLayout * LayoutBoxChoix;

    //Iteration
    Matrice *matcour;
    Iterateur *travailleur;
    QTimer *timer1;

    //Boutons
    QPushButton *ValiderNbGen;  // Valider le nombre N d'itérations
    QPushButton *ValiderTemps;  // Valider le temps entre deux itérations


public:
    QPushButton *AleaBouton;    // Initialiser aleatoirement la matrice
    QPushButton *Play;      // lancer UNE itération
    QPushButton *Infini;    // lancer une INFINITE d'itérations
    QPushButton *PlayN;     // lancer N itérations
    QPushButton *StopInf;      // Stopper l'infinité d'itérations
    QPushButton *StopN;     // Stopper les N itérations
    QPushButton *Chargement;    // Charger une matrice
    QPushButton *Enregistrer; // Pour enregistrer une fois
    //QSpinBox *VersionIte;
    //QPushButton* ValiderAppliIte;
   // QPushButton *ChargementTransition;


    InterfaceMatrice();
    //InterfaceMatrice(Matrice* cour,Iterateur* worker,vector<EtatType*> *type);
    ~InterfaceMatrice();
    void modificationGrille();
    void matriceAleatoire();
    void playPause1(bool record);
    void playPause2(bool record, int n);

    void setMatrice(Matrice* matrice);
    void setIterateur(Iterateur* iterateur);
    void setTableauEtats(vector<EtatType*> *type);
	void griser(bool b);
	void reinit();


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
    void NIterations();       // Lancer N itérations
    void FaireStopN();              // Stopper les N itérations
    void ChangerRec(int state);     // Changer l'état de rec
    void InitMatrice();             // initialiser aleatoirement la matrice
};

#endif // INTERFACEMATRICE_H

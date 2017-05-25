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
private:
    QTableWidget *grilleCellule;
    QTableWidgetItem *itemCellule;
    QPushButton *playPause;
    QCheckBox *enregistrement;
    bool rec;
    QSlider *saisieNbGenerations;
    int nbGenerations;

    vector<EtatType*> *Etats;
    vector<QBrush*> brushEtats;
    QPushButton* Stop;
    QPushButton* ValiderNbGen;
    int NbGenFinal;
    QLCDNumber *nbSlider;
    Matrice * matcour;
    Iterateur* travailleur;
    QTimer* timer1;
    QSpinBox* tempsIteration;
    int temps;
    int tempsfinal;
    QPushButton* ValiderTemps;
    QPushButton* Chargement;
	QGroupBox * BoxMatriceAlea;
	QVBoxLayout * layoutMA;
	vector<QSpinBox*> tabAlea;
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

public slots:
    //void actualiserAffichage(QTableWidgetItem * item);
    void ChangerCellule(int row,int column);
    void Afficher();
    void LancerIterateur();
    void ChangerRec(int state);
    void ChangerNbGenerations(int val);
    void NbGenerationsFini();
    void NbIterations();
    void FaireStop();
    void RecupererTemps(int t);
    void ValiderTempsFinal();
    void ChargerMatrice();
	void InitMatrice();
};

#endif // INTERFACEMATRICE_H

#ifndef INTERFACEREGLE_H
#define INTERFACEREGLE_H

#include <etattype.h>
#include "qspinbox.h"
#include "qcombobox.h"
#include "qlineedit.h"
#include "qscrollarea.h"
#include <QLabel>
#include <QCheckBox>
#include "regletype.h"
#include <QFile>
#include <QFileDialog>
#include <QRegExp>
#include <QMessageBox>
#include "Jeu_de_Regle_nt.h"
#include "Jeu_de_Regle.h"
#include "interfacematrice.h"


using namespace std;

class InterfaceRegle : public QWidget
{
    Q_OBJECT

private:

    Jeu_de_Regle_nt *Jdr_nt;
    Jeu_de_Regle * Jdr;
    QHBoxLayout* layoutPere;
    QVBoxLayout *layoutPrincipal;
        QHBoxLayout *layoutDA;
             QLabel *labelDepart;
             QComboBox *saisieDepart;
             QLabel *labelArrive;
             QComboBox *saisieArrive;
        QHBoxLayout * layoutProba;
            QLabel *labelProba;
            QCheckBox *checkProba;
            QSpinBox *saisieProba;
            QLabel *labelArriveP;
            QComboBox *saisieArriveProba;
        //Manque la partie affichage;
        QGridLayout *layoutTabSaisieRegle;
        vector<QLineEdit*> tabSaisieRegle;
        QPushButton *ajouterBouton;
        QFrame *fenetreRegle;
            QScrollArea *fenetreRegleScroll;
            QVBoxLayout *fenetreRegleLayout;
            vector<RegleType *> r;
        QHBoxLayout *layoutBouton;
            QPushButton *validerBouton;
            QPushButton *enregistrerBouton;

public:
    //explicit InterfaceRegle(QWidget *parent = 0);

    InterfaceRegle();

    vector<QLineEdit*> getVectorRegle();

    bool verifRegle();

    void setTableauEtats(vector <EtatType*> *tableau);
    void setJDR(Jeu_de_Regle *Jeu);
    Jeu_de_Regle_nt * getJDR_nt();

public slots:

    void CheckboxStateChanged();
    void ajouterRegle();
    void EnregistrerRegles();
    void ChargerRegles();
    void ValiderRegles();

};
#endif // INTERFACEREGLE_H

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

	InterfaceMatrice * IM;
    Jeu_de_Regle_nt *Jdr_nt;
    Jeu_de_Regle * Jdr;
    int tailleMatrice;
    int voisinage;
    vector<EtatType *> *couleurs;
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
    explicit InterfaceRegle(QWidget *parent = 0);

    InterfaceRegle(QHBoxLayout* p,int v,int taille,Jeu_de_Regle *J, Jeu_de_Regle_nt* J_nt, vector<EtatType *> *tabEtats, QWidget *parent = 0);

    vector<QLineEdit*> getVectorRegle();

    bool verifRegle();

signals:

public slots:

    void CheckboxStateChanged();
    void ajouterRegle();
    void EnregistrerRegles();
    void ChargerRegles();
    void ValiderRegles();

};
#endif // INTERFACEREGLE_H

#ifndef INTERFACEPARAMETRE_H
#define INTERFACEPARAMETRE_H

#include "etattype.h"

#include "qspinbox.h"
#include "qcombobox.h"
#include "qframe.h"
#include "qscrollbar.h"
#include "qpushbutton.h"
#include "qlineedit.h"
#include "qcolordialog.h"
#include "qfiledialog.h"
#include <vector>
#include "QString"
#include "qscrollarea.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include "Jeu_de_Regle_nt.h"
#include "Jeu_de_Regle.h"
#include "interfaceregle.h"


using namespace std;

class InterfaceParametre : public QWidget
{
    Q_OBJECT

private:

	InterfaceRegle * IR;
    Jeu_de_Regle_nt * Jdr_nt;
    Jeu_de_Regle * Jdr;
    vector<EtatType*> tabEtats;
    QVBoxLayout * layoutParent;
    QHBoxLayout* layoutPere;
    QVBoxLayout *parametreLayout;
        QPushButton *chargerBouton;
        QHBoxLayout *tailleLayout;
            QLabel *tailleLabel;
            QSpinBox *saisieTaille;
        QHBoxLayout *typeLayout;
            QLabel *typeLabel;
            QComboBox *saisieVoisinage;
        QGroupBox * boxEtat;
            QVBoxLayout *boxEtatLayout;
                QHBoxLayout * nomLayout;
                    QLabel *nomLabel;
                    QLineEdit *saisieNomEtat;
                QHBoxLayout *couleurLayout;
                    QLabel *couleurLabel;
                    QComboBox *saisieCouleurEtat;
                QPushButton * ajouterEtatbouton;
                QFrame *fenetreEtat;
                    QScrollArea *fenetreEtatScroll;
                    QVBoxLayout *fenetreEtatLayout;
        QHBoxLayout *boutonLayout;
            QPushButton *validerBouton;
            QPushButton *enregistrerBouton;

public:

      InterfaceParametre(QHBoxLayout* p,Jeu_de_Regle* J, Jeu_de_Regle_nt *J_nt, QVBoxLayout *L,QWidget *parent = 0);
	  ~InterfaceParametre();
      int VerifierParametreEtat(QColor c , QString n);


public slots:

      void ajoutEtat();
      void EnregistrerParametres();
      void ChargerParametres();
      void ValiderParametres();
};

#endif // INTERFACEPARAMETRE_H

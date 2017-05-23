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


using namespace std;

class InterfaceParametre : public QWidget
{
    Q_OBJECT

private:
    vector<EtatType*> tabEtats;
    QVBoxLayout * layoutParent;

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

      InterfaceParametre(QVBoxLayout *L,QWidget *parent = 0);

      int VerifierParametreEtat(QColor c , QString n);


public slots:

      void ajoutEtat();
      void EnregistrerParametres();
      void ChargerParametres();
      void ValiderParametres();
};

#endif // INTERFACEPARAMETRE_H

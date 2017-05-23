#ifndef INTERFACEREGLE_H
#define INTERFACEREGLE_H

//#include <QObject>
//#include <vector>
#include <etattype.h>
#include "qspinbox.h"
#include "qcombobox.h"
//#include "qframe.h"
//#include "qscrollbar.h"
//#include "qpushbutton.h"
#include "qlineedit.h"
//#include "qcolordialog.h"
//#include "qfiledialog.h"
//#include <vector>
//#include "QString"
#include "qscrollarea.h"
//#include <QVBoxLayout>
#include <QLabel>
//#include <QGroupBox>
#include <QCheckBox>
//#include <QTableWidget>
#include "regletype.h"
#include <QFile>
#include <QFileDialog>
#include <QRegExp>
#include <QMessageBox>

using namespace std;

class InterfaceRegle : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout *layoutPrincipal;
        QPushButton *chargerBouton;
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

    InterfaceRegle(vector<EtatType *> *tabEtats, QWidget *parent = 0);

    vector<QLineEdit*> getVectorRegle();

    bool verifRegle();

signals:

public slots:

    void CheckboxStateChanged();
    void ajouterRegle();
    void EnregistrerRegles();
    void ChargerRegles();

};
#endif // INTERFACEREGLE_H
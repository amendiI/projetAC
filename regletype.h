#ifndef REGLETYPE_H
#define REGLETYPE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

using namespace std;

class RegleType : public QWidget
{
    Q_OBJECT

private:

    vector<RegleType*> *vectPere;

    int depart;
    int arrivee;
    string * regles;
    int proba[2];

    QHBoxLayout * layout;
        QLabel * labelregles;
        QPushButton *supprimerBouton;

public:
    explicit RegleType(vector<RegleType *> *p, int d, int a, vector<QLineEdit*> *b, int proba, int ap, QWidget *parent = 0);

    int getDepart();
    int getArrivee();
    string* getRegle();
    int* getProba();

signals:

public slots:

    void Supprimer();
};

#endif // REGLETYPE_H

#ifndef ETATTYPE_H
#define ETATTYPE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>



using namespace std;

class EtatType : public QWidget
{
    Q_OBJECT
private:

    vector<EtatType*> *vectPere;
    QColor couleur;
    QPushButton *supprimer;
    QHBoxLayout *layout;
    QLineEdit *nom;
    QLineEdit *echantillonCouleur;

public:
    EtatType(vector<EtatType*> *V,QString c, QString s, QWidget *parent = 0);
    ~EtatType();
    QColor GetColor();
    QString GetNom();

public slots:
    void Supprimer();

};

#endif // ETATTYPE_H

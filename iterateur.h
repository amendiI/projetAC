#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "matrice.h"
#include "Jeu_de_Regle.h"

class Iterateur
{
public:
    /*- Constructeurs -*/
    Iterateur();
    /*- Destructeur -*/
    ~Iterateur();
    /*- Setters -*/
    void setMatrice(Matrice * addrM);
    void setJDR(Jeu_de_Regle * addrJDR);
    void setApplication(int app);
    void setTransitions(unsigned short **trans);
    /*- Méthodes de mise en oeuvre -*/
    int transformMatrice();
private:
    /*- Attributs -*/
    Matrice* matriceCourante;
    Matrice* matriceTransition;
    Jeu_de_Regle * regles;
    unsigned short* voisins;
    unsigned short* etatsVoisins;
    unsigned short** transitionTable;//format: CN(ne)E(se)S(sw)W(nw)C'
    int application;
    /*- Méthode de mise en oeuvre -*/
    void transformCellule(unsigned int cellule);
    void somEnvironment(unsigned int cellule);
    void applyTransitionTable(unsigned int cellNumber);
};

#endif // ITERATEUR_H

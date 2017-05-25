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
	/*- Méthodes de mise en oeuvre -*/
    int transformMatrice();
    //void SetValMatriceTransition(unsigned int i,unsigned int j,unsigned int NewValue);
private:
	/*- Attributs -*/
    Matrice* matriceCourante;
    Matrice* matriceTransition;
    Jeu_de_Regle * regles;
    unsigned short* etatsVoisins;
	/*- Méthode de mise en oeuvre -*/
    void transformCellule(unsigned int cellule);
    void somEnvironment(unsigned int cellule);
};

#endif // ITERATEUR_H

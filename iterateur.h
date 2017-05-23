#ifndef ITERATEUR_H
#define ITERATEUR_H

#include <matrice.h>

class Iterateur
{
public:
	/*- Constructeurs -*/
    Iterateur();
	/*- Destructeur -*/
    ~Iterateur();
	/*- Setters -*/
    void setMatrice(Matrice * addrM);
    //void setJDR(JeuDeRegle * addrJDR);
	/*- Méthodes de mise en oeuvre -*/
    int transformMatrice();
private:
	/*- Attributs -*/
    Matrice* matriceCourante;
    Matrice* matriceTransition;
    //JeuDeRegle * regles;
    unsigned short* etatsVoisins;
	/*- Méthode de mise en oeuvre -*/
    void transformCellule(unsigned int cellule);
    void somEnvironment(unsigned int cellule);
};

#endif // ITERATEUR_H

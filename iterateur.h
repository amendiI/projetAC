#ifndef ITERATEUR_H
#define ITERATEUR_H

#include <matrice.h>

class Iterateur
{
public:
    Iterateur();
    ~Iterateur();
    Iterateur(Matrice * addrM);
    void setMatrice(Matrice * addrM);
    //void setJDR(JeuDeRegle * addrJDR);
    int transformMatrice();
private:
    void transformCellule(unsigned int cellule);
    void somEnvironment(unsigned int cellule);
    Matrice* matriceCourante = 0;
    Matrice* matriceTransition = 0;
    //JeuDeRegle * regles;
    unsigned short* etatsVoisins;
};

#endif // ITERATEUR_H

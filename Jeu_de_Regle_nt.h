#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Regle_nt.h"

using namespace std;

class Jeu_de_Regle_nt
{
private:
	list<Regle_nt> L;
	int nb_etat;
	int type_voisinage;

public:
    //constructeur-destructeur
    Jeu_de_Regle_nt();
	~Jeu_de_Regle_nt();

    //setter, joue le rôle du construceteur dans les specifications
    void set_val(int nombre_etat, int type_voisinage);

    //ajoute une règle dans la liste
    void ajout_regle(int d, int a, string* voi, int p[2]);

    //non utilisé car implémentée dans l'interface
    //int verification_donnee();

    //getters
	list<Regle_nt> get_List();//pas dans les specifications
	int get_taille();
	int get_n();
	int get_type_voisinage();
};


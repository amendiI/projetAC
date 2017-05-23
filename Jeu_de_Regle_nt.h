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
	int taille;
	int nb_etat;
	int type_voisinage;

public:
	Jeu_de_Regle_nt(int taille,int nombre_etat,int type_voisinage);
	~Jeu_de_Regle_nt();
	void ajout_regle(int d, int a, string* voi, int p[2]);
	int verification_donnee();
	list<Regle_nt> get_List();//pas dans les specifications
	int get_taille();
	int get_n();
	int get_type_voisinage();
};


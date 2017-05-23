#pragma once
#include "Jeu_de_Regle_nt.h"
#include "Regle.h"
#include "RegleProba.h"

class Jeu_de_Regle
{
private:
	vector<list<RegleProba>> L;
	int probabilitee[2];
	int arrivee;
	int depart;
	vector<string> voisinage;//erreur dans les specification, ce n'es pas un int mais un tableau de string
	int taille;
	int type_voisinage;
	int n;

public:
    Jeu_de_Regle(){}
	~Jeu_de_Regle();
	void traitement_voisinage(int i, vector<int>);
	void verification_donnee(int i, int j, vector<int>);
	int applicationJeu(int* voi, int etat);
    void set_value(Jeu_de_Regle_nt jdrnt);
    int get_taille(){return taille;}
    int get_typevoisinage(){return type_voisinage;}
    int get_nbetat(){return n;}
};


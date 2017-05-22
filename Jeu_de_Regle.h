#pragma once
#include "Jeu_de_Regle_nt.h"
#include "Regle.h"
#include "RegleProba.h"

#define taille_voisinage 4

class Jeu_de_Regle
{
private:
	vector<list<RegleProba>> L;
	int probabilitee[2];
	int arrivee;
	int depart;
	vector<string> voisinage;//erreur dans les specification, ce n'es pas un int mais un tableau de string
public:
	Jeu_de_Regle(Jeu_de_Regle_nt jdrnt);
	~Jeu_de_Regle();
	void traitement_voisinage(int i, vector<int>);
	void verification_donnee(int i, int j, vector<int>);
	int applicationJeu(int* voi, int etat);
};


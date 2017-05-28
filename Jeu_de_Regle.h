#pragma once
#include "Jeu_de_Regle_nt.h"
#include "Regle.h"
#include "RegleProba.h"

class Jeu_de_Regle
{
private:
    vector<list<RegleProba> > L;
	int probabilitee[2];
	int arrivee;
	int depart;
	vector<string> voisinage;//erreur dans les specification, ce n'es pas un int mais un tableau de string
	int type_voisinage;
	int n;

public:
    //constructeur-destructeur
    Jeu_de_Regle(){}
	~Jeu_de_Regle();

    //fonctions traitant le jdr
    void set_value(Jeu_de_Regle_nt jdrnt);
	void traitement_voisinage(int i, vector<int>);
	void verification_donnee(int i, int j, vector<int>);


    int applicationJeu(unsigned short *voi, int etat);
    int get_typevoisinage(){return type_voisinage;}
    int get_nbetat(){return n;}
};


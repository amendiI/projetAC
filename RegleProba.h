#pragma once
#include "Regle.h"

class RegleProba :public Regle
{
private:
	int probabilitee;
	int etatP;
    int n;//pas dans les specifications, obligatoire pour connaitre le nombre d'état

public:
    //constructeur-destructeur
	RegleProba(int d, int a, vector<int> v, int proba, int etatP,int n);
	~RegleProba();

    //getters
	int get_probabilitee();
	int get_etatP();

    //dubuggage
    void aff();
};


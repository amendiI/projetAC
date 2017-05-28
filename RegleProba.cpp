#include "RegleProba.h"

RegleProba::RegleProba(int d, int a, vector<int> v, int proba, int etatP,int n)
{
	etat_depart = d;
	etat_arivee = a;
	probabilitee = proba;
	this->etatP = etatP;
	voisinage = v;
	this->n = n;
}

RegleProba::~RegleProba(){}

int RegleProba::get_probabilitee(){return probabilitee;}

int RegleProba::get_etatP(){return etatP;}


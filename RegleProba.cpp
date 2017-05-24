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

void RegleProba::aff()
{
	cout << "etat depart :" <<etat_depart<< endl;
	cout << "etat arivee :" << etat_arivee << endl;
	cout << "voisinage : ";
	for (int i = 0; i < n; i++)
	{
		cout << voisinage[i] <<",";
	}
	cout << endl;
}

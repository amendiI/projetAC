#include "Regle.h"

Regle::Regle()
{
	etat_depart = -1;
	etat_arivee = -1;
}

Regle::Regle(int d, int a, vector<int> v)
{
	etat_depart = d;
	etat_arivee = a;
	voisinage = v;
}

Regle::~Regle(){}

int Regle::get_depart(){return etat_depart;}

int Regle::get_arivee(){return etat_arivee;}

vector<int> Regle::get_voisinage(){return voisinage;}

#include "Regle_nt.h"

Regle_nt::Regle_nt(int d, int a, string* voi, int* p,int nb_etat)
{
	n = nb_etat;
	etat_depart = d;
	etat_arrivee = a;
	probabilitee[0] = p[0];
	probabilitee[1] = p[1];

	for (int i = 0; i < n; i++)
	{
		voisinage.insert(voisinage.end(), voi[i]);
	}
}

Regle_nt::~Regle_nt()
{
}

int Regle_nt::get_depart()
{
	return etat_depart;
}

int Regle_nt::get_arrivee()
{
	return etat_arrivee;
}

vector<string> Regle_nt::get_voisinage()
{
	return voisinage;
}

int* Regle_nt::get_probabilitee()
{
	return probabilitee;
}

void Regle_nt::affichage()
{	
	/*
	cout << "(" << etat_depart << "," << etat_arrivee << ")" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << voisinage[i]<<"|";
	}
	cout << endl;
	*/
}

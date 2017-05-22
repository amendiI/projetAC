#include "stdafx.h"
#include "Regle.h"

#include "iostream"
using namespace std;

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
	cout << "(" << etat_depart << "," << etat_arivee << ")" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << voisinage[i] << "|";
	}
	cout << endl<<endl;
}

Regle::~Regle()
{
}

int Regle::get_depart()
{
	return etat_depart;
}

int Regle::get_arivee()
{
	return etat_arivee;
}
vector<int> Regle::get_voisinage()
{
	return voisinage;
}

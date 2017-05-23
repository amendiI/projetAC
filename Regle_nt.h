#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Regle_nt
{
private:
	int etat_depart;
	int etat_arrivee;
	vector<string> voisinage;//modification mineur par rapport au specification
	int probabilitee[2];//modification: la 1ere case est la probabilitée et la 2eme est l'etat alternatif
	int n;
public:
	Regle_nt(int d,int a,string* voisinage,int* p,int nb_etat);
	~Regle_nt();
	int get_depart();
	int get_arrivee();
	vector<string> get_voisinage();
	int* get_probabilitee();
	void affichage();
};


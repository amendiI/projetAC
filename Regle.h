#pragma once
#include <vector>
#include "iostream"
using namespace std;
/*
 * classe non utilisé, elle est remplacé par la classe règle_proba qui gère les probabilitées a 100%
 */

class Regle
{
protected:
	int etat_depart;
	int etat_arivee;
	vector<int> voisinage;

public:
    //constructeur-destructeur
	Regle();
	Regle(int d,int a, vector<int> v);
	~Regle();

    //getters
	int get_depart();
	int get_arivee();
	vector<int> get_voisinage();
};


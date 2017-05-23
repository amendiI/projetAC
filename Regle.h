#pragma once
#include <vector>

using namespace std;

class Regle
{
protected:
	int etat_depart;
	int etat_arivee;
	vector<int> voisinage;
public:
	Regle();
	Regle(int d,int a, vector<int> v);
	~Regle();
	int get_depart();
	int get_arivee();
	vector<int> get_voisinage();
};


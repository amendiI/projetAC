#pragma once
#include "Regle.h"
#define n 4

class RegleProba :public Regle
{
private:
	int probabilitee;
	int etatP;

public:
	RegleProba(int d, int a, vector<int> v, int proba, int etatP);
	~RegleProba();
	int get_probabilitee();
	int get_etatP();
	void aff();
};


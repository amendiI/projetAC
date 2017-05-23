#pragma once
#include "Regle.h"

class RegleProba :public Regle
{
private:
	int probabilitee;
	int etatP;
	int n;

public:
	RegleProba(int d, int a, vector<int> v, int proba, int etatP,int n);
	~RegleProba();
	int get_probabilitee();
	int get_etatP();
	void aff();
};


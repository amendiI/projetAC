#include "Jeu_de_Regle.h"

int nb;//variable globale utile pour Tpresison qui ne peux ni faire partie de la classe ni prendre un argument supplementaire

bool Tpresision(Regle_nt R1, Regle_nt R2)//pas dans les specifications mais obligatoire pour trier la liste.
{
	int c1 = 0;
	int c2 = 0;
    for (int i = 0; i < nb; i++)
	{
		if (!R1.get_voisinage()[i].compare(""))
			c1++;
		if (!R2.get_voisinage()[i].compare(""))
			c2++;
	}

	return (c1<c2);
}


void Jeu_de_Regle::set_value(Jeu_de_Regle_nt jdrnt)
{
	taille = jdrnt.get_taille();
	n = jdrnt.get_n();
    if(jdrnt.get_type_voisinage())
        type_voisinage = 9;
    else
        type_voisinage = 4;
	L.resize(n);
    nb=n;
    jdrnt.get_List().sort(Tpresision);
	for (Regle_nt R : jdrnt.get_List())
	{
		probabilitee[0] = R.get_probabilitee()[0];
		probabilitee[1] = R.get_probabilitee()[1];
		arrivee=R.get_arrivee();
		depart=R.get_depart();
		voisinage=R.get_voisinage();
		vector<int> T(n,0) ;
		T.resize(n);
		traitement_voisinage(0, T);
	}
}

Jeu_de_Regle::~Jeu_de_Regle()
{
}
//TODO PROBA
void Jeu_de_Regle::traitement_voisinage(int i, vector<int> T)
{
	string tmp = voisinage[i];
	
	if (voisinage[i].find("+", voisinage[i].size()-1)!=-1)
	{
		int x=stoi(tmp.erase(voisinage[i].size() - 1, 1));
		for (int j = x; j <=taille; j++)
			verification_donnee(i, j, T);
	}
	else if (voisinage[i].find("-", voisinage[i].size() - 1) != -1)
	{
		cout << "-" << endl;
		int x = stoi(tmp.erase(voisinage[i].size() - 1, 1));
		for (int j = x; j >= 0; j--)
			verification_donnee(i, j, T);
	}
	else if (voisinage[i].find("-") != -1)
	{
        size_t pos = voisinage[i].find("-");
		int x = stoi(tmp.substr(0, pos));
		int y = stoi(tmp.substr(pos+1));
		cout << x << endl;
		cout << y << endl;
		for (int j = x; j <= y; j++)
			verification_donnee(i, j, T);
	}
	else if (voisinage[i].empty())
		verification_donnee(i, -1, T);
	
	else
		verification_donnee(i,stoi(voisinage[i]),T);
}

void Jeu_de_Regle::verification_donnee(int i,int j, vector<int> T)
{

	vector<int> Ntab(T);
	Ntab[i] = j;
	if (i==n-1)
	{
			L[depart].push_back(RegleProba(depart, arrivee, Ntab,probabilitee[0],probabilitee[1], n));
	}
	else
	{
		traitement_voisinage(i + 1, Ntab);
	}
}

int Jeu_de_Regle::applicationJeu(int * voi, int etat)
{
	bool bol = true;
	for (RegleProba R : L[etat])
	{
		int vide=0;
		bol = true;

		for (int i = 0; i < n; i++)
		{
			if (R.get_voisinage()[i] != voi[i]&& R.get_voisinage()[i]!=-1)
				bol = false;
			if (R.get_voisinage()[i] == -1)
				vide++;
		}
		if (bol|| vide == 4)
			if (R.get_probabilitee() == 100)
				return R.get_arivee();
			else if (R.get_probabilitee() >= (rand() % 100 + 1))
				return R.get_arivee();
			else
				return R.get_etatP();
			
	}
	return etat;
}

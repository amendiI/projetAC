#include "Jeu_de_Regle_nt.h"

Jeu_de_Regle_nt::Jeu_de_Regle_nt()
{

}

void Jeu_de_Regle_nt::set_val(int taille, int nombre_etat, int type_voisinage)
{
	this->taille = taille;
	nb_etat = nombre_etat;
	this->type_voisinage = type_voisinage;
}

Jeu_de_Regle_nt::~Jeu_de_Regle_nt()
{
}

void Jeu_de_Regle_nt::ajout_regle(int d, int a, string* voi, int p[2])
{
	Regle_nt rnt = Regle_nt(d, a, voi, p,nb_etat);
	L.emplace_front(rnt);
	L.front().affichage();
}

int Jeu_de_Regle_nt::verification_donnee()
{
	for (Regle_nt R:L)
	{
		vector<string> vs = R.get_voisinage();
		for (int i = 0; i < nb_etat -1; i++)
		{
			mot_ok:
			string s = vs[i];
			if (s[i] == 0|| s[i] == 1 || s[i] == 2 || s[i] == 3 || s[i] == 4 || s[i] == 5 || s[i] == 6 || s[i] == 7 || s[i] == 8 || s[i] == 9)
			{
				i++;
				while (s[i] == 0 || s[i] == 1 || s[i] == 2 || s[i] == 3 || s[i] == 4 || s[i] == 5 || s[i] == 6 || s[i] == 7 || s[i] == 8 || s[i] == 9)
					i++;
				if (i == s.size())
					goto mot_ok;
				if (s[i] == '+' || s[i] == '-')
				{
					i++;
					if (i == s.size())
						goto mot_ok;

					if (s[i] == 0 || s[i] == 1 || s[i] == 2 || s[i] == 3 || s[i] == 4 || s[i] == 5 || s[i] == 6 || s[i] == 7 || s[i] == 8 || s[i] == 9)
					{
						i++;
						while (s[i] == 0 || s[i] == 1 || s[i] == 2 || s[i] == 3 || s[i] == 4 || s[i] == 5 || s[i] == 6 || s[i] == 7 || s[i] == 8 || s[i] == 9)
							i++;
						if (i == s.size())
							goto mot_ok;
					}
				}
				else
					return 0;
					
			}
			else
				return 0;
		}
	}
	return 1;
}

list<Regle_nt> Jeu_de_Regle_nt::get_List()
{
	return L;
}

int Jeu_de_Regle_nt::get_taille()
{
	return taille;
}

int Jeu_de_Regle_nt::get_n()
{
	return nb_etat;
}

int Jeu_de_Regle_nt::get_type_voisinage()
{
	return type_voisinage;
}




#include "Jeu_de_Regle_nt.h"

Jeu_de_Regle_nt::Jeu_de_Regle_nt(){}

Jeu_de_Regle_nt::~Jeu_de_Regle_nt(){}

void Jeu_de_Regle_nt::set_val(int nombre_etat, int type_voisinage)
{
	nb_etat = nombre_etat;
	this->type_voisinage = type_voisinage;
}

void Jeu_de_Regle_nt::ajout_regle(int d, int a, string* voi, int p[2])
{
	Regle_nt rnt = Regle_nt(d, a, voi, p,nb_etat);
	L.emplace_front(rnt);
}

list<Regle_nt> Jeu_de_Regle_nt::get_List(){return L;}


int Jeu_de_Regle_nt::get_n(){return nb_etat;}

int Jeu_de_Regle_nt::get_type_voisinage(){return type_voisinage;}




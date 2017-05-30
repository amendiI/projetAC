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

Jeu_de_Regle::~Jeu_de_Regle() {}

//cr�e le jeu de r�gle
void Jeu_de_Regle::set_value(Jeu_de_Regle_nt jdrnt)
{
	//nettoie la liste au cas ou il existe quelque chose
	for (size_t i = 0; i < L.size(); i++)
		L[i].clear();
	L.clear();

	//r�cuperation des donn�es
	n = jdrnt.get_n();
    if(jdrnt.get_type_voisinage())
        type_voisinage = 9;
    else
        type_voisinage = 4;
	L.resize(n);
    nb=n;
	//tris de la liste, les r�gles les plus pr�cise sont mise en premeier
    jdrnt.get_List().sort(Tpresision);
	//pour chaque regle non trait�
	for (Regle_nt R : jdrnt.get_List())
	{
		//initialisation de la r�gle,et des param�tres invariant
		probabilitee[0] = R.get_probabilitee()[0];
		probabilitee[1] = R.get_probabilitee()[1];
		arrivee=R.get_arrivee();
		depart=R.get_depart();
		voisinage=R.get_voisinage();

		//initalisation du vecteur qui contiens les differents �tats requis du voisinage
		vector<int> T(n,0) ;
		T.resize(n);
		//lance le traitement du voisinage pour le premier �tat.
		traitement_voisinage(0, T);
	}
}

void Jeu_de_Regle::traitement_voisinage(int i, vector<int> T)
{
	string tmp = voisinage[i];
	
	//regarde quel est l'entr�e et appel verification voisinage avec les nombres requis
	if (voisinage[i].find("+", voisinage[i].size()-1)!=-1)
	{
		int x=stoi(tmp.erase(voisinage[i].size() - 1, 1));
        for (int j = x; j <=type_voisinage; j++)
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
		for (int j = x; j <= y; j++)
			verification_donnee(i, j, T);
	}
	//si il n'ya  a pas de nombre, -1 est entr�
	else if (voisinage[i].empty())
		verification_donnee(i, -1, T);
	//le cas par d�faut met la valeur demand�
	else
		verification_donnee(i,stoi(voisinage[i]),T);
}

void Jeu_de_Regle::verification_donnee(int i,int j, vector<int> T)
{
	//copie le vecteur et modifie la valeur dans ce dernier 
	vector<int> Ntab(T);
	Ntab[i] = j;

	//dans le cas ou tout les �tats ont �t� trait� une r�gle est cr�e
	if (i==n-1)
        L[depart].push_back(RegleProba(depart, arrivee, Ntab,probabilitee[0],probabilitee[1], n));
	//sinon on traite l'�tat i+1
	else
        traitement_voisinage(i + 1, Ntab);
}

int Jeu_de_Regle::applicationJeu(unsigned short * voi, int etat)
{
    bool bol;
    int vide;
	for (RegleProba R : L[etat])
	{
        vide=0;
		bol = true;

		for (int i = 0; i < n; i++)
		{
			if (R.get_voisinage()[i] != voi[i]&& R.get_voisinage()[i]!=-1)
				bol = false;
			if (R.get_voisinage()[i] == -1)
				vide++;
		}
        if (bol|| vide == n)
			if (R.get_probabilitee() == 100)
				return R.get_arivee();
			else if (R.get_probabilitee() >= (rand() % 100 + 1))
				return R.get_arivee();
			else
				return R.get_etatP();
	}
	return etat;
}

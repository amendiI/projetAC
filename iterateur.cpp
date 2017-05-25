#include "iterateur.h"

Iterateur::Iterateur(){
	matriceCourante=NULL;
	matriceTransition=NULL;
	etatsVoisins=NULL;
    regles=NULL;
}

/*
Iterateur::Iterateur(Matrice *addrM){
    if(addrM!=NULL){
        matriceCourante=addrM;
        matriceTransition=new Matrice(matriceCourante->getSize(),matriceCourante->getNbPossibleStates());
        matriceTransition->setMoore(matriceCourante->isMoore());
        etatsVoisins=new unsigned short[matriceCourante->getNbPossibleStates()];
    }
}
*/

Iterateur::~Iterateur(){
    free(matriceTransition);
    free(etatsVoisins);
}

void Iterateur::setMatrice(Matrice* addrM){
    if(addrM!=NULL){
        matriceCourante=addrM;
        matriceTransition=new Matrice(matriceCourante->getSize(),matriceCourante->getNbPossibleStates());
        matriceTransition->setMoore(matriceCourante->isMoore());
        etatsVoisins=(unsigned short*)malloc(matriceCourante->getNbPossibleStates() * sizeof(unsigned short));
    }
}

void Iterateur::setJDR(Jeu_de_Regle* rules){
	regles=rules;
}

int Iterateur::transformMatrice(){
    unsigned int i;
    for(i=0;i<matriceCourante->getNbCells();i++){
        transformCellule(i);
    }
    for(i=0;i<matriceCourante->getNbCells();i++){
        matriceCourante->getCell(i)->setValue(matriceTransition->getCell(i)->getValue());
    }
    return 0;
}

void Iterateur::transformCellule(unsigned int cellule){
    somEnvironment(cellule);

    //int* etatsVoisinsCast =(int*)etatsVoisins;
    //Cell* c = matriceTransition->getCell(cellule);
    //int valeurCellule = (int)c->getValue();
    //unsigned short AppJeu = (unsigned short)regles->applicationJeu(etatsVoisinsCast,valeurCellule);

    //cout << regles->applicationJeu(etatsVoisinsCast,valeurCellule) << endl;

    //matriceTransition->getCell(cellule)->setValue(AppJeu);
    //matriceTransition->getCell(cellule)->setValue((unsigned short)regles->applicationJeu((int*)etatsVoisins  , (int)cellule->getValue()));

    matriceTransition->getCell(cellule)->setValue((unsigned short)regles->applicationJeu(etatsVoisins,(int)matriceCourante->getCell(cellule)->getValue()));
}

void Iterateur::somEnvironment(unsigned int cellule){

    unsigned int a=cellule%matriceCourante->getSize(),b=(cellule-a)/(matriceCourante->getSize());
    for(int i=0;i<matriceCourante->getNbPossibleStates();i++)etatsVoisins[i]=0;
    if(a>0){
        etatsVoisins[matriceCourante->getVal(a-1,b)]++;
        if(matriceCourante->isMoore()){
            if(b>0)     etatsVoisins[matriceCourante->getVal(a-1,b-1)]++;
            if(b<matriceCourante->getSize()-1)etatsVoisins[matriceCourante->getVal(a-1,b+1)]++;
        }
    }
    if(a<matriceCourante->getSize()-1){
        etatsVoisins[matriceCourante->getVal(a+1,b)]++;
        if(matriceCourante->isMoore()){
            if(b>0)     etatsVoisins[matriceCourante->getVal(a+1,b-1)]++;
            if(b<matriceCourante->getSize()-1)etatsVoisins[matriceCourante->getVal(a+1,b+1)]++;
        }
    }
    if(b>0)     etatsVoisins[matriceCourante->getVal(a,b-1)]++;
    if(b<matriceCourante->getSize()-1)etatsVoisins[matriceCourante->getVal(a,b+1)]++;

}

/*
void Iterateur::SetValMatriceTransition(unsigned int i, unsigned int j, unsigned int NewValue)
{
    matriceTransition->setVal(i,j,NewValue);
}
*/

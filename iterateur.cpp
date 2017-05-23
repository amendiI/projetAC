#include "iterateur.h"

Iterateur::Iterateur():Iterateur(NULL)
{

}

Iterateur::Iterateur(Matrice *addrM)
{
    if(addrM!=NULL){
        matriceCourante=addrM;
        matriceTransition=new Matrice(matriceCourante->getSize(),matriceCourante->getNbPossibleStates());
        matriceTransition->setMoore(matriceCourante->isMoore());
        etatsVoisins=new unsigned short[matriceCourante->getNbPossibleStates()];//(unsigned short*)malloc(matriceCourante->getNbPossibleStates() * sizeof(unsigned short));
    }
}

Iterateur::~Iterateur()
{

    free(matriceTransition);
    free(etatsVoisins);
}

void Iterateur::setMatrice(Matrice *addrM)
{
    if(addrM!=NULL){
        matriceCourante=addrM;
        matriceTransition=new Matrice(matriceCourante->getSize(),matriceCourante->getNbPossibleStates());
        matriceTransition->setMoore(matriceCourante->isMoore());
        etatsVoisins=(unsigned short*)malloc(matriceCourante->getNbPossibleStates() * sizeof(unsigned short));
    }
}

int Iterateur::transformMatrice()
{
    unsigned int i;
    for(i=0;i<matriceCourante->getNbCells();i++){
        transformCellule(i);
    }
    for(i=0;i<matriceCourante->getNbCells();i++){
        matriceCourante->getCell(i)->setValue(matriceTransition->getCell(i)->getValue());
    }
    return 0;
}

void Iterateur::transformCellule(unsigned int cellule)
{
    somEnvironment(cellule);

    //TODO (here, example for Game of Life)
    switch(etatsVoisins[1]){
    case 2 : matriceTransition->getCell(cellule)->setValue(matriceCourante->getCell(cellule)->getValue());
        break;
    case 3 : matriceTransition->getCell(cellule)->setValue(1);
        break;
    default: matriceTransition->getCell(cellule)->setValue(0);
    }
}

void Iterateur::somEnvironment(unsigned int cellule) //current version only working for 2D
{

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

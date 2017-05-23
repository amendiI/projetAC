#include "matrice.h"

Matrice::Matrice():Matrice(100,2){

}

Matrice::Matrice(const unsigned int newSize, const unsigned short nbPossibleStates):Matrice(newSize,nbPossibleStates,0){

}

Matrice::Matrice(const unsigned int newSize, const unsigned short nbPossibleStates, const int initOption){
    nbDimensions=nbDim;
    size=newSize;
    nbPS=nbPossibleStates;
    typeVoisinage=false;
    cellules= new Cell[getNbCells()];
    switch(initOption){
    case 0:
        for(unsigned int i=0;i<getNbCells();i++)cellules[i]=Cell();
        break;
    case 1:
        srand((unsigned)time(NULL));
        for(unsigned int i=0;i<getNbCells();i++){
            cellules[i]=Cell();
            cellules[i].setValue(rand()%nbPS);
        }
        break;
    }
}

Matrice::~Matrice(){
    for(unsigned int i=0;i<getNbCells();i++)free(&cellules[i]);
    free(cellules);
}

void Matrice::setMoore(const bool isMoore){
    typeVoisinage=isMoore;
}

void Matrice::setVal(int x,int y,unsigned short newValue){
    setVal(newValue,nbDimensions,x,y);
}

bool Matrice::isMoore(){
    return typeVoisinage;
}

unsigned short Matrice::getNbDimensions(){
    return nbDimensions;
}

unsigned short Matrice::getNbPossibleStates(){
    return nbPS;
}

unsigned int Matrice::getSize(){
    return size;
}

unsigned int Matrice::getNbCells(){
    return pow(size,nbDimensions);
}

unsigned short Matrice::getVal(int x,int y){
    return getVal(nbDimensions,x,y);
}

Cell* Matrice::getCell(unsigned int x){
    return &cellules[x];
}

Cell* Matrice::getCell(unsigned int x,unsigned int y){
    return getCell(nbDimensions,x,y);
}

unsigned short Matrice::getTailleEnvironement(){
    if(typeVoisinage){
        return pow(3,nbDimensions);
    }
    else{
        return 1+2*nbDimensions;
    }
}

void Matrice::setVal(unsigned short newValue, unsigned short nbD,...){
    if(newValue<nbPS){
        unsigned int pos=0,tmp=0;
        va_list ap;
        va_start(ap, nbD);
        for(unsigned short i=0;i<nbD;i++){
            tmp=va_arg(ap, int);
            pos+=pow(size,i)*tmp;
        }
        va_end(ap);
        cellules[pos].setValue(newValue);
    }
}

unsigned short Matrice::getVal(unsigned short nbD,...){
    unsigned int pos=0,tmp=0;
    va_list ap;
    va_start(ap, nbD);
    for(unsigned short i=0;i<nbD;i++){
        tmp=va_arg(ap, int);
        pos+=pow(size,i)*tmp;
    }
    va_end(ap);
    return cellules[pos].getValue();
}

Cell* Matrice::getCell(unsigned short nbD,...){
    unsigned int pos=0,tmp=0;
    va_list ap;
    va_start(ap, nbD);
    for(unsigned short i=0;i<nbD;i++){
        tmp=va_arg(ap, int);
        pos+=pow(size,i)*tmp;
    }
    va_end(ap);
    return &cellules[pos];
}

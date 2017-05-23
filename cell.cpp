#include "cell.h"

Cell::Cell(){
    val=0;
}

Cell::~Cell(){

}


unsigned short Cell::getValue(){
    return val;
}

void Cell::setValue(unsigned short newVal){
    val=newVal;
}
/*
unsigned short* Cell::getEnvironment(){
    unsigned short* environment=malloc(matrice->getTailleEnvironement() * sizeof(unsigned short));
    if(environment == NULL)return NULL;
    environment[0]=val;
    for(unsigned short i=1;i<=matrice->getNbDimensions();i++){
        if(matrice->isMoore()){

        }
        else{

        }
    }
    return environment;
}

void Cell::setMatrice(Matrice * addrM){
    matrice=addrM;
}
*/
